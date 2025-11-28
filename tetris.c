#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5

/*
    Struct Peca:
    Representa cada peça do Tetris Stack com:
        - nome: caractere ('I', 'O', 'T', 'L')
        - id: número único indicando ordem de criação
*/
typedef struct {
    char nome;
    int id;
} Peca;

/*
    Função gerarPeca:
    Cria automaticamente uma nova peça com tipo aleatório.
*/
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];  // uma das quatro formas
    nova.id = id;
    return nova;
}

/*
    Função exibirFila:
    Mostra todas as peças presentes na fila circular.
*/
void exibirFila(Peca fila[], int frente, int tras, int quantidade) {
    printf("\nFila de peças:\n");

    if (quantidade == 0) {
        printf("[vazia]\n");
        return;
    }

    int i = frente;
    for (int count = 0; count < quantidade; count++) {
        printf("[%c %d] ", fila[i].nome, fila[i].id);
        i = (i + 1) % TAM_FILA;  // avanço circular
    }
    printf("\n");
}

/*
    Função enqueue:
    Insere nova peça ao final da fila circular.
*/
void enqueue(Peca fila[], int *frente, int *tras, int *quantidade, Peca nova) {
    if (*quantidade == TAM_FILA) {
        printf("\nA fila está cheia! Não é possível inserir nova peça.\n");
        return;
    }

    fila[*tras] = nova;
    *tras = (*tras + 1) % TAM_FILA;
    (*quantidade)++;

    printf("\nPeça [%c %d] inserida na fila.\n", nova.nome, nova.id);
}

/*
    Função dequeue:
    Remove a peça da frente da fila.
*/
void dequeue(Peca fila[], int *frente, int *tras, int *quantidade) {
    if (*quantidade == 0) {
        printf("\nA fila está vazia! Nenhuma peça para jogar.\n");
        return;
    }

    Peca removida = fila[*frente];
    *frente = (*frente + 1) % TAM_FILA;
    (*quantidade)--;

    printf("\nPeça jogada: [%c %d]\n", removida.nome, removida.id);
}

int main() {
    srand(time(NULL));

    Peca fila[TAM_FILA];  // fila circular
    int frente = 0, tras = 0, quantidade = 0;
    int geradorID = 0;    // controla IDs das peças

    // Inicializar a fila com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(fila, &frente, &tras, &quantidade, gerarPeca(geradorID++));
    }

    int opcao;

    do {
        exibirFila(fila, frente, tras, quantidade);

        printf("\n=== Menu ===\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dequeue(fila, &frente, &tras, &quantidade);
                break;

            case 2:
                enqueue(fila, &frente, &tras, &quantidade, gerarPeca(geradorID++));
                break;

            case 0:
                printf("\nEncerrando o sistema...\n");
                break;

            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
