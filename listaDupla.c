#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct Data
{
    int dia;
    int mes;
    int ano;
}data;

typedef struct Estudante
{
    char registro[10];
    char nome[40];
    data aniversarioDia;
    float media;
    struct Estudante *next;
    struct Estudante *prev;
}estudante;


typedef struct ControlaLista
{
    estudante *first;
    estudante *last;
}controlaLista;


void liberaMemoria(controlaLista lista)
{
    estudante *aux;
    aux = lista.first;
    while (aux != NULL)
    {
        lista.first = aux->next;
        free(aux);
        printf("*");
        aux = lista.first;
    }
    printf("\n\n");
}

data setaData(int d, int m, int a)
{
    data aniversarioDia;
    aniversarioDia.dia = d;
    aniversarioDia.mes = m;
    aniversarioDia.ano = a;
    return aniversarioDia;
}

controlaLista inserirEstudante(controlaLista lista)
{
    int d, m, a;
    estudante *s, new, *aux;
    char prev_registro[10];
    s = (estudante *)malloc(sizeof(estudante));
    scanf(" %s", prev_registro);
    scanf(" %s", new.registro);
    scanf(" %s", new.nome);
    scanf(" %d/%d/%d", &d, &m, &a);
    scanf(" %f", &new.media);

    new.aniversarioDia = setaData(d, m, a);
    *s = new;

    if (lista.first == NULL)
    {
        s->next = NULL;
        s->prev = NULL;
        lista.first = s;
        lista.last = s;
        return lista;
    }

    for (aux = lista.first; aux != NULL; aux = aux->next)
    {
        if (strcmp(aux->registro, prev_registro) == 0)
        {
            if(aux->next != NULL){
                aux->next->prev = s;
            }
            else{
                lista.last = s;
            }
            
            s->next = aux->next;
            s->prev = aux;
            aux->next = s;
            
            return lista;
        }
    }
   
    lista.first->prev = s;
    s->next = lista.first;
    s->prev = NULL;
    lista.first = s;
    
    return lista;
}

controlaLista deletaEstudante(controlaLista lista)
{
    char registro[10];
    scanf(" %s", registro);
    estudante *auxnext;
    estudante *aux = lista.first;
    if (lista.first == NULL)
    {
        printf("Lista vaiza!!\n");
        return lista;
    }

    while (aux != NULL)
    {
        if (strcmp(aux->registro, registro) == 0)
        {
            if (aux == lista.first)
            {
                lista.first = aux->next;
                lista.first->prev = NULL;
            }
            else if (aux == lista.last)
            {
                lista.last = aux->prev;
                lista.last->next = NULL;
            }
            else
            {
                aux->prev->next = aux->next;
                aux->next->prev = aux->prev;
            }
            auxnext=aux->next;
            free(aux);
            aux = auxnext;
        }
        else{
        aux=aux->next;
        }
    }
    return lista;
}

void prinEstudantes(controlaLista lista)
{
    estudante *aux;
    if (lista.first == NULL)
    {
        printf("Lista vaiza!!\n");
        return;
    }
    for (aux = lista.first; aux != NULL; aux = aux->next)
    {
        printf("%s, %s, %d/%d/%d, %.2f\n", aux->registro, aux->nome, aux->aniversarioDia.dia, aux->aniversarioDia.mes, aux->aniversarioDia.ano, aux->media);
    }
}

void prinEstudantesReverse(controlaLista lista)
{
    estudante *aux;
    if (lista.first == NULL)
    {
        printf("Lista vaiza!!\n");
        return;
    }
    for (aux = lista.last; aux != NULL; aux = aux->prev)
    {
        printf("%s, %s, %d/%d/%d, %.2f\n", aux->registro, aux->nome, aux->aniversarioDia.dia, aux->aniversarioDia.mes, aux->aniversarioDia.ano, aux->media);
    }
}

void contadorDeElementos(estudante *first)
{
   
    estudante *aux;
    int count = 0;
    for (aux = first; aux != NULL; aux = aux->next)
    {
        count++;
    }
    printf("%d\n", count);
}

controlaLista init_list()
{
    controlaLista lista;
    lista.first = NULL;
    lista.last = NULL;
    return lista;
}

int main()
{
    controlaLista lista = init_list();

    int opcao;

    scanf("%d", &opcao);
    do
    {
        switch (opcao)
        {
        case 1:
            lista = inserirEstudante(lista);
            break;

        case 2:
            lista = deletaEstudante(lista);
            break;
        case 3:
            prinEstudantes(lista);
            break;
        case 4:
            prinEstudantesReverse(lista);
            break;
        case 5:
            contadorDeElementos(lista.first);
            break;

        case 0:
            break;
        }

        scanf("%d", &opcao);
    } while (opcao != 0);
    liberaMemoria(lista);
    return 0;
}