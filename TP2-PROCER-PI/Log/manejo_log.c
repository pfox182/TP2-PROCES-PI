/*
 * manejo_log.c
 *
 *  Created on: 28/11/2012
 *      Author: utnso
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../FuncionesPropias/manejo_archivos.h"
#include "manejo_log.h"


int logx(int proceso,char *log){
	char *nombre_archivo=(char *)malloc(1024);
	bzero(nombre_archivo,1024);
	sprintf(nombre_archivo,"/home/utnso/pi.%d.log",proceso);

	FILE * archivo;
	if ( (archivo=fopen (nombre_archivo, "a+")) == NULL){
		printf("Error al crear el archivo de log\n");
		return -1;
	}

	fwrite(log,sizeof(char),strlen(log),archivo);

	fclose(archivo);

	return 0;
}


