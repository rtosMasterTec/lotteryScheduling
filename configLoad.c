#include "configLoad.h"

// global variables
config_t config;

int readfile (void) {

   FILE *fr;            /* declare the file pointer */
   char line[80];
   int linea;				/* Numero de linea leido en el archivo de texto */


   fr = fopen("Parametros.txt", "r");  /* open the file for reading */

   if (fr == NULL) {
	printf("Couldn't open file!!\n");
        exit(0);
   }

   /* inicializacion de variables */

   linea = 1;
   config.preemptive = 0;
   config.tickets[0] = 0;
   config.tickets[1] = 0;
   config.tickets[2] = 0;
   config.tickets[3] = 0;
   config.tickets[4] = 0;
   config.workLoad[0] = 0;
   config.workLoad[1] = 0;
   config.workLoad[2] = 0;
   config.workLoad[3] = 0;
   config.workLoad[4] = 0;
   config.quantum = 0;
   config.totalwork = 0;
   config.totaltickets = 0;

   while(fgets(line, 80, fr) != NULL)
   {
	 /* get a line, up to 80 chars from fr.  done if NULL */

	printf("%s",line);

        if (line[0] != '#') {

            if (linea == 1) {
                /*sscanf (line, "%d", &preemptive);*/
                if (line[0] == '1') config.preemptive = true;
                else config.preemptive = false;
                linea = (linea + 1);
            } else
                if (linea == 2) {
                    sscanf (line, "%d", &config.tickets[0]);
                    linea = (linea + 1);
            } else
                if (linea == 3) {
                    sscanf (line, "%d", &config.tickets[1]);
                    linea = (linea + 1);
            } else
                if (linea == 4) {
                    sscanf (line, "%d", &config.tickets[2]);
                    linea = (linea + 1);
            } else
                if (linea == 5) {
                    sscanf (line, "%d", &config.tickets[3]);
                    linea = (linea + 1);
            } else
                if (linea == 6) {
                    sscanf (line, "%d", &config.tickets[4]);
                    linea = (linea + 1);
            } else
                if (linea == 7) {
                    sscanf (line, "%d", &config.workLoad[0]);
                    linea = (linea + 1);
            } else
                if (linea == 8) {
                    sscanf (line, "%d", &config.workLoad[1]);
                    linea = (linea + 1);
            } else
                if (linea == 9) {
                    sscanf (line, "%d", &config.workLoad[2]);
                    linea = (linea + 1);
            } else
                if (linea == 10) {
                    sscanf (line, "%d", &config.workLoad[3]);
                    linea = (linea + 1);
            } else
                if (linea == 11) {
                    sscanf (line, "%d", &config.workLoad[4]);
                    linea = (linea + 1);
            } else
                if (linea == 12) {
                    sscanf (line, "%d", &config.quantum);
                    linea = (linea + 1);
            }
        } /* close if (line[0] != '#') */
   } /* Close While */

   fclose(fr);  /* close the file */

   /* Despliegue de informacion obtenida del archivo */

   if (config.preemptive) printf ("Modo de operacion: No Expropiativo\n");
   else printf ("Modo de operacion: Expropiativo\n");

   printf ("\n");

   printf ("Boletos thread 1: %4d", config.tickets[0]);
   printf ("            Unidades de trabajo thread 1: %4d\n", config.workLoad[0]);

   printf ("Boletos thread 2: %4d", config.tickets[1]);
   printf ("            Unidades de trabajo thread 2: %4d\n", config.workLoad[1]);

   printf ("Boletos thread 3: %4d", config.tickets[2]);
   printf ("            Unidades de trabajo thread 3: %4d\n", config.workLoad[2]);

   printf ("Boletos thread 4: %4d", config.tickets[3]);
   printf ("            Unidades de trabajo thread 4: %4d\n", config.workLoad[3]);

   printf ("Boletos thread 5: %4d", config.tickets[4]);
   printf ("            Unidades de trabajo thread 5: %4d\n", config.workLoad[4]);

   printf ("\n");

   if (config.preemptive) {
        printf ("Tamaño del quantum: %d", config.quantum);
        printf ("ms\n");
   }
   else {
        printf ("Porcentaje de trabajo para ceder CPU: %d", config.quantum);
        printf ("%%\n");
   }
   printf ("\n");

   config.totaltickets = (config.tickets[0]+config.tickets[1]+config.tickets[2]+config.tickets[3]+config.tickets[4]);
   printf ("Total de tiquetes: %d\n", config.totaltickets);

   printf ("\n");

   return 0;
}

