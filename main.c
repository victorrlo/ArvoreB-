#include <stdio.h>
#include <stdlib.h>

#define ORDEM 2

typedef enum {false, true} bool; //false=0 true=1

typedef struct {
    int codCliente;
    char nome[100];
}clienteRegistro;

typedef struct no{
    void ** ponteiros;
    int * chaves;
    struct no * pai;
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
no * fila = NULL;


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

// imprime árvore cada nível por linha, com as chaves de cada nó e | separando-os.
void imprimirArvore( no * raiz ) {

	no * n = NULL;
	int i = 0;
	int pagina = 0;
	int novaPagina = 0;

	if (raiz == NULL) {
		printf("Árvore vazia.\n");
		return;
	}
	fila = NULL;
	enfileirar(raiz);
	while( fila != NULL ) {
		n = tirarDaFila();
		if (n->pai != NULL && n == n->pai->ponteiros[0]) {
			novaPagina = path_to_root( raiz, n );
			if (novaPagina != pagina) {
				pagina = novaPagina;
				printf("\n");
			}
		}
		for (i = 0; i < n->qtdChaves; i++) {
			printf("%d ", n->chaves[i]);
		}
		if (!n->eFolha)
			for (i = 0; i <= n->qtdChaves; i++)
				enfileirar(n->ponteiros[i]);
		printf("| ");
	}
	printf("\n");
}

//  mostra caminho da raíz até a folha, procurando pela chave. retorna folha da chave
no * achaFolha( no * raiz, int chave) {
	int i = 0;
	no * c = raiz;
	if (c == NULL) { 
        printf("Árvore vazia.\n");
		return c;
	}
	while (!c->eFolha) {
        printf("[");
        for (i = 0; i < c->qtdChaves - 1; i++)
            printf("%d ", c->chaves[i]);
        printf("%d] ", c->chaves[i]);
		i = 0;
		while (i < c->qtdChaves) {
			if (chave >= c->chaves[i]) i++;
			else break;
		}
		c = (no *)c->ponteiros[i];
    }
    printf("Folha [");
    for (i = 0; i < c->qtdChaves - 1; i++)
        printf("%d ", c->chaves[i]);
    printf("%d] ->\n", c->chaves[i]);
	return c;
}



// procura e retorna o registro dada determinada chave
clienteRegistro * busca( no * raiz, int chave) {
	int i = 0;
	no * c = achaFolha( raiz, chave);
	if (c == NULL) return NULL;
	for (i = 0; i < c->qtdChaves; i++)
		if (c->chaves[i] == chave) break;
	if (i == c->qtdChaves) 
		return NULL;
	else
		return (clienteRegistro *)c->ponteiros[i];
}
// acha o registro de dada chave e imprime
void buscaImprime(no * raiz, int chave) {
	clienteRegistro * r = busca(raiz, chave);
	if (r == NULL)
		printf("Registro não encontrado com chave %d.\n", chave);
	else 
		printf("Registro na %lx -- chave %d, value %d.\n",
		                (chave, r->codCliente));
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