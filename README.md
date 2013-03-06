////////////////////////////////////////////////////
// Lista de Archivos
////////////////////////////////////////////////////
En el .tgz se encuentra los siguientes archivos.
1) README.md		- Este documento
2) Makefile  		- Archivo de compilacion
3) Parametros.txt	- Archivo de configuracion de entrada
4) configLoad.h		- Modulo encargada de cargar el archivo de configuracion (header)
5) configLoad.c		- Modulo encargada de cargar el archivo de configuracion
6) def.h		- Archivo de Defines
7) mathAlgo.h		- Modulo que contiene la funcion matematica (header)
8) mathAlgo.c		- Modulo que contiene la funcion matematica
9) print2screen.h	- Modulo que imprime a pantalla (header)
10) print2screen.c	- Modulo que imprime a pantalla
11) scheduler.h		- Scheduler (header)
12) scheduler.c		- Scheduler

////////////////////////////////////////////////////
// Compilacion y Ejecucion
////////////////////////////////////////////////////

1) Instale la libreria curses.h
   En Ubuntu

	sudo apt-get install libncurses5-dev libncursesw5-dev

2) Descomprima el paquete
	tar -xzvf garita-hidalgo-hsieh-tenorio.tgz

3) Entre al directorio
	cd garita-hidalgo-hsieh-tenorio

4) Ejecute
	make

5) Corra el ejecutable
	lottery.exec	

6) Al finalizar el programa, pulse una tecla para salir.

////////////////////////////////////////////////////
// Opciones
////////////////////////////////////////////////////

Si se va a compilar utilizando gcc, hay que incluir la opcion -lncurses

	gcc  -o lottery.exec configLoad.o main.o mathAlgo.o print2screen.o scheduler.o threads.o -lncurses


////////////////////////////////////////////////////
// Funcionamiento
////////////////////////////////////////////////////

1) Archivo de configuracion

	Entrada de datos:
	Los parametros de entrada del programa se hacen mediante un archivo llamado "Parametros.txt", el nombre del archivo no debe ser cambiado, pues ocasionará que el programa no pueda cargar los datos.
	En este archivo se incluye información de entrada referente a:
	1- Modo de operación (Expropiativo o no expropiativo)
	2- Boletos asignados a cada thread (5 números)
	3- Unidades de trabajo asignados a cada thread (5 números)
	4- Quantum o porcentaje de trabajo (según el modo que se haya escogido)

	Cada dato debe colocarse en una línea separada.

	El programa toma los valores en el archivo de forma secuencial, esto es: el programa asume un orden en el que los datos fueron incluidos en el archivo, por lo que para obtener los resultados esperados este orden debe respetarse.

	El programa permite colocar comentarios en el archivo, siempre y cuando estos comentarios se encuentren en una línea aparte a los datos y que el primer caracter de la línea sea un "#". De esta forma estas lineas seran omitidas por el programa durante la extración de los datos.

	Un detalle importante es que el programa espera números enteros en cada uno de los parametros, por lo que es necesario colocar sólo este tipo de datos para garantizar el correcto funcionamiento del programa (no son permitidos: numeros reales, letras o caracteres especiales, excepto si forman parte de un comentario usando '#' como primer caracter de línea)

	El orden en que deben colocarse los datos en archivo de texto es el siguiente:

	1- Modo de operacion: En este caso solo se debe colocar 1 o 0, 1 en caso de que el modo de operación sea Expropiativo y 0 en caso de que sea No Expropiativo
	2- Boletos asignados al thread 1, es un número entero que indica la cantidad de boletos asignados a el thread #1
	3- Boletos asignados al thread 2, es un número entero que indica la cantidad de boletos asignados a el thread #2
	4- Boletos asignados al thread 3, es un número entero que indica la cantidad de boletos asignados a el thread #3
	5- Boletos asignados al thread 4, es un número entero que indica la cantidad de boletos asignados a el thread #4
	6- Boletos asignados al thread 5, es un número entero que indica la cantidad de boletos asignados a el thread #5
	7- Unidades de trabajo asignadas al thread 1, estas son las unidades de trabajo (50 terminos de la serie de Taylor para Arcsin(x)) que serán ejecutadas por el thread 1.
	8- Unidades de trabajo asignadas al thread 2, estas son las unidades de trabajo (50 terminos de la serie de Taylor para Arcsin(x)) que serán ejecutadas por el thread 2.
	9- Unidades de trabajo asignadas al thread 3, estas son las unidades de trabajo (50 terminos de la serie de Taylor para Arcsin(x)) que serán ejecutadas por el thread 3.
	10- Unidades de trabajo asignadas al thread 4, estas son las unidades de trabajo (50 terminos de la serie de Taylor para Arcsin(x)) que serán ejecutadas por el thread 4.
	11- Unidades de trabajo asignadas al thread 5, estas son las unidades de trabajo (50 terminos de la serie de Taylor para Arcsin(x)) que serán ejecutadas por el thread 5.
	12- Quantum o porcentaje de trabajo, este dato depende del modo de operación: Si se trabaja en modo "Expropiativo" (Modo = 1) éste dato debe contener el quantum en milisegundos cuando el scheduler debe expropiar el thread actual. En caso de trabajar en modo "No Expropiativo" (Modo = 0), éste dato debe contener el porcentaje completado por el thread antes de ceder el CPU al scheduler. Como se puede ver este último dato es dual y su valor y utilización en el programa depende del modo de operación.

	Como se mencionó anteriormente este orden debe respetarse para que los datos sean correctamente interpretados por el programa.

	Para guía al usuario se incluye un ejemplo junto con el programa, en el archivo "Parametros.txt"

2) Main

	1- Carga el archivo de configuracion
	2- Inicializar los threads
	3- Inicializa el display (ncurses)
	4- Llama a la rutina de scheduler

3) Scheduler

	1- Hace scheduling expropiativo o no-expropiativo dependiendo del archivo de configuracion
	2- Inicia los threads mediante las funciones de sigsetjmp() y siglongjmp(), las cuales fueron insertadas dentro de funciones auxiliares
   saveState y restoreState
   3- Despues del primer saveState se retorna el valor que viene ya sea de un restore del estado o de salvar el estado, cuando proviene de salvar
   el estado es 0 el retorno mientras que cuando proviene de restaurar el estado seria un 1, se hizo un experimento de tener pilas distintas para 
   cada thread en cuyo caso devuelve un 5 cuando se requiere restaurar el estado original (para poder devolverse al main con el correcto estado de pila)
   El switch entre thread funciona sin embargo la interrupcion de tiempo no funciona despues de cambiar a un segundo thread, por lo que solo se pudo 
   realizar con un unico thread
   4- Se procede a setear el timer de interrupcion de tiempo y posteriormente a setear la funcion que recibe la interrupcion (en realidad la senal que
   general el SO despues de recibir la interrupcion)
   5- Se decicio utilizar un timer virtual ya que solo toma en cuenta el tiempo mientras se esta ejecutando la tarea y no mientras la tarea fue 
   expropiada por el SO (linux)
	4- Cuando se termina de ejecutar un thread, llama a print2screen() para actualizar la barra de progreso.

4) CalculatePI

	1- Los threads llaman a la funcion calculatePI para hacer la operacion matematica

5) Print2screen

	1- Muestra el progreso de los tasks en pantalla

////////////////////////////////////////////////////
// Display
////////////////////////////////////////////////////

	Al ejecutar el programa, se muestra en vivo las unidades de trabajo total que se asignaron para cada task y tambien la cantidad de trabajo hecho.
	Ademas se muestra en una barra de progreso es status de cada proceso.

	Al finalizar el programa, hay que presionar una tecla para salir.

////////////////////////////////////////////////////
// Limitaciones
////////////////////////////////////////////////////

	Se recomienda una terminal de por lo menos 90x25 para que la barra de progreso no se desborde.
   No esta funcionando para mas de un thread y nos faltaron detalles de integracion de los distintos componentes al centrarnos en realizar el problema 
   que tuvimos, ya que luego de ejecutar el scheduler pasa el control al primer task, luego del quantum de tiempo el control es expropiado y se procede 
   a llamar un segundo thread, sin embargo el control nunca regresa al scheduler (que deberia realizar el catch de la excepcion disparada por el timer)
   sin embargo al parecer no se vuelve a generar esta excepcion cuando se realiza un cambio hacia otra tarea, mientras que si se realiza un cambio entre 
   el scheduler y una sola tarea siempre se generan las excepcion y son capturadas sin problema.



Eso es todo!

  /\_/\
 ( o.o )
  > ^ <

