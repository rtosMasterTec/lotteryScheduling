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
	2- Inicia los threads mediante las funciones de sigsetjmp() y siglongjmp()
	3- Cuando se termina de ejecutar un thread, llama a print2screen() para actualizar la barra de progreso.

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


Eso es todo!

  /\_/\
 ( o.o )
  > ^ <

