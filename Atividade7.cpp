#include<stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct registro{ 
	int v1;
	int v2;
	int custo;
} REGISTRO;

typedef struct aresta {
    int vertice;
    int peso;
    struct aresta *prox;
} NO;

typedef struct {
    NO* inicio;
} VERTICE;

void exibir(VERTICE* g, int n ){
    for (int i = 0; i < n; i++)
    {   
        printf("V%d:  ",i);
        NO* no = g[i].inicio;
        while (no)
        {
            printf("V%d ",no->vertice);
            no = no->prox;
        }
        printf("\n") ;
    } 
}

void criaAdj(VERTICE* g, int vi, int vf, int p){
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->vertice = vf;
    novo->peso = p;
    novo->prox = g[vi].inicio;
    g[vi].inicio = novo;
}


int main(){

    FILE* arq;
    arq = fopen("grafo.dad","rb");
    if(arq != NULL){
        int tam;
        fread(&tam,sizeof(int),1,arq);

        VERTICE* graf = (VERTICE*) malloc(sizeof(VERTICE)*tam);
        for (int i = 0; i < tam; i++){
            graf[i].inicio = NULL;
        }

        int count = 0;
        struct registro vetor_grafo[45];
        while (!feof(arq)){
             fread(&vetor_grafo[count],sizeof(registro),1,arq);
             count++;
        }
        
        fclose(arq);

        for (int i = 0; i < count-1; i++){
            criaAdj(graf,vetor_grafo[i].v1,vetor_grafo[i].v2,vetor_grafo[i].custo);
        }
        exibir(graf,tam);
    }
}