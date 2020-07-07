#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define RESULTADO_ARQUIVO "resultadosVestibular.txt"
#define RESPOSTAS_ARQUIVO "respostasVestibular.txt"
#define GABARITO_ARQUIVO "gabaritoVestibular.txt"

int qtdLinhas(char* filename){
    FILE *fp;
    int count = 1;
    char c;

    fp = fopen(filename, "r");

    if (fp == NULL){
        printf("Não foi possivel abrir o arquivo");
        return 0;
    }

    for (c = getc(fp); c != EOF; c = getc(fp)){
        if (c == '\n'){
            count = count + 1;
        }
    }

    fclose(fp);

    return count;
}

struct Aluno{
    int id;
    char respostas[52];
    int nota;
};

struct Resultado{
    char gabarito[52];
};


int main(void) {

    FILE *arquivo1, *arquivo2, *arquivo3;
    int linhas = 0, i = 0, j = 0, contador = 0;


    struct Aluno aux;
    struct Resultado vestibular;



    arquivo1 = fopen(RESPOSTAS_ARQUIVO, "r");

    if (arquivo1 == NULL) {
        printf("Não foi possivel abrir o arquivo");
        return 1;
    }
    linhas = qtdLinhas(RESPOSTAS_ARQUIVO);

    struct Aluno alunos[linhas];

    while(!feof(arquivo1)) {
        fscanf(arquivo1,"%d,%s\n", &alunos[i].id, alunos[i].respostas);
        i++;
    }

    for(i = 0; i < linhas; i++) {
        printf("Aluno %d\n ID:%d\t Respostas:%s\n", (i+1), alunos[i].id, alunos[i].respostas);
    }


    arquivo2 = fopen(GABARITO_ARQUIVO, "r");

    if (arquivo2 == NULL) {
        printf("Não foi possivel abrir o arquivo");
        return 1;
    }
    fscanf(arquivo2,"%s", &vestibular.gabarito);
    printf("Gabarito: %s\n", vestibular.gabarito);

    for(i = 0; i < linhas; i++) {
        printf("\n\tAluno %d\n", (i+1));
        for(j = 0; j <= 51; j++) {
            printf("Questao %d  Resposta: %c\n", (j+1), alunos[i].respostas[j]);
            if(alunos[i].respostas[j] == vestibular.gabarito[j]) {
                contador += 1;
            }
        }
        alunos[i].nota = contador;
        contador = 0;
    }
    printf("\n");

    for(i = 0; i < linhas; i++) {
        for (j = 0; j < linhas; j++) {
            if (alunos[i].nota > alunos[j].nota) {
                aux = alunos[i];
                alunos[i] = alunos[j];
                alunos[j] = aux;
            }
        }
    }


    arquivo3 = fopen(RESULTADO_ARQUIVO, "w");

    if (arquivo3 == NULL) {
        printf("Não foi possivel abrir o arquivo");
        return 1;
    }

    for(i = 0; i < linhas; i++){
        fprintf(arquivo3, "%d, %d\n", alunos[i].id, alunos[i].nota);
    }

    fclose(arquivo1);
    fclose(arquivo2);
    fclose(arquivo3);
}
