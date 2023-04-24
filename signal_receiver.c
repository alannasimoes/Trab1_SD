#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void sigkill(){
    /*O signal kill não dá brecha para a execução dessa função*/
    printf("O atual processo foi morto covardemente, saindo...\n");
}

void sigint(){
    printf("Recebi um caractere de interrupção, saindo...\n");
    exit(0);
}

void sigusr1(){
    printf("Recebi um signal pouco específico.\n");
    exit(0);
}

int main(){
    int pid_atual = getpid();
    printf("O número do processo atual é: %i\n", pid_atual);
    signal(SIGKILL, sigkill);
    signal(SIGINT, sigint);
    signal(SIGUSR1, sigusr1);
    printf("Esperando a recepção do sinal por 1 minuto.\n");
    for (int i =0; i <= 120; i++){
        sleep(1);
    }
    return 0;
}

