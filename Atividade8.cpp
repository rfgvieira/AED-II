#include<stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct registro{ 
	int v1;
	int v2;
	int custo;
} REGISTRO;

typedef struct tabela {
    char chave[2];
    int endereco;
    struct tabela *prox;
} TABELA;

typedef struct aresta {
    int vertice;
    int peso;
    struct aresta *prox;
} NO;

typedef struct {
    NO* inicio;
} VERTICE;

void criaAdj(VERTICE* g, int vi, int vf, int p){
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->vertice = vf;
    novo->peso = p;
    novo->prox = g[vi].inicio;
    g[vi].inicio = novo;
}

VERTICE* leGrafo(FILE* arq){
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
            return graf;
    }
}

void insereTabela(){

}

void custoIndex(FILE* arq,int vi,int vf){
    registro reg;
    int prox = 0;
    TABELA tabela;
    while (!feof(arq)){
        char chave1 = -1;
        char chave2 = -1;

        fread(&chave1,sizeof(reg.v1),1,arq);
        fread(&chave2,sizeof(reg.v2),1,arq);
        fseek(arq,sizeof(reg.custo),SEEK_CUR);
        

        prox++;
    }
    
    
    
    
    
}

int custoGraf(VERTICE* g,int vi,int vf){
    NO* p = g[vi].inicio;
    while (p)
    {
        if(p->vertice == vf){
            return p->peso;
        }
        p = p->prox;
    }
    return NULL;
    
}

int main(){

    FILE* arq;
    arq = fopen("grafo.dad","rb");
    VERTICE* graf = leGrafo(arq);
    int custo = custoGraf(graf,2,4);
    printf("%d",custo);
}