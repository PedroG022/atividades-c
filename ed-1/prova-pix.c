#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// ================================
// Other constants
// ================================

#define WINDOWS false
#define DEBUG false

// ================================
// Size constants
// ================================

#define MAX_STR 100
#define MAX_CONTAS 100
#define MAX_CHAVES 100

// ================================
// Menu constants
// ================================

#define MENU_SEPARATOR "================================"

#define MENU_PRINCIPAL 1
#define MENU_CONSULTA 2
#define MENU_PIX 3

#define MENU_SAIR 0
#define MENU_DEBUG 9

#define MENU_P_CADASTRAR 1
#define MENU_P_CONSULTAR 2

#define MENU_C_CADASTRAR_CHAVE 1
#define MENU_C_TRANSFERIR 2

#define CHAVE_CPF 1
#define CHAVE_TELEFONE 2
#define CHAVE_ALEATORIO 3

// ================================
// Structs
// ================================

typedef struct ContaBancaria {
    int numConta;
    char nomeTitular[MAX_STR];
    float limiteCredito;
    float saldoAtual;
} ContaBancaria;

typedef struct ChavesPix {
    int tipoChave;
    int chave;
    int numConta;
} ChavesPix;

// ================================
// Utils
// ================================

void clear() {
    if (WINDOWS)
        system("cls");
    else
        system("clear");
}

void separator() {
    printf("%s\n", MENU_SEPARATOR);
}

void lineBreak() {
    printf("\n");
}

void unknown() {
    printf("Opção desconhecida!\n");
}

// ================================
// Struct utils
// ================================

int encontrarConta(ContaBancaria contas[], int quantidadeContas, int numeroConta) {
    for (int atual = 0; atual < quantidadeContas; atual++)
        if (contas[atual].numConta == numeroConta)
            return atual;

    return -1;
}

int encontrarChavePixConta(ChavesPix chaves[], int quantidadeChaves, int tipo, int chave, int numConta) {
    for (int atual = 0; atual < quantidadeChaves; atual++) {
        if (chaves[atual].tipoChave == tipo && chaves[atual].chave == chave && chaves[atual].numConta == numConta)
            return atual;
    }

    return -1;
}

int encontrarChavePix(ChavesPix chaves[], int quantidadeChaves, int tipo, int chave) {
    for (int atual = 0; atual < quantidadeChaves; atual++) {
        if (chaves[atual].tipoChave == tipo && chaves[atual].chave == chave)
            return atual;
    }

    return -1;
}


void mostrarConta(ContaBancaria conta) {
    printf("Número: %d\n", conta.numConta);
    printf("Titular: %s\n", conta.nomeTitular);
    printf("Limite: R$%.2f\n", conta.limiteCredito);
    printf("Saldo: R$%.2f\n", conta.saldoAtual);
}

void mostrarChave(ChavesPix chave) {
    printf("Tipo: %d\n", chave.tipoChave);
    printf("Chave: %d\n", chave.chave);
    printf("Número da conta: %d\n", chave.numConta);
}

// ================================
// Menus
// ================================

int menu(int opcao) {
    int resposta;

    switch (opcao) {
        case MENU_PRINCIPAL:
            printf("%d - Cadastrar\n", MENU_P_CADASTRAR);
            printf("%d - Consultar\n", MENU_P_CONSULTAR);

            if (DEBUG)
                printf("%d - DEBUG\n", MENU_DEBUG);
            break;

        case MENU_CONSULTA:
            printf("%d - Cadastrar chave Pix\n", MENU_C_CADASTRAR_CHAVE);
            printf("%d - Realizar transferência\n", MENU_C_TRANSFERIR);
            break;

        case MENU_PIX:
            printf("%d - Utilizar CPF\n", CHAVE_CPF);
            printf("%d - Utilizar Telefone\n", CHAVE_TELEFONE);
            printf("%d - Utilizar chave aleatória\n", CHAVE_ALEATORIO);
            break;

        default:
            printf("Menu invalido!");
    }

    printf("%d - Sair\n", MENU_SAIR);

    separator();

    printf("Escolha a opção desejada: ");
    scanf("%d", &resposta);

    return resposta;
}

void menuDebug(ContaBancaria contas[], int quantidadeContas, ChavesPix chaves[], int quantidadeChaves) {
    clear();

    printf("Conta(s) cadastrada(s): %d\n", quantidadeContas);
    printf("Chave(s) cadastrada(s): %d\n", quantidadeChaves);

    lineBreak();
    printf("Contas\n");
    separator();

    for (int atual = 0; atual < quantidadeContas; atual++) {
        mostrarConta(contas[atual]);
        separator();
    }

    lineBreak();
    printf("Chaves\n");
    separator();

    for (int atual = 0; atual < quantidadeChaves; atual++) {
        mostrarChave(chaves[atual]);
        separator();
    }
}

ContaBancaria menuCadastrarConta(int quantidadeContas) {
    clear();

    ContaBancaria conta;
    conta.numConta = quantidadeContas;

    printf("Cadastrar conta\n");
    separator();

    printf("Insira o nome do titular: ");
    scanf("%s", conta.nomeTitular);

    printf("Insira o limite de crédito: R$");
    scanf("%f", &conta.limiteCredito);

    printf("Insira o saldo atual: R$");
    scanf("%f", &conta.saldoAtual);

    lineBreak();

    printf("Conta cadastrada com sucesso!\n");
    printf("O número desta conta é: %d\n", conta.numConta);

    lineBreak();

    return conta;
}

void menuCadastroPix(ChavesPix chaves[], int *quantidadeChaves, int numConta) {
    srand(time(NULL));

    clear();
    printf("Cadastrar chave pix\n");
    separator();

    ChavesPix chave;
    chave.numConta = numConta;
    chave.tipoChave = menu(MENU_PIX);

    switch (chave.tipoChave) {
        case CHAVE_CPF:

            printf("Insira o CPF: ");
            scanf("%d", &chave.chave);

            if (encontrarChavePixConta(chaves, *quantidadeChaves, CHAVE_CPF, chave.chave, numConta) >= 0) {
                printf("Esta chave já existe!\n");
                return;
            }

            if (encontrarChavePix(chaves, *quantidadeChaves, CHAVE_CPF, chave.chave) >= 0) {
                printf("Uma mesma chave com este CPF já foi cadastrada!\n");
                return;
            }

            break;
        case CHAVE_TELEFONE:
            printf("Insira o telefone: ");
            scanf("%d", &chave.chave);

            if (encontrarChavePixConta(chaves, *quantidadeChaves, CHAVE_TELEFONE, chave.chave, numConta) >= 0) {
                printf("Esta chave já existe!\n");
                return;
            }

            if (encontrarChavePix(chaves, *quantidadeChaves, CHAVE_TELEFONE, chave.chave) >= 0) {
                printf("Uma mesma chave com este telefone já foi cadastrada!\n");
                return;
            }
            break;
        case CHAVE_ALEATORIO:
            do { chave.chave = rand() % (9999 + 1 - 1000) + 1000; }
            while (encontrarChavePixConta(chaves, *quantidadeChaves, CHAVE_ALEATORIO, chave.chave, numConta) != -1);
            break;

        case MENU_SAIR:
            return;

        default:
            unknown();
            return;
    }

    chaves[*quantidadeChaves] = chave;
    *quantidadeChaves += 1;

    printf("A chave %d do tipo %d foi cadastrada com sucesso!\n", chave.chave, chave.tipoChave);
}

void menuTransferencia(ContaBancaria contas[], int quantidadeContas, ChavesPix chaves[], int quantidadeChaves,
                       int numContaOrigem) {
    clear();
    printf("Transferir\n");
    separator();

    int tipo;
    int chave;

    printf("Insira o tipo da chave desejada: ");
    scanf("%d", &tipo);

    printf("Insira a chave: ");
    scanf("%d", &chave);

    int conta = encontrarChavePix(chaves, quantidadeChaves, tipo, chave);

    if (conta == -1) {
        printf("Chave não encontrada!\n");
        return;
    }

    ChavesPix chaveAlvo = chaves[conta];
    ContaBancaria contaAlvo = contas[chaveAlvo.numConta];

    float valor;

    printf("Realizando transferência para %s.\n", contaAlvo.nomeTitular);
    printf("Insira a quantia desejada: R$");
    scanf("%f", &valor);

    if ((contas[numContaOrigem].saldoAtual - valor) < (0 - contas[numContaOrigem].limiteCredito)) {
        printf("Você não tem limite!\n");
        return;
    }

    contas[numContaOrigem].saldoAtual -= valor;
    contas[chaveAlvo.numConta].saldoAtual += valor;

    separator();

    printf("Transferência realizada com sucesso!\n");
    printf("Saldo atual: R$%.2f\n", contas[numContaOrigem].saldoAtual);

    separator();
}

void menuConsulta(ContaBancaria contas[], int quantidadeContas, ChavesPix chaves[], int *quantidadeChaves) {
    clear();

    printf("Consultar\n");
    separator();

    int numConta;
    ContaBancaria conta;

    printf("Insira o número da conta a ser consultado: ");
    scanf("%d", &numConta);

    if (encontrarConta(contas, quantidadeContas, numConta) == -1) {
        printf("Conta não encontrada!\n");
        return;
    }

    conta = contas[numConta];

    lineBreak();
    mostrarConta(conta);
    lineBreak();

    separator();

    switch (menu(MENU_CONSULTA)) {
        case MENU_C_CADASTRAR_CHAVE:
            menuCadastroPix(chaves, quantidadeChaves, numConta);
            break;

        case MENU_C_TRANSFERIR:
            menuTransferencia(contas, quantidadeContas, chaves, *quantidadeChaves, numConta);
            break;

        case MENU_SAIR:
            return;

        default:
            unknown();
    }
}


int main() {
    ContaBancaria contas[MAX_CONTAS];
    int quantidadeContas = 0;

    ChavesPix chaves[MAX_CHAVES];
    int quantidadeChaves = 0;

    while (true) {
        clear();
        printf("Banco\n");
        separator();

        switch (menu(MENU_PRINCIPAL)) {
            case MENU_P_CADASTRAR:
                contas[quantidadeContas] = menuCadastrarConta(quantidadeContas);
                quantidadeContas += 1;
                break;

            case MENU_P_CONSULTAR:
                menuConsulta(contas, quantidadeContas, chaves, &quantidadeChaves);
                break;

            case MENU_DEBUG:
                if (DEBUG)
                    menuDebug(contas, quantidadeContas, chaves, quantidadeChaves);
                else
                    unknown();
                break;

            case MENU_SAIR:
                return 0;

            default:
                unknown();
        }

        printf("Pressione ENTER para continuar...");
        setbuf(stdin, NULL);
        getchar();
    }

}