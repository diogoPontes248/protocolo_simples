#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//definição de comandos de controle da mensagem
#define ERR "err"
#define ACK "ack"
#define NAK "nak"
#define END "end"

//constante da porcentagem de erro do envio da mensagem
#define ERRP 10

struct msg{
    char controle[4];
    char caractere;
};
typedef struct msg mensagem;

struct Pessoa{
    FILE *arquivo;
    char preparado;
    int idx;
    char recebido[200];
};
typedef struct Pessoa pessoa;

mensagem enviarMsg(pessoa *p, mensagem recebido){
    mensagem msg;
    if(strcmp(END, recebido.controle) == 0){
        if(fread(&p->preparado, sizeof(char), 1, p->arquivo)){
            strcpy(msg.controle, ACK);
            msg.caractere = p->preparado;
        }
        else{
            strcpy(msg.controle, END);
        }

        return msg;
    }
    else if(strcmp(ACK, recebido.controle) == 0){
        p->recebido[p->idx] = recebido.caractere;
        p->idx++;
        if(fread(&p->preparado, sizeof(char), 1, p->arquivo)){
            strcpy(msg.controle, ACK);
            msg.caractere = p->preparado;
        }
        else{
            strcpy(msg.controle, END);
        }

        return msg;
    }
    else if(strcmp(NAK, recebido.controle) == 0){
        p->recebido[p->idx] = recebido.caractere;
        p->idx++;

        strcpy(msg.controle, ACK);
        msg.caractere = p->preparado;

        return msg;
    }

    strcpy(msg.controle, NAK);
    msg.caractere = p->preparado;

    return msg;
}

int main()
{
    pessoa A = {0}, B = {0};
    mensagem msgA, msgB;
    srand(time(NULL));

    A.arquivo = fopen("arquivoA.txt", "r");
    B.arquivo = fopen("arquivoB.txt", "r");
    fread(&A.preparado, sizeof(char), 1, A.arquivo);
    fread(&B.preparado, sizeof(char), 1, B.arquivo);
    A.idx = 0;
    B.idx = 0;

    strcpy(msgA.controle, ERR);

    while(strcmp(msgA.controle, END) != 0 && strcmp(msgB.controle, END) != 0){
        msgB = enviarMsg(&A, msgA);
        if((1 + rand() % 100) <= ERRP){
            strcpy(msgB.controle, ERR);
        }
        msgA = enviarMsg(&B, msgB);
        if((1 + rand() % 100) <= ERRP){
            strcpy(msgA.controle, ERR);
        }
    }
    A.recebido[A.idx] = '\0';
    B.recebido[B.idx] = '\0';

    printf("A recebeu: %s\n", A.recebido);
    printf("B recebeu: %s\n", B.recebido);

    fclose(A.arquivo);
    fclose(B.arquivo);

    return 0;
}
