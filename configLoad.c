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
   
   return 0;
}

