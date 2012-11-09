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


void error(const char *msg);
int socket_client(char* host,char* puerto);
int send_ansisop_file(int sockfd);
int sendall(int sockfd,char *buffer, int *len);


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

	    char *buffer;
	    int bytes_recived;

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

	    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) == -1){
	        error("ERROR connecting");
	    }

	   printf("LLegue hasta antes del send_ansisop_file\n");

	   //Enviar datos
	   if((send_ansisop_file(sockfd)) != 0){
		   error("ERROR en el send_ansisop_file");
	   }

	   printf("Pase el send_ansisop_file\n");

	   //Recibimos confirmacion
	   if((bytes_recived=recv(sockfd,buffer,256,0)) <= 0){
		   if( bytes_recived == 0){
		   	   printf("El servidor cerro la conexion sin enviar confirmacion\n");
		   }else{
			   error("ERROR en el recv");
		   }
	   }

	   printf("El mensaje recibido es: %s\n",buffer);

	   close(sockfd);

	   return 0;
}
void error(const char *msg)
{
    perror(msg);
    exit(0);
}
int send_ansisop_file(int sockfd){
	char *nombre_archivo="/home/utnso/hola";
	FILE *archivo;
	char *buffer=(char *)malloc(1024);//TODO: malloc por el tamaño del archivo
	char caracter;
	int cant_caracteres = 0;

	archivo=fopen (nombre_archivo, "r");
	if( archivo == NULL){
		error("Error de apertura del archivo\n");
	}


	while(feof(archivo) == 0){
		caracter = fgetc(archivo);
		buffer[cant_caracteres]=caracter;
		cant_caracteres++;
		//fscanf(archivo,"%s", *buffer) != EOF //Otra forma de leer
	}
	buffer[cant_caracteres]='\0';

	//Armamos el paquete a enviar al server
	int header = strlen(buffer);
	printf("Header:%d\n",header);
	//Enviamos el header para indicar el tamaño del paquete
	if( send(sockfd,&header,sizeof(header),0) == -1){
		error("Error al enviar el header");
	}
	printf("BUffer:%s\n",buffer);
	//Enviamos el paquete
	if( sendall(sockfd,&(*buffer),&header) == -1){
		error("Error al enviar el paquete");
	}
	printf("Todo enviado\n");
	fclose(archivo);
	bzero(buffer,sizeof(buffer));
	return 0;
}

int sendall(int sockfd,char *buffer, int *len){
	int total=0;//Los bytes que enviamos hasta ahora
	int bytes_left=*len;//Los bytes que faltan enviar
	int n = 0;

	while( total < *len){
		n = send(sockfd,buffer+total, bytes_left,0);
		if( n == -1){break;}
		total =+ n;
		bytes_left =- n;
	}

	*len = total;//Cantidad de paquetes enviados en realidad

	return n==-1?-1:0;//Que copada esta sentencia XP
}

