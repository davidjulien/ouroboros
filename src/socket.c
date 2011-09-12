#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

#include "log.h"

#include "socket.h"

/* Etablissement de la socket */
int establish(const char *hostname, unsigned short int portnum) {
    int s;
    struct hostent *he;
    struct sockaddr_in server;

    /* Création d'un "objet" socket */
    if ((s=socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        ERROR("Erreur de création de la socket : %s", strerror(errno));
        return -1;
    }

    /* Récupération d'une description du host à partir de son nom */
    if ((he = gethostbyname(hostname)) == NULL) {
        ERROR("Erreur d'accès aux informations de %s : %s", hostname, 
                strerror(errno));
        return -1;
    }

    /* Préparation des données */
    memcpy(&server.sin_addr, he->h_addr_list[0], he->h_length);
    server.sin_family = AF_INET;
    server.sin_port = htons(portnum);

    /* Connexion */
    INFO("Connexion sur %s:%d", hostname, portnum);
    if (connect(s, (struct sockaddr *)&server, sizeof(server))) {
        ERROR("Erreur de connexion : %s", strerror(errno));
        return -1;
    }

    INFO("Connexion réussie sur %s:%d (%d)", hostname, portnum, s);

    return s;
}

void close_socket(int fd)
{
    INFO("Fermeture de la socket");
    close(fd);
}
