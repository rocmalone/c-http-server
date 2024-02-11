#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <unistd.h>

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
    printf("Socket created successfully\n");

    struct sockaddr_in host_addr;
    int host_addrlen = sizeof(host_addr);

    host_addr.sin_family = AF_INET; // Required
    /* Convert host binary representation of port to network representation 
       (networking is big endian, host might be little). 
       Recall: 1 in big endian is 0 0 0 1 vs. 1 0 0 0 in little endian */
    host_addr.sin_port = htons(PORT);

    /* INADDR_ANY accepts messages from any network adapter.
       It translates to 0.0.0.0 */
    struct in_addr host_sin_addr;
    host_sin_addr.s_addr = htonl(INADDR_ANY);
    host_addr.sin_addr.s_addr; 

    /* Bind socket to the address 
       (struct sockaddr *)&host_addr casts the mem addr of host_addr (type 
       sockaddr_in) to a pointer to a sockaddr */
    if (bind(sockfd, (struct sockaddr *)&host_addr, host_addrlen) != 0) {
        perror("[ERR] Webserver (Bind)");
        return 1;
    }
    printf("Socket successfully bound to address\n");

    // Listen for incoming connections
    if (listen(sockfd, SOMAXCONN) != 0) {
        perror("[ERR] Webserver (Listen)");
        return 1;
    }
    printf("Server listening for connections\n");

    // Infinite loop
    for(;;) {
        // Await incoming connections and accept them
        int newsockfd = accept(sockfd, (struct sockaddr *)&host_addr,
                                (socklen_t *)&host_addrlen);

        // Display error then keep accepting connections
        if (newsockfd < 0) {
            perror("[ERR] Webserver (Accept)");
            continue;
        }

        printf("Connection accepted\n");
        close(newsockfd);
    }


    return 0;
}