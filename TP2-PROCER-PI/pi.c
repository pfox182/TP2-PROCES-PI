/*
 * pi.c
 *
 *  Created on: 05/11/2012
 *      Author: utnso
 */



#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE 1024 //TODO:nose
//Variables globales
char *host;
char *puerto;

//Includes propios
#include "FuncionesPropias/manejo_archivos.h"
#include "FuncionesPropias/manejo_mensajes.h"
//Prototipos
void error(const char *msg);
int socket_client(char *nombre_archivo);
int send_ansisop_file(int sockfd,char *nombre_archivo);
int cargar_archivo_configuracion();

int main(int argc, char *argv[])
{
	char *nombre_archivo;

	/*
	if (argc < 3) {
		fprintf(stderr,"usage %s hostname port\n", argv[0]);
	    exit(0);
	}
	*/

	//nombre_archivo="/home/utnso/hola1";
	nombre_archivo=argv[1]; //Implementacion verdadera

	cargar_archivo_configuracion();
	socket_client(nombre_archivo);

    return 0;
}

//FUNCIONES +++++++++++++++++++++++++++++++++++
int socket_client(char *nombre_archivo){

		int sockfd, portno;
	    struct sockaddr_in serv_addr;
	    struct hostent *server;
	    char *buffer=(char *)malloc(BUFFER_SIZE);//Se hace realloc en recibir mensaje
	    char *respuesta=(char *)malloc(strlen("si"));

	    portno = atoi(puerto);

	    sockfd = socket(AF_INET, SOCK_STREAM, 0);
	    if (sockfd < 0){
	        error("ERROR opening socket");
	    }

	    server = gethostbyname(host);
	    if (server == NULL) {
	        fprintf(stderr,"ERROR, no such host\n");
	        exit(0);
	    }

	    serv_addr.sin_family = AF_INET;
	    serv_addr.sin_port = htons(portno);
	    serv_addr.sin_addr = *((struct in_addr *)server->h_addr);
	    memset(&(serv_addr.sin_zero),'\0',8);

	    //Nos conectamos
	    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) == -1){
	        error("ERROR connecting");
	    }


		//Enviar codigo
	    if((send_ansisop_file(sockfd,nombre_archivo)) != 0){
	    	error("ERROR en el send_ansisop_file");
	   }

	   //Recibimos fin,imprimir y suspend
	   if ( recibir_mensaje(&buffer,sockfd) == -1){
		   return -1;
	   }

	   while( strstr(buffer,"finalizado") == NULL ){
		   printf("%s\n",buffer);
		   if( strstr(buffer,"mps") != NULL){
				close(sockfd);
				return -1;//No retorna con error, es un error del flujo normal
			}
		   if( strstr(buffer,"mmp") != NULL){
			   if((send_ansisop_file(sockfd,nombre_archivo)) != 0){
					error("ERROR en el send_ansisop_file");
			   }
			}
		   if( strstr(buffer,"suspendido") != NULL){
		   //LOGICA DEL SUSPEND
			   if ( scanf("%s",respuesta) == -1 ){
				   printf("Error en el scanf\n");
			   }
			   printf("La respuesta que ingresaste es %s\n",respuesta);

			   if ( enviar_mensaje(respuesta,sockfd) == -1){
				   return -1;
			   }
		   //FIN SUSPEND
		   }
		   if ( recibir_mensaje(&buffer,sockfd) == -1){
			   return -1;
		   }
	   }

	   printf("El buffer es: %s\n",buffer);

	   //close(sockfd);

	   return 0;
}
void error(const char *msg)
{
    perror(msg);
    exit(0);
}
int send_ansisop_file(int sockfd,char *nombre_archivo){
	printf("Vamos a leer el archivo %s\n",nombre_archivo);
	char *buffer=leer_archivo(nombre_archivo);

	enviar_mensaje(buffer,sockfd);
	bzero(buffer,sizeof(buffer));
	return 0;
}

int cargar_archivo_configuracion(){
	char *nombre_archivo_conf="/home/utnso/pi.conf";
	char *texto_del_archivo = leer_archivo(nombre_archivo_conf);
	char *linea;
	char *valor;

	while( texto_del_archivo != NULL){
		linea = strtok(texto_del_archivo,"\n");
		texto_del_archivo = strtok(NULL,"\0");

		if( strstr(linea,"puerto")){
			valor = strtok(linea," ");
			valor = strtok(NULL,";");
			if( valor != NULL ){
				puerto=valor;
			}
		}
		if( strstr(linea,"host")){
			valor = strtok(linea," ");
			valor = strtok(NULL,";");
			if( valor != NULL ){
				host=valor;
			}
		}

	}

	return 0;
}


