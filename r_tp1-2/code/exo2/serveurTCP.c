#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>


int main(void){

     //Créer une socket de type Datagramme en IPV4
    int sockfd;
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        error_init_socket(sockfd);
    }

    return EXIT_SUCCESS;
}