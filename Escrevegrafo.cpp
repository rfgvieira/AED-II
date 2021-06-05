#include<stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct registro { 
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

void criaAdj(VERTICE* g, int vi, int vf, int p,registro* vetor_grafo,int* cont){
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->vertice = vf;
    novo->peso = p;
    novo->prox = g[vi].inicio;
    g[vi].inicio = novo;
    vetor_grafo[*cont].v1=vi;
    vetor_grafo[*cont].v2=vf;
    vetor_grafo[*cont].custo=p;
    *cont= *cont+1;
}

int main(){
    FILE* arq;
    arq = fopen("grafo.dad","wb");
    VERTICE* graf = (VERTICE*) malloc(sizeof(VERTICE)*5);
    
    for (int i = 0; i < 5; i++){
        graf[i].inicio = NULL;
    }
    int tamgraf = 5;
    struct registro vetor_grafo[10];
    fwrite(&tamgraf,sizeof(tamgraf),1,arq);

    int cont = 0;
    criaAdj(graf,0,2,3,vetor_grafo,&cont);
    criaAdj(graf,0,1,8,vetor_grafo,&cont);
    criaAdj(graf,2,1,4,vetor_grafo,&cont);
    criaAdj(graf,2,4,1,vetor_grafo,&cont);
    criaAdj(graf,3,1,3,vetor_grafo,&cont);
    criaAdj(graf,3,2,3,vetor_grafo,&cont);
    criaAdj(graf,4,3,8,vetor_grafo,&cont);


    fwrite(vetor_grafo,sizeof(registro),cont,arq);
    fclose(arq);

    
}