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
void limpar();
void liberar(no *lista);

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
    
    int i, j, valor, op, c;
    
    //Lendo as matrizes do arquivo e armazenando em listas
    lista1 = leitura(lista1,file);
    lista2 = leitura(lista2,file);
    fclose(file);

    //Atribuindo a soma e a multiplicacao das Matrizes A e B para Listas
    lista_soma = soma(lista1,lista2,lista_soma);
    lista_mult = mult(lista1,lista2,lista_mult);
    
    do
    {
        //menu
        printf("\n[1]Escrever Matriz Condensada\n[2]Escrever Soma das Matrizes A e B\n[3]Escrever Multiplicacao das Matrizes A e B\n[4]Soma dos elementos abaixo da diagonal principal da Matriz\n[5]Sair\n");
        scanf("%d",&op);

        switch (op)
        {
        case 1:
            limpar();
            printf("Escolha a Matriz:\n[1]A\n[2]B\n ");
            scanf("%d",&c);
            switch (c)
            {
            case 1:
                imprimir_lista(lista1);
                imprimir_matriz(lista1);
                break;
            case 2:
                imprimir_lista(lista2);
                imprimir_matriz(lista2);
                break;
            
            default:
                printf("Opcao invalida");
                break;
            }
            break;
        case 2:
            limpar();
            imprimir_lista(lista_soma);
            imprimir_matriz(lista_soma);
            break;
        case 3:
            limpar();
            imprimir_lista(lista_mult);
            imprimir_matriz(lista_mult);
            break;
        case 4:
            limpar();
            printf("Escolha a Matriz:\n[1]A\n[2]B\n[3]Soma\n[4]Multiplicacao\n");
            scanf("%d",&c);
            switch (c)
            {
            case 1:
                soma_inferior(lista1);
                break;
            case 2:
                soma_inferior(lista2);
                break;
            case 3:
                soma_inferior(lista_soma);
                break;
            case 4:
                soma_inferior(lista_mult);
                break; 
            default:
                printf("Opcao invalida");
                break;
            }
            break;
        case 5:
            liberar(lista1);
            liberar(lista2);
            liberar(lista_soma);
            liberar(lista_mult);
            printf("\nSaindo...\n\n");
            break;
        default:
            limpar();
            printf("Opcao invalida\n\n");
            break;
        }
    } while (op != 5);
    
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
    //aloca memoria
    no *novo = (no *)malloc(sizeof(no));
    return novo;
}

no *inserir_fim(no *lista, int dado, int l, int c)
{
    //insere uma celula no fim da lista
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
    //imprime informacoes da lista
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
            //verifica se a celula eh correta, senao, a celula nao existe, portanto o valor eh 0
            if(aux->linha == i && aux->coluna == j)
            {
                printf("%4d ", aux->valor);
                aux = aux->prox;
            }
            else
            {
                printf("   0 ");
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
    int i,j,k,soma;
    int A[15][15];
    int B[15][15];

    //atribuindo as listas para matrizes
    for (i = 0; i < 15; i++)
    {
        for (j = 0; j < 15; j++)
        {
            if (aux1 != NULL && aux1->linha == i && aux1->coluna == j)
            {
                A[i][j] = aux1->valor;
                aux1 = aux1->prox;
            }
            else
            {
                A[i][j] = 0;
            }

            if (aux2 != NULL && aux2->linha == i && aux2->coluna == j)
            {
                B[i][j] = aux2->valor;
                aux2 = aux2->prox;
            }
            else
            {
                B[i][j] = 0;
            }
            
        }
        
    }
    
    //multiplicando as matrizes e armazenando o resultado em uma lista
    for (i = 0; i < 15; i++)
    {
        for (j = 0; j < 15; j++)
        {
            soma = 0;

            for (k = 0; k < 15; k++)
            {
                soma += A[i][k] * B[k][j];
            }
            //nao armazena valor 0 na lista
            if (soma != 0)
            {
                lista_mult = inserir_fim(lista_mult,soma,i,j);
            }
            
        }
        
    }
    

    
    return lista_mult;
}

void soma_inferior(no *lista)
{
    no *aux = lista;
    int soma = 0;
    //soma dos elementos abaixo da diagonal principal de uma matriz
    while(aux != NULL)
    {
        if(aux->linha > aux->coluna)
        {
            soma += aux->valor;
        }
        aux = aux->prox;
    }
    
    printf("Soma: %d\n",soma);
}

void limpar()
{
    //limpar tela
    #ifdef _WIN32 || _WIN64
        system("cls");
    #else
        system("clear");
    #endif
}

void liberar(no *lista)
{
    //liberando memoria alocada
    while (lista != NULL)
    {
        no *deletando = lista;
        lista = lista->prox;
        free(deletando);
    }
}