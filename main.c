#include <stdio.h>
#include <stdlib.h>

int main (void) {
    FILE *pont_arq;

    //criação de arquivos binários
    pont_arq = fopen("metadados.bin", "w+b");
    fclose(pont_arq);
    pont_arq = fopen("indice.bin", "w+b");
    fclose(pont_arq);
    pont_arq = fopen("dados.bin", "w+b");
    fclose(pont_arq);
    printf("Arquivos criados com sucesso!\n");

    system("pause");

    return(0);
}