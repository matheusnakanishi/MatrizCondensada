#include <stdio.h>
#include <stdlib.h>

typedef struct NO no;

struct NO{
    int valor;
    int linha;
    int coluna;
    struct NO *prox;
};

no *criar();
void imprimir_lista(no *lista);
void imprimir_matriz(no *lista);
no *inserir_fim(no *lista, int dado, int l, int c);
no *soma(no *lista1, no *lista2, no* lista_soma);
no *mult(no *lista1, no *lista2, no *lista_mult);
void soma_inferior(no *lista);
no *leitura(no *lista, FILE *file);

int main()
{
    FILE *file = fopen("matrizes.txt", "r");
    if(file == NULL)
    {
        printf("Erro em abrir o arquivo");
    }
    
    no *lista1 = NULL;
    no *lista2 = NULL;
    no *lista_soma = NULL;
    no *lista_mult = NULL;
    
    int i, j, valor;
    
    lista1 = leitura(lista1,file);
    lista2 = leitura(lista2,file);
    
    //imprimir_lista(lista1);
    //imprimir_matriz(lista1);
    //lista_soma = soma(lista1,lista2,lista_soma);
    //imprimir_matriz(lista2);
    lista_mult = mult(lista1,lista2,lista_mult);
    imprimir_matriz(lista_mult);
    //soma_inferior(lista1);
    //imprimir_lista(lista_mult);
    
    
    

    return 0;
}

no *leitura(no *lista, FILE *file)
{
    int i, j, valor;

    for(i = 0; i < 15; i++)
    {
        for(j = 0; j < 15; j++)
        {
            fscanf(file,"%d",&valor);
            if(valor != 0)
            {
                lista = inserir_fim(lista,valor,i,j);
            }
        }
    }

    return lista;
}

no *criar()
{
    no *novo = (no *)malloc(sizeof(no));
    return novo;
}

no *inserir_fim(no *lista, int dado, int l, int c)
{
    no *novo = criar();
    novo->valor = dado;
    novo->linha = l;
    novo->coluna = c;
    if(lista == NULL)
    {
        lista = novo;
        novo->prox = NULL;
    }
    else
    {
        no *aux = lista;
        while(aux->prox != NULL)
        {
            aux = aux->prox;
        }
        novo->prox = NULL;
        aux->prox = novo;
    }
    return lista;
}

void imprimir_lista(no *lista)
{
    no *aux = lista;
    
    printf("Conteudo da Lista\n\n");

    while(aux != NULL)
    {
        printf("Valor: %d\nLinha: %d\nColuna: %d\n----------\n ",aux->valor,aux->linha,aux->coluna);
        aux = aux->prox;
    }
    
}

void imprimir_matriz(no *lista)
{
    no *aux = lista;
    int i, j;
    
    printf("Matriz Completa\n\n");
    
    for(i = 0; i < 15; i++)
    {
        for(j = 0; j < 15; j++)
        {
            if(aux->linha == i && aux->coluna == j)
            {
                printf("%d ", aux->valor);
                aux = aux->prox;
            }
            else
            {
                printf("0 ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

no *soma(no *lista1, no *lista2, no* lista_soma)
{
    int s;
    no *aux1 = lista1;
    no *aux2 = lista2;
    int i, j;
    
    for(i = 0; i < 15; i++)
    {
        for(j = 0; j < 15; j++)
        {
            s = 0;
            if(aux1->linha == i && aux1->coluna == j)
            {
                s += aux1->valor;
                aux1 = aux1->prox;
            }
            if(aux2->linha == i && aux2->coluna == j)
            {
                s += aux2->valor;
                aux2 = aux2->prox;
            }
            lista_soma = inserir_fim(lista_soma,s,i,j);
        }
    }
    return lista_soma;
}

no *mult(no *lista1, no *lista2, no *lista_mult)
{
    no *aux1 = lista1;
    no *aux2 = lista2;
    int i, j, k;
    int s = 0;
    //char check = 't';
    
    for(i = 0; i < 15; i++)
    {
        for(j = 0; j < 15; j++)
        {
            for(k = 0; k < 15; k++)
            {
                while(aux1->linha != i || aux1->coluna != k)
                {
                    if(aux1->linha > i)
                    {
                        aux1->valor = 0;
                        break;
                    }
                    aux1 = aux1->prox;
                    
                }
                
                while(aux2->linha != k || aux2->coluna != j)
                {
                   if(aux2->linha > k)
                    {
                        aux2->valor = 0;
                        break;
                    }
                    aux2 = aux2->prox;
                    
                }
                
                s += aux1->valor * aux2->valor;
                
                aux2 = lista2;
            }
            
            lista_mult = inserir_fim(lista_mult,s,i,j);
            s = 0;
            aux1 = lista1;
        }
    }
    
    return lista_mult;
}

void soma_inferior(no *lista)
{
    no *aux = lista;
    int soma = 0;
    
    while(aux != NULL)
    {
        if(aux->linha > aux->coluna)
        {
            soma += aux->valor;
        }
        aux = aux->prox;
    }
    
    printf("Soma do Triangulo Inferior: %d",soma);
}
