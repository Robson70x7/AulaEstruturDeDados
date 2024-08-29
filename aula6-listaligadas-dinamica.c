/*
    Segue a mesma lógica da aula 5 porém agora ao invéz de ter um tamanho fixo da estrutura, para cada
    inserção/exclusão sera alocado/desalocado um espaço de memória para o novo registro.

    - Traz mais complexidade de implementação
    - Traz ganhos de gerenciamento de recurso de memória, ganhando desenpenho.
 */
#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

typedef int TipoChave;

typedef struct {
    TipoChave chave;
}Registro;

typedef struct self{
    Registro reg;
    struct self *prox; //recebe o ponteiro para a proxima estrutura
}Elemento;

typedef Elemento *PONT;

typedef struct{
    PONT inicio;
}Lista;

void inicialziar(Lista *lista){
    /*
    Como não existe uma tamanho fixo alocado inicialmente, appenas é necessário indicar que o prmeiro
    elemento valido não existe.
    */
    lista->inicio = NULL;
}

int tamanho(Lista *lista){
    int tam = 0;
    int item = lista->inicio;
    while (item != NULL)
    {
        tam++;
        item = lista->inicio->prox;
    }
    return tam;
}

void exibir(Lista *lista){
    PONT item = lista->inicio;
    printf("Exibindo itens da lista:\n");
    while (item != NULL)
    {
        printf("Item: %i\n", item->reg.chave);
        item = item->prox;
    }
    printf("Fim\n");
}

PONT busca(Lista *lista, TipoChave chave, PONT *ant){
    PONT item = lista->inicio;
    *ant = NULL;
    while (item != NULL && item->reg.chave < chave){
        *ant = item;
        item = item->prox;
    }

    if(item != NULL && item->reg.chave == chave) return item;
    return NULL;
}

bool inserir(Lista *lista, Registro reg){
    PONT ant, item;

    item = busca(lista, reg.chave, &ant);

    if(item != NULL) return false;

    item = (PONT) malloc(sizeof(Elemento));
    item->reg = reg;

    if(ant==NULL){
        item->prox = lista->inicio;
        lista->inicio = item;
    }else{

        item->prox = ant->prox;
        ant->prox = item;
    }
    return true;
}

bool excluir(Lista *lista, TipoChave chave){
    PONT ant, item;

    item = busca(lista, chave, &ant);

    if(item == NULL) return false;

    if(ant == NULL){
        lista->inicio = item->prox;
    }else{
        ant->prox = item->prox;
    }
    free(item);
    return true;
}
void reinicializar(Lista *lista){
    PONT item = lista->inicio;
    while (item != NULL) {
        PONT del = item;
        item = item->prox;
        free(del); 
    }
    lista->inicio = NULL;
}

int main(int argc, char const *argv[])
{
    Lista lista;
    inicialziar(&lista);

    for (int i = 0; i < 10; i++)
    {
        Registro reg;
        reg.chave = i+2;
        inserir(&lista, reg);
    }
    exibir(&lista);
    excluir(&lista,(TipoChave)5);    
    exibir(&lista);


    return 0;
}








