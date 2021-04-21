#include<stdio.h>
#include<malloc.h>
#include<stdbool.h>

typedef struct aresta {
    int vertice;
    struct aresta *prox;
} NO;

typedef struct {
    NO* inicio;
} VERTICE;    


void exibir(VERTICE* g, int n ){
    for (int i = 0; i < n; i++)
    {
        printf("V%d: ",i);
        NO* no = g[i].inicio;
        while (no)
        {
            printf("V%d ",no->vertice);
            no = no->prox;
        }
        printf("\n") ;
    }
    
}

void criaAdj(VERTICE* g, int vi, int vf){
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->vertice = vf;
    novo->prox = g[vi].inicio;
    g[vi].inicio = novo;
}

int main(){
    VERTICE* graf = (VERTICE*) malloc(sizeof(VERTICE)*5);
    for (int i = 0; i < 5; i++)
        graf[i].inicio = NULL;

    criaAdj(graf,0,2);
    criaAdj(graf,0,1);
    criaAdj(graf,2,1);
    criaAdj(graf,2,4);
    criaAdj(graf,3,1);
    criaAdj(graf,3,2);
    criaAdj(graf,4,3);
    
    exibir(graf, 5);
}