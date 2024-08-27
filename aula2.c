#include <stdio.h>
#include <malloc.h>
#define alturaMaxim 256


typedef struct 
{
    float Peso, Altura;
}PesoAltura;

int main(){
    //Ponteiros
    int x = 25; //Uma variavel alocada na memoria, x representa o valor final da memoria
    int* y = &x; // o simbolo * após o tipo representa que é uma variavel do tipo ponteiro,
    // guarda o endereço de memoria onde encontra o valor final. 
    //O simbolo & significa que queremos obter o endenreço da memoria e não o valor armazenado
    *y = 30; //O simbolo * antes da variavel de tipo ponteiro, representa que o valor informado deve ser
    //alterado na fonte onde o endereço de momeria armazenado na variavel aponta.
    PesoAltura pesoAlt;
    pesoAlt.Peso = 65.15;
    pesoAlt.Altura = 1.68;

    PesoAltura* pesoalt2 = (PesoAltura*) malloc(sizeof(PesoAltura));
    pesoalt2->Altura = 20;
    pesoalt2->Peso = 35;

    printf("Seu peso é %.2f e sua altura é %.2f\n", pesoAlt.Peso, pesoAlt.Altura); //Variavel de tipo de estrutura tem seus valores acessados atravez do sinal '.'
    printf("Seu peso é %.2f e sua altura é %.2f", pesoalt2->Peso, pesoalt2->Altura); //Variavel de tipo de ponteiro tem seus valores acessados atravez do sinal '->'
    
    return 0;
}
