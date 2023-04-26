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
    int twait, tsignal;
    sigset_t signals_set;

    sigfillset(&signals_set);
    sigdelset(&signals_set,SIGKILL);
    sigdelset(&signals_set,SIGINT);
    sigdelset(&signals_set,SIGUSR1);

    printf("O número do processo atual é: %i\n", pid_atual);
    signal(SIGKILL, sigkill);
    signal(SIGINT, sigint);
    signal(SIGUSR1, sigusr1);
    printf("Digite 1 para busy wait e 2 para blocking wait: ");
    scanf("%i", &twait);
    
    if (twait == 1){
        printf("Esperando a recepção do sinal por 2 minutos.\n");
        for (int i =0; i <= 120; i++){
            sleep(1);
        }
    }
    else if (twait == 2){
        sigwait(&signals_set, &tsignal);
    }
    else{
        printf("Valor inválido \n");
        return -1;
    }
    return 0;
}