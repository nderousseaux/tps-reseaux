#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

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

    //On prépare l'adresse du serveur
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000); //Port 5000
    serv_addr.sin_addr.s_addr = INADDR_ANY;


    char data[1024];
    snprintf(data, sizeof data, "Salut, comment vas-tu ?");
    sendto(sockfd, &data, sizeof(data), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    return EXIT_SUCCESS;
}