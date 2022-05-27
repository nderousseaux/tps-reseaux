#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h> 
#include <arpa/inet.h>

//Fonction pour transformer une adresse dans une structure sockaddr en char*
char* get_ip_str(const struct sockaddr* sa, char* s, size_t maxlen) {
    switch (sa->sa_family) {
        case AF_INET: //Si c'est une ipv4
            inet_ntop(AF_INET, &(((struct sockaddr_in *) sa)->sin_addr), s, maxlen);
            return s;
            break;

        case AF_INET6: //Si c'est une ipv6
            inet_ntop(AF_INET6, &(((struct sockaddr_in6 *) sa)->sin6_addr), s, maxlen);
            return s;
            break;

        default: //Sinon
            strncpy(s, "Unknown AF", maxlen);
            return s;
    }
}

int error_init_socket(int sockfd){
    switch (sockfd){
        case EACCES:
            perror("La création d'une telle socket n'est pas autorisée.");
            break;
        case EAFNOSUPPORT:
            perror("L'implémentation ne supporte pas la famille d'adresses indiquée.");
            break;
        case EINVAL:
            perror("Protocole inconnu, ou famille de protocole inexistante.");
            break;
        case EMFILE:
            perror("La table des fichiers est pleine.");
            break;
        case ENFILE:
            perror("La limite du nombre total de fichiers ouverts sur le système a été atteinte.");
            break;
        case ENOBUFS:
            perror("Pas suffisamment d'espace pour allouer les tampons nécessaires. La socket ne peut être créée tant que suffisamment de ressources ne seront pas libérées.");
            break;
        case ENOMEM:
            perror("Pas suffisamment d'espace pour allouer les tampons nécessaires. La socket ne peut être créée tant que suffisamment de ressources ne seront pas libérées.");
            break;
        case EPROTONOSUPPORT:
            perror("Le type de protocole, ou le protocole lui-même n'est pas disponible dans ce domaine de communication.");
            break;
        default:
            perror("Erreur inconnue");
            break;
    }
    return 0;
}

int main(void){
    //Créer une socket de type Datagramme en IPV4
    int sockfd;
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        error_init_socket(sockfd);
    }

    //On prépare une adresse socket 
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000); //Port 5000
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    //On attache le socket et l'addresse
    bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)); 

    //On attend l'arrivée d'un message
    char msg[1024]; //Message qui sera recu
    struct sockaddr client_addr; //Adresse de l'expéditeur
    socklen_t size; //Taille de la réponse

    recvfrom(sockfd, &msg, 1024, 0, &client_addr, &size);

    printf("Message : %s\n", msg); 
    printf("Nombre de caractères : %lu\n", strlen(msg));

    char str_addr_client[1024];
    printf("Addresse du client :%s\n", get_ip_str(&client_addr, str_addr_client, 1024));

    printf("Port du client :%d\n", ((struct sockaddr_in *) &client_addr)->sin_port
    );

    return EXIT_SUCCESS;
}