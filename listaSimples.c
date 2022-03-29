#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data
{
    int dia;
    int mes;
    int ano;
}Data;

typedef struct estudante
{
    char registro[10];
    char nome[40];
    Data aniversario;
    float media;
    struct estudante *next;
}Estudante;

void liberaMemoria(Estudante *s)
{
    Estudante *aux;
    aux = s;
    while (aux != NULL)
    {
        s = aux->next;
        free(aux);
        printf("-");
        aux = s;
    }
    printf("\n\n");
}

Data defineData(int d, int m, int a){
    Data aniversario;
    aniversario.dia = d;
    aniversario.mes = m;
    aniversario.ano = a;
    return aniversario;
}


Estudante *inserirEstudante(Estudante *primeiro)
{
    char nome[40];
    float media;
    int d, m, a;
    char registro[10];
    Estudante *s;

    s = (Estudante*)malloc(sizeof(Estudante));
    Estudante *aux = primeiro;
    scanf(" %s", registro);
    scanf(" %s", nome);
    scanf("%d/%d/%d", &d, &m, &a);
    scanf("%f", &media);

    Data aniversario = defineData(d,m,a);
    s->media = media;
    strcpy(s->nome, nome);
    strcpy(s->registro, registro);
    s->aniversario = aniversario;
    s->next = NULL;

    if (primeiro == NULL)
        return s;

    for (; aux != NULL; aux = aux->next)
    {
        if (aux->next == NULL)
        {
            aux->next = s;
            return primeiro;
        }
    }
    return primeiro;
}

Estudante *deletaEstudante(Estudante *primeiro)
{
    char registro[10];
    scanf(" %s", registro);

    Estudante *aux = primeiro;
    Estudante *prev = primeiro;
    if (primeiro == NULL)
    {
        printf("Lista está vazia!\n");
        return primeiro;
    }
    
    while(aux != NULL){
        if (strcmp(aux->registro, registro) == 0){
            if (aux == primeiro){
                primeiro = aux ->next;
                free(aux);
                prev = primeiro;
                aux = prev;
            }
            else{
                prev->next = aux->next;
                free(aux);
                aux = prev->next;
            }
        }
        else{
        prev = aux;
        aux = aux->next;
        }
        
    }
    return primeiro;
}

void printEstudantes(Estudante *primeiro)
{
    Estudante *aux = primeiro;
    if (primeiro == NULL)
    {
        printf("Lista está vazia!\n");
        return;
    }
    for (; aux != NULL; aux = aux->next)
    {
        printf("%s, %s, %d/%d/%d, %.2f\n", aux->registro, aux->nome, aux->aniversario.dia, aux->aniversario.mes, aux->aniversario.ano, aux->media);
    }
}

void estudanteSentidoInverso(Estudante *f)
{
    if (f == NULL)
    {
        return;
    }
        estudanteSentidoInverso(f->next);
        printf("%s, %s, %d/%d/%d, %.2f\n", f->registro, f->nome, f->aniversario.dia, f->aniversario.mes, f->aniversario.ano, f->media);
    
}

void contaElementos(Estudante *primeiro){
    if (primeiro == NULL){
        printf("Lista está vazia!\n");
        return;
    }

    Estudante* aux;
    int contador = 0;

    for(aux = primeiro; aux != NULL; aux = aux->next){
        contador++;
    }
    printf("%d\n", contador);
}


int main()
{   
    Estudante *primeiro = NULL;
    int opcao;
    
    scanf("%d", &opcao);
    do
    {
        switch (opcao)
        {
        case 1:
            primeiro = inserirEstudante(primeiro);
            break;
        case 2:
            primeiro = deletaEstudante(primeiro);
            break;
        case 3:
            printEstudantes(primeiro);
            break;
        case 4:

        if(primeiro == NULL){
            printf("Lista está vazia!\n");
        }
            estudanteSentidoInverso(primeiro);
            break;
        case 5:
            contaElementos(primeiro);
            break;
        case 0:
            break;
        }

        scanf("%d", &opcao);
    } while (opcao != 0);
    liberaMemoria(primeiro);

    return 0;
}