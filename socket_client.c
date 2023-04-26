#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/socket.h>
#define PORT 3008
  
int main()
{
    struct sockaddr_in server_address = {
        .sin_family = AF_INET,
        .sin_port = htons(PORT)
    };
    int status, client_socket;
    char numero_string[20], buffer[20];
    int iterante = 1;
    int limitante = 0;
    int quantidade, resultado;
    time_t timevar; 
    printf("insira o número de operações\n");
    scanf("%i", &quantidade);
    srand ((unsigned) time (&timevar)); 
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Ocorreu um erro na criação do socket \n");
        return -1;
    }
    /*Para caso de uma comunicação entre computadores distintos, utilizar o endereço IP do mesmo, o utilizado abaixo indica localhost*/
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);
  
    if ((status = connect(client_socket, (struct sockaddr*)&server_address,sizeof(server_address)))< 0) {
        printf("\nFalha na conexão \n");
        return -1;
    }
    while (limitante < quantidade){
            sprintf(numero_string, "%i", iterante);
            send(client_socket, numero_string, 20, 0);
            read(client_socket, buffer, 20);
            resultado = atoi(buffer);
            if (resultado){
                printf("O número %i é primo\n", iterante);
            }
            else{
                printf("O número %i não é primo\n", iterante);
            }
            limitante ++;
            iterante+= rand() % 100 + 1;
        }
    sprintf(numero_string, "%i", 0);
    send(client_socket, numero_string, 20, 0);
    close(client_socket);
    return 0;
}