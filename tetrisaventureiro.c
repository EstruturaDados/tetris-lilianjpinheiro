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

typedef struct {
    Peca itens[MAX];
    int topo;
} Pilha;

void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

// forward declaration
void renumerarFila(Fila *f);

void inserirFila(Fila *f, Peca p) {
    if (f->total == MAX) {
        printf("Fila cheia! Não é possível inserir.\n");
        return;
    }
    p.id = f->total + 1;
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
    // renumerar após alteração para garantir ids em ordem crescente
    renumerarFila(f);
}

void inserirPilha(Pilha *p, Peca item) {
    if (p->topo == MAX - 1) {
        printf("Pilha cheia! Não é possível inserir.\n");
        return;
    }
    p->itens[++(p->topo)] = item;
}

void removerFila(Fila *f, Peca *p) {
    if (f->total == 0) {
        printf("Fila vazia! Não é possível remover.\n");
        return;
    }
    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
    // renumerar após remoção
    renumerarFila(f);
}

void removerPilha(Pilha *p, Peca *item) {
    if (p->topo == -1) {
        printf("Pilha vazia! Não é possível remover.\n");
        return;
    }
    *item = p->itens[(p->topo)--];
}

void mostrarFila(Fila *f) {
    printf("Fila (total=%d): ", f->total);
    if (f->total == 0) {
        printf("[vazia]");
    } else {
        for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
            printf("[%s, %d] ", f->itens[idx].nome, f->itens[idx].id);
        }
    }
    printf("\n");
}

void mostrarPilha(Pilha *p) {
    printf("Pilha de reserva (total=%d): ", p->topo + 1);
    if (p->topo == -1) {
        printf("[vazia]");
    } else {
        for (int i = 0; i <= p->topo; i++) {
            printf("[%s, %d] ", p->itens[i].nome, p->itens[i].id);
        }
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

void renumerarFila(Fila *f) {
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
        f->itens[idx].id = i + 1;
    }
}

void reservarPeca(Fila *f, Pilha *p, Peca *reserva) {
    if (f->total == 0) {
        printf("Fila vazia! Não é possível reservar.\n");
        return;
    }
    *reserva = f->itens[f->inicio];
    removerFila(f, reserva);
    inserirPilha(p, *reserva);
    printf("Peça reservada: [%s, %d]\n", reserva->nome, reserva->id);
}

void usarPecaReserva(Fila *f, Pilha *p) {
    if (p->topo == -1) {
        printf("Nenhuma peça reservada!\n");
        return;
    }
    Peca reserva;
    removerPilha(p, &reserva);
    inserirFila(f, reserva);
    printf("Peça reserva usada: [%s, %d]\n", reserva.nome, reserva.id);
}



int main() {
    Fila fila;
    inicializarFila(&fila);
    srand((unsigned)time(NULL));
    preencherFilaInicial(&fila, 5);

    int opcao;
    Peca removida;
    Pilha pilhaReserva;

    inicializarPilha(&pilhaReserva);

    do {

        printf("\n================================");
        printf("\n      TETRIS STACK - MENU\n");
        printf("\n================================\n");

        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reserva \n");
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
                    Peca novaPeca;
                    char nomes[] = {'I', 'O', 'T', 'L'};
                    gerarPeca(&novaPeca, nomes[rand() % 4], 0);
                    inserirFila(&fila, novaPeca);
                    printf("Peça gerada e inserida na fila!\n");
                    mostrarFila(&fila);
                    mostrarPilha(&pilhaReserva);
                }
                break;

            case 2:
                if (fila.total == 0) {
                    printf("Fila vazia! Não é possível reservar.\n");
                } else {
                    Peca pecaReserva = { .id = 0 }; // Inicializa a peça reserva com id 0
                    reservarPeca(&fila, &pilhaReserva, &pecaReserva);
                    mostrarFila(&fila);
                    mostrarPilha(&pilhaReserva);
                }
                break;

            case 3:
                if (pilhaReserva.topo == -1) {
                    printf("Pilha de reservas vazia!\n");
                } else {
                    usarPecaReserva(&fila, &pilhaReserva);
                    mostrarFila(&fila);
                    mostrarPilha(&pilhaReserva);
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