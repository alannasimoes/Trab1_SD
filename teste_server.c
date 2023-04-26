#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#define PORT 3008

int primo(int number){
    int limite;
    limite = number/2;
    for (int i = 2;i <= limite; i++){
        if (number%i == 0){
            return 0;
        }
    }
    return 1;
}

int main()
{
    int server, client_socket;
    struct sockaddr_in address = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = INADDR_ANY,
        .sin_port = htons(PORT)
    };
    
    int num, result;
    int structlen = sizeof(address);
    char numero_string[20], buffer[20];
    
    // Creating socket file descriptor
    if ((server = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Falha na criação do socket");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (bind(server, (struct sockaddr*) &address, sizeof(address))< 0) {
        perror("Falha no bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server, 5) < 0) {
        perror("Falha no listen");
        exit(EXIT_FAILURE);
    }
    if ((client_socket = accept(server, (struct sockaddr*)& address,(socklen_t*)& structlen)) < 0) {
        perror("Falha no accept");
        exit(EXIT_FAILURE);
    }
    while(1){
        read(client_socket, buffer, 20);
        num = atoi(buffer);
        if (num == 0){
            printf("Execução encerrada");
            break;
        }
        result = primo(num);
        sprintf(numero_string, "%i", result);
        send(client_socket, numero_string, 20, 0);
    }
    
    close(client_socket);
    shutdown(server, SHUT_RDWR);
    return 0;
}