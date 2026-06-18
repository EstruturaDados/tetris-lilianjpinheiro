#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Desafio Novato: Criação da fila de peças do Tetris Stack
typedef struct {
    char nome[2];
    int id;
} Peca;

#define MAX 5

typedef struct {
    Peca itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

void inserirFila(Fila *f, Peca p) {
    if (f->total == MAX) {
        printf("Fila cheia! Não é possível inserir.\n");
        return;
    }
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

void removerFila(Fila *f, Peca *p) {
    if (f->total == 0) {
        printf("Fila vazia! Não é possível remover.\n");
        return;
    }
    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
}

void mostrarFila(Fila *f) {
    printf("Fila: ");
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
        printf("[%s, %d] ", f->itens[idx].nome, f->itens[idx].id);
    }
    printf("\n");
}

void gerarPeca(Peca *p, char nome, int id) {
    p->nome[0] = nome;
    p->nome[1] = '\0';
    p->id = id;
}

void aleatorizarPeca(Peca pecas[], int n) {
    char nomes[] = {'I', 'O', 'T', 'L'};
    for (int i = 0; i < n; i++) {
        gerarPeca(&pecas[i], nomes[rand() % 4], i + 1);
    }
}

void preencherFilaInicial(Fila *f, int n) {
    if (n > MAX) n = MAX;
    char nomes[] = {'I', 'O', 'T', 'L'};
    for (int i = 0; i < n; i++) {
        Peca p;
        gerarPeca(&p, nomes[rand() % 4], i + 1);
        inserirFila(f, p);
    }
}




int main() {
    Fila fila;
    inicializarFila(&fila);
    srand((unsigned)time(NULL));
    preencherFilaInicial(&fila, 5);

    int opcao;
    Peca removida;

    do {

        printf("\n================================");
        printf("\n      TETRIS STACK - MENU\n");
        printf("\n================================\n");

        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("3 - Estado atual das peças \n");
        printf("0 - Sair\n");

        printf("\nEscolha: ");
        scanf("%d", &opcao);

        getchar();

        switch(opcao){

            case 1:
                if (fila.total == 0) {
                    printf("Fila vazia! Não é possível remover.\n");
                } else {
                    removerFila(&fila, &removida);
                    printf("Removida: [%s, %d]\n", removida.nome, removida.id);
                    mostrarFila(&fila);
                }
                break;

            case 2:
            {
                Peca novaPeca;
                char nomes[] = {'I', 'O', 'T', 'L'};
                gerarPeca(&novaPeca, nomes[rand() % 4], fila.total + 1);
                inserirFila(&fila, novaPeca); 
                printf("Peça gerada e inserida na fila!\n");
                mostrarFila(&fila);
                printf("Fila: [%d]\n", fila.total);
                break;
            }

            case 3:
            if (fila.total == 0) {
                printf("Fila vazia!\n");

            } else {
                mostrarFila(&fila);
                printf("Fila: [%d]\n", fila.total);
            }
            break;

            case 0: {
                printf("\nSaindo do jogo...\n");
                break;
            }
            default:
                printf("\nOpcao invalida!\n");

        }

    }while(opcao != 0);

    return 0;
}