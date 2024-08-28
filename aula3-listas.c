/*
Aula 3 - Lista Linear

São estruturas de dados na qual cada elemento é precedido por um elemento e sucedido por outro
(exceto o primeiro que não um predecessor e o ultimo que não tem um sucessor).
Os elementos estão em uma determinada ordem (por exemplo, a ordem de inserção ou por uma determinada chave)


Lista Linear Sequencial
 É uma lista na qual a ordem lógica dos elementos (a ordem vista pelos usuarios) é a mesma ordem física
 (em memória principal) dos elementos.
 Isto é, elementos vizinhos na lista estara em posições vizinhas na memória


 Modelgagem:
 Modelaremos utilizando um arrajo de registros;
 Registros conterão as informações de intersse do usuario;
 Nosso arranjo tera um tamanho fixo e controlaremos o numero de elementos com uma variavel adicional.


FUNÇÕES
Inicializar a estrutura
Retornar a quantidde de elementos validos
Exibir os elementos
Buscar
Inserir
Excluir
Rinicializar
*/
#include <stdio.h>
#include <stdbool.h>
#define MAX 50

typedef int KEY;

typedef struct
{
    KEY chave;

} Registro;

typedef struct
{
    Registro registros[MAX];
    int Count;
} Lista;

void inicializar(Lista *lista)
{
    lista->Count = 0;
}

int tamanaho(Lista *lista)
{
    return lista->Count;
}

void exibirTodos(Lista *lista)
{
    printf("Lista \" ");
    for (int i = 0; i < lista->Count; i++)
    {
        printf("Chave: %i\n", lista->registros[i].chave);
    }

    printf("\"\n");
}

int buscarSequencia(Lista *lista, KEY chave)
{
    int i = 0;
    while (i < lista->Count)
    {
        if (chave == lista->registros[i].chave)
            return i;
        else
            i++;
    }
    return -1;
}

int buscaSentinela(Lista *lista, KEY chave){
    int i =0;
    //insere o elemento buscado no sentinela (Ultima posição após o elemento valido)
    lista->registros[lista->Count].chave = chave;

    while (i != lista->registros[i].chave) i++;
    
    if(i == lista->Count) return -1;
    
    return i;    
}

bool inserirOrdenado(Lista *lista, Registro registro){
    if(lista->Count == MAX) return false;
    int j;
    for (j = lista->Count; j > 0 && j > registro.chave; j--)
    {
        lista->registros[j] =lista->registros[j-1];
    }
    lista->registros[j] = registro;
    lista->Count++;
}

int buscaBinaria(Lista *lista, KEY chave){
    int esq, dir, meio;
    esq=0;
    dir = lista->Count-1;

    while (esq <= dir)
    {
        meio = (esq + dir) / 2;
        if(chave == meio) return meio;
        if(chave > meio) esq = meio +1;
        else dir = meio -1;    
    }
    return -1;
}

bool inserirElemento(Lista *lista, Registro registro, int pos)
{

    if (lista->Count == MAX || pos < 0 || pos > lista->Count)
        return false;

    int j;
    for (j = lista->Count; j > pos; j--)
    {
        lista->registros[j] = lista->registros[j - 1];
    }
    lista->registros[pos] = registro;
    lista->Count++;
    return true;
}

bool excluirComBuscaSequencial(Lista *lista, KEY chave)
{
    int pos, j;
    pos = buscarSequencia(lista, chave);
    if (pos == -1)
        return false;

    for (j = pos; j < lista->Count; j++)
    {
        lista->registros[j] = lista->registros[j + 1];
    }
    lista->Count--;
    return true;
}

bool excluirComBuscaBinaria(Lista *lista, KEY chave)
{
    int pos, j;
    pos = buscaBinaria(lista, chave);
    
    if (pos == -1)
        return false;

    for (j = pos; j < lista->Count; j++)
        lista->registros[j] = lista->registros[j + 1];
    
    lista->Count--;
    return true;
}


void reiniciar(Lista *lista)
{
    lista->Count = 0;
}

int main()
{
    Lista list;

    inicializar(&list);

    Registro reg;
    reg.chave = 1;
    inserirElemento(&list, reg, 0);

    exibirTodos(&list);
    
    for (int i = 2; i <= 100; i++)
    {
        Registro regi;
        regi.chave = i;
        inserirElemento(&list, regi, i-1);   
    }

    exibirTodos(&list);

    excluir(&list, (KEY)5);
   
    exibirTodos(&list);

    return 0;
}
