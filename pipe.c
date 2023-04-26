#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
/*A sequência de incremento será feita de 5 em 5 valores*/

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

int main (void) {
    pid_t pid;
    int quant, num, pipe_operations[2], prim;
    int iterante = 1;
    int limitante = 0;
    char numero[20], buffer [20];
    time_t timevar;
    printf("Insira o a quantidade de números a ser analisada: ");
    scanf("%i", &quant);
    srand ((unsigned) time (&timevar));
    if (pipe (pipe_operations)){
        printf("Falha na criação do pipe \n");
        return 1;
    }
    pid = fork ();
    if (pid < 0){
        printf("Falha na realização do fork. \n ");
        return 1;
    }
    else if (pid > 0){
        close (pipe_operations[0]);
        while (limitante < quant){
            sprintf(numero, "%i", iterante);
            write (pipe_operations[1],numero,20);
            limitante ++;
            iterante+=rand() % 100 + 1;
        }
        sprintf(numero, "%i", 0);
        write (pipe_operations[1],numero,20);
    }
    else{
        close (pipe_operations[1]);
        while(1){
            read(pipe_operations[0], buffer, 20);
            num = atoi(buffer);
            if (num == 0){
                printf("Programa finalizado\n");
                exit(0);
            }
            prim = primo(num);
            if (prim == 1){
                printf("O %i informado é primo\n", num);
            }
            else {
                printf("O %i informado não é primo\n", num);
            }
        }

    }
}