/*
Aula 5 - Listas Ligadas Statica (Tamanho fixo do arranjo da estrutura)

Parecido com a lista sequencia, porém com algumas caracteriscas diferentes:
Com a lista ligada evitamos a necessidade de deslocamento de elementos dentro da estrutura para inserção
e exclusão.
- É um estrutura linear (cada elemento possui no máximo um predecesso e um sucessor)
- A ordem lógica dos elementos (a ordem vista pelo usuario) NÃO É A MESMA ORDEM FÍSICA
(em memória principal) dos elementos.
- Cada elemento precisa indicar quem é o seu sucessor
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define MAX 50
#define INVALIDO -1

typedef int TipoChave;

typedef struct
{
    TipoChave chave;
} Registro;

typedef struct
{
    Registro registro;
    int prox;
} Elemento;

typedef struct
{
    Elemento elementos[MAX];
    int inicio; //indice do primeiro elemento valido
    int dispo //indice do primeiro elemento disponível
} Lista;

/*
    Passos para inicializar a estrutura:
    - Colocar todos os elementos na "lista" de disponíveis;
    - Acertar a variável dispo (primeiro item disponível);
    - Acertar a variável inicio (para indicar que não hánenhum item válido);
*/
void inicializar(Lista *lista)
{
    //Cada elemento indica seu sucessor com o próximo indice.
    for (int i = 0; i < MAX - 1; i++)
        lista->elementos[i].prox = i + 1;
    
    //Ultimo elemento não aponta para ninguém
    lista->elementos[MAX - 1].prox = INVALIDO;
    //indica que não existe elementos validos. Ou seja lista vazia
    lista->inicio = INVALIDO;
    //indica que a primeira posição com espaço disponível é o indice 0.
    lista->dispo = 0; // indice disponível
}

/*
    Para saber a quantidade de elementos na estrura, percorremos a estrutura começando no primiro 
    elemento, e somando 1 para cada iteração, e apontando para o seu sucessor, até que encotramos o elemento
    com o proxima com valir Invalido indicando que não existe elementos depois dele.
 */
int tamanho(Lista *lista)
{
    int i = lista->inicio;
    int tam = 0;
    while (i != INVALIDO)
    {
        tam++;
        i = lista->elementos[i].prox;
    }
    return tam;
}

void exibir(Lista *lista)
{
    int i = lista->inicio;
    printf("Iniciando listagem dos dados...\n");
    while (i != INVALIDO)
    {
        printf("Registro: %i\n", lista->elementos[i].registro.chave);
        i = lista->elementos[i].prox;
    }
    printf("Fim...\n");
}

/*
    Percorre a estrutura buscando a chave indicada, como a estrutura estará ordenada não será necessário
    percorrer toda a lista (em alguns casos), indicaremos uma condição no loop onde se o valor iterado 
    no momento for maior que a chave procurada o loop sera encerrado, indicando que não foi encontrado
    o elemento.
 */
int buscaSequencial(Lista *lista, TipoChave chave)
{
    int i = lista->inicio;
    while (i != INVALIDO && lista->elementos[i].registro.chave < chave)
        i = lista->elementos[i].prox;

    if (i != INVALIDO && lista->elementos[i].registro.chave == chave)
        return i;

    return INVALIDO;
}

/*
    Retorna o primeiro indice de posição disponível e reatribui o indice da próxima posição
    disponível.
*/
int obterNo(Lista *lista)
{
    int primeiroDisp = lista->dispo;
    if (primeiroDisp != INVALIDO)
        lista->dispo = lista->elementos[primeiroDisp].prox;

    return primeiroDisp;
}

bool inserirElementoOrd(Lista *lista, Registro reg)
{
    //Se não existe elemento disponível, retorna false. Lista cheia
    if (lista->dispo == INVALIDO)
        return false;

    //Percorre a estrutura até encontrar o primeiro elemento menor que a chave a ser adicionada
    //capturando quem é o elemento antecessor
    int ant = INVALIDO;
    int atu = lista->inicio;
    while (atu != INVALIDO && lista->elementos[atu].registro.chave < reg.chave)
    {
        ant = atu;
        atu = lista->elementos[atu].prox;
    }

    // valida se elento já existe, e não insere (Apenas caso não queira iserir elementos duplicados)
    if (atu != INVALIDO && lista->elementos[atu].registro.chave == reg.chave)
        return false;

    //Obtem o primeiro indice disponível
    atu = obterNo(lista);
    //Insere o registro na posição disponível
    lista->elementos[atu].registro = reg;
    
    //Valida se existe elemento anterior a posição inserida
    if (ant == INVALIDO)
    {
        //Caso não.
        //O proximo elemento do registro inserido será o primeiro elemento da estrutura, ja que 
        //Não existe nenhum item antes dele.
        lista->elementos[atu].prox = lista->inicio;

        //Aponta o elemento inserido como sendo o primeiro da lista.
        lista->inicio = atu;
    }
    else
    {
        //Caso exista elementos anteriores
        //O proximo elemento do elemento atual aponta para o proximo elemento do elemento anterior;
        lista->elementos[atu].prox = lista->elementos[ant].prox;
        //O proximo elemento do anterior aponta para o novo registro inserido
        lista->elementos[ant].prox = atu;
    }
    return true;
}

void devolverNo(Lista *lista, int key){
    lista->elementos[key].prox = lista->dispo;
    lista->dispo = key; 
}

void reinicializar(Lista *l){
    inicializar(l);
}

bool excluir(Lista *lista, TipoChave chave)
{
    int ant = INVALIDO;
    int atu = lista->inicio;
    while (atu != INVALIDO && lista->elementos[atu].registro.chave < chave)
    {
        ant = atu;
        atu = lista->elementos[atu].prox;
    }

    if(atu==INVALIDO || lista->elementos[atu].registro.chave!=chave) return false;
    if(ant == INVALIDO) lista->inicio = lista->elementos[atu].prox;
    else lista->elementos[ant].prox = lista->elementos[atu].prox;

    devolverNo(lista, atu);
    return true;
}


int main(int argc, char const *argv[])
{
    srand(time(NULL));

    Lista lista;
    inicializar(&lista);
    for (int i = 0; i < 50; i++)
    {
        Registro reg;
        reg.chave =  i + rand() % 101;
        inserirElementoOrd(&lista,reg);
    }
    exibir(&lista);

    excluir(&lista, lista.elementos[10].registro.chave);

    exibir(&lista);
    
    return 0;
}
