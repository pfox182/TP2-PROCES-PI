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

//Includes propios
#include "FuncionesPropias/manejo_archivos.h"
#include "FuncionesPropias/manejo_mensajes.h"
//Prototipos
void error(const char *msg);
int socket_client(char* host,char* puerto);
int send_ansisop_file(int sockfd);

int main(int argc, char *argv[])
{
	if (argc < 3) {
		fprintf(stderr,"usage %s hostname port\n", argv[0]);
	    exit(0);
	}

	socket_client(argv[1],argv[2]);

    return 0;
}

//FUNCIONES +++++++++++++++++++++++++++++++++++
int socket_client(char* host,char* puerto){
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
	    if((send_ansisop_file(sockfd)) != 0){
	    	error("ERROR en el send_ansisop_file");
	   }

	   //Recibimos fin,imprimir y suspend
	   if ( recibir_mensaje(buffer,sockfd) == -1){
		   return -1;
	   }
	   while( strstr(buffer,"finalizado") == NULL ){
		   printf("%s\n",buffer);
		   if( strstr(buffer,"mps") != NULL){
				close(sockfd);
				return -1;//No retorna con error, es un error del flujo normal
			}
		   if( strstr(buffer,"mmp") != NULL){
			   if((send_ansisop_file(sockfd)) != 0){
					error("ERROR en el send_ansisop_file");
			   }
			}
		   if( strstr(buffer,"suspendido") != NULL){
			   //tenemos que responder
			   printf("La respuesta que ingresaste es %s\n",respuesta);
			   if ( enviar_mensaje(respuesta,sockfd) == -1){
				   return -1;
			   }
		   }
		   if ( recibir_mensaje(buffer,sockfd) == -1){
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
int send_ansisop_file(int sockfd){
	char *nombre_archivo="/home/utnso/hola1";
	char *buffer=leer_archivo(nombre_archivo);

	enviar_mensaje(buffer,sockfd);
	bzero(buffer,sizeof(buffer));
	return 0;
}



