#include <stdio.h>
#include <stdlib.h>

#define ORDEM 2

typedef enum {false, true} bool; //false=0 true=1

typedef struct {
    int codCliente;
    char nome[100];
}clienteRegistro;

typedef struct {
    void ** ponteiros;
    int * chaves;
    struct node * pai;
    bool eFolha;
    int qtdChaves;
    char id_pag[20];
    FILE *arq;
    struct no * proximo; // Used for queue.
} no;


/*  ordem d determina o máximo e mínimo de entradas em cada nó.
*   cada nó/página tem no mínimo d registros e d+1 descendentes.
*   cada nó/página tem no máximo d*2 registros e d*2+1 descendentes.
*   se o nó for raíz, no mínimo 1 registro e 2 descendentes.


    No caso do trabalho de ordem 2,

    nó -> mín 2 registros e 3 descendentes.
    nó -> máx 4 registros e 5 descendentes.
    raíz -> mín 1 registro e 2 descendentes.
*/
int ordem = ORDEM;

/*  
    usado para imprimir a árvore começando da raíz, imprimindo cada nível em linhas separadas
    terminando nas folhas.
*/
no* fila = NULL;


// imprimir árvore
void enfileirar( no * novoNo ) {
	no * c;
	if (fila == NULL) {
		fila = novoNo;
		fila->proximo = NULL;
	}
	else {
		c = fila;
		while(c->proximo != NULL) {
			c = c->proximo;
		}
		c->proximo = novoNo;
		novoNo->proximo = NULL;
	}
}

no * tirarDaFila( void ) {
	no * n = fila;
	fila = fila->proximo;
	n->proximo = NULL;
    return n;
}

// imprime as folhas
void imprimirFolhas( no * raiz ) {
	int i;
	no * c = raiz;
	if (raiz == NULL) {
		printf("Empty tree.\n");
		return;
	}
	while (!c->eFolha)
		c = c->ponteiros[0];
	while (true) {
		for (i = 0; i < c->qtdChaves; i++) {
			printf("%d ", c->chaves[i]);
		}
		if (c->ponteiros[ordem - 1] != NULL) {
			printf(" | ");
			c = c->ponteiros[ordem - 1];
		}
		else
			break;
	}
	printf("\n");
}

int main (void) {
    FILE *pontArq;

    //criação de arquivos binários
    pontArq = fopen("metadados.bin", "wb");
    fclose(pontArq);
    pontArq = fopen("indice.bin", "wb");
    fclose(pontArq);
    pontArq = fopen("dados.bin", "wb");
    fclose(pontArq);
    printf("Arquivos criados com sucesso!\n");



}