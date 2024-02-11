#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>

#define PORT 8080

int main() {
    // Create a socket
    //   AF_INET: Socket domain for IPv4
    //   SOCK_STREAM: reliable byte streams for TCP
    //   __protocol = 0: default protocol for type
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // Error occured
    if (sockfd == -1) {
        perror("[ERR] Webserver (Socket)");
        // Exit program with error
        return 1;
    }
    printf("Socket created successfully");

    /* Socket address for this host.
       Look in: man 7 ip for struct. */
    // struct sockaddr_in hostaddr;
    // hostaddr.sin_family = AF_INET; // required
    // hostaddr.sin_port = htons(PORT)


    // bind(sockfd, )

    return 0;
}