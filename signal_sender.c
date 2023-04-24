#include <signal.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>

bool process_exist(int processpid){

    if (kill(processpid, 0) == -1)
    {
        if(errno != ESRCH)
        {
            return true;
        }
        return false;
    }
    return true;
}

int main(){
    int pid_destino, tsignal;
    bool exists;
    
    printf("Digite o número do signal desejado, para mais informações, utilize o comando kill -l: ");
    scanf("%i", &tsignal);
    
    printf("Digite o número do processo destino: ");
    scanf("%i", &pid_destino);
    
    exists = process_exist(pid_destino);
    if (exists == false){
        printf("O processo informado não existe \n");
        return -1;
    }
    if(kill(pid_destino, tsignal) != -1)
        {
            printf("O Signal foi enviado com sucesso! \n");
        }
    return 0;

}