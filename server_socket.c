#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#define PORT 8080

int main(){

    int client_socket, valread;
    
    struct sockaddr_in sock_address = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = htons(INADDR_ANY),
        .sin_port = htons(PORT)
    };
    
    struct sockaddr_in csock_address = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = htons(INADDR_ANY),
        .sin_port = htons(PORT)
    };
    char buffer[20];
    char* hello = "Hello from server";
    int client_size = sizeof csock_address;
    int server = socket(AF_INET, SOCK_STREAM, 0);
/*
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
*/
    bind(server, (struct sockaddr*) &sock_address, sizeof(sock_address));
    listen(server, 5);
    while(1){
        accept(server, (struct sockaddr*) &csock_address, &client_size);
        valread = read(client_socket, buffer, 20);
        printf("%s\n", buffer);
        send(client_socket, hello, strlen(hello), 0);
        printf("Hello message sent\n");
        close(client_socket);
        shutdown(server, SHUT_RDWR);
        return 0;
    }
}
