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
    bool chave;
    int flag;
    NO* inicio;
} VERTICE;

void criaAdj(VERTICE* g, int vi, int vf, int p){
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->vertice = vf;
    novo->peso = p;
    novo->prox = g[vi].inicio;
    g[vi].inicio = novo;
}


int main(){

    FILE* arq;
    arq = fopen("grafo.wasd","rb");
    if(arq != NULL){
        int tam;
        fread(&tam,sizeof(int),1,arq);

        VERTICE* graf = (VERTICE*) malloc(sizeof(VERTICE)*tam);
        for (int i = 0; i < tam; i++){
            graf[i].inicio = NULL;
        }

        int count = -1;
        struct registro vetor_grafo[36];
        count = fread(&vetor_grafo,sizeof(int),1,arq);

        for (int i = 0; i < count; i++){
            criaAdj(graf,vetor_grafo[i].v1,vetor_grafo[i].v2,vetor_grafo[i].custo);
        }
    }
}