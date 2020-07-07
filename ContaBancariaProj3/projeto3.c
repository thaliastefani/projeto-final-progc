#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MIN 100000
#define MAX 999999
#define CONTA_ARQUIVO "contaBancaria.txt"
#define EXTRATO_ARQUIVO "extratoBancario.txt"

int gerarNumAleatorio() {

    srand(time(NULL));
    double scaled = (double)rand()/RAND_MAX;

    return (MAX - MIN +1)*scaled + MIN;
}

void menuOperacoes() {
    printf("\n\tMENU DE OPERACOES BANCARIAS\n");
    printf("1. SAQUE\n");
    printf("2. DEPOSITO\n");
    printf("3. SALDO\n");
    printf("4. SAIR\n");
}


struct Cliente {
    char nome[256];
    char cpf[11];
};

struct Conta {
    int numeroConta;
    struct Cliente cliente;
    float saldo;
};


int main() {

    FILE* arquivo;
    int operacaoBancaria = 0, sair = 0;
    float valor = 0;
    char dateStr[9];

    struct Cliente cliente1;
    struct Conta contaBancaria;

    arquivo = fopen(CONTA_ARQUIVO, "w");

    if (arquivo == NULL) {
        printf("Não foi possivel abrir o arquivo: %s", arquivo);
        return EXIT_FAILURE;
    }

    printf("\tABRIR CONTA BANCARIA\n");

    printf("Nome do Cliente: ");
    gets(cliente1.nome);

    printf("CPF do Cliente: ");
    gets(cliente1.cpf);

    contaBancaria.cliente = cliente1;
    contaBancaria.numeroConta = gerarNumAleatorio();
    contaBancaria.saldo = 150;

    printf("\nConta Bancaria aberta com sucesso!\n");

    fprintf(arquivo, "N. Conta: %d\tCliente: %s\tCPF: %s", contaBancaria.numeroConta, contaBancaria.cliente.nome, contaBancaria.cliente.cpf);

    fclose(arquivo);

    printf("\nOla, %s!\n\n", cliente1.nome);

    arquivo = fopen(EXTRATO_ARQUIVO,"w");

    if (arquivo == NULL) {
        printf("Não foi possivel abrir o arquivo: %s", arquivo);
        return EXIT_FAILURE;
    }

    fprintf(arquivo,"%d\t%s\n\nTIPO MOV.\tSALDO ATUAL\tDATA\n", contaBancaria.numeroConta, contaBancaria.cliente.nome);

    while(sair == 0) {
        menuOperacoes();
        printf("\nDigite qual operacao deseja realizar: ");
        scanf("%d", &operacaoBancaria);

        switch(operacaoBancaria) {
        case 1:
            // saque
            printf("\n\tSAQUE\n");
            printf("Saldo atual: %f\n", contaBancaria.saldo);

            do{
                printf("Digite o valor desejado para realizar o SAQUE: ");
                scanf("%f", &valor);

                if(valor > contaBancaria.saldo || valor <= 0){
                    printf("\nValor Invalido. Negativo, Nulo ou Saldo Insuficiente!\n");
                }
            } while (valor > contaBancaria.saldo || valor <= 0);

            contaBancaria.saldo -= valor;
            printf("\nOperacao realizada com sucesso!\n");
            printf("Saldo Atual: %f\n", contaBancaria.saldo);

            fprintf(arquivo,"SAQUE   \t%f\t%s\n", contaBancaria.saldo, _strdate( dateStr));

            break;
        case 2:
            // deposito
            printf("\n\tDEPOSITO\n");
            printf("Saldo atual: %f\n", contaBancaria.saldo);

            do{
                printf("Digite o valor desejado para realizar o DEPOSITO: ");
                scanf("%f", &valor);

                if(valor <= 0){
                    printf("\nValor Invalido. Negativo ou Nulo!\n");
                }
            } while (valor <= 0);

            contaBancaria.saldo += valor;
            printf("\nOperacao realizada com sucesso!\n");
            printf("Saldo Atual: %f\n", contaBancaria.saldo);

            fprintf(arquivo,"DEPOSITO\t%f\t%s\n", contaBancaria.saldo, _strdate( dateStr));

            break;
        case 3:
            // saldo
            printf("\n\tSALDO\n");
            printf("%s, Seu saldo atual eh: %f\n", contaBancaria.cliente.nome, contaBancaria.saldo);

            break;
        case 4:
            // sair
            sair = 1;

            break;
        default:
            printf("\nOpcao Invalida!\n");
        }
    }
    fclose(arquivo);

    return 0;
}
