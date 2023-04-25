#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080
  
int main()
{
    int status, valread, client;
    struct sockaddr_in serv_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(PORT)
    };
    char* hello = "Hello from client";
    char buffer[20];
    client = socket(AF_INET, SOCK_STREAM, 0);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    status = connect(client, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
    send(client, hello, strlen(hello), 0);
    printf("Hello message sent\n");
    valread = read(client, buffer, 20);
    printf("%s\n", buffer);
    close(client);
    return 0;
}