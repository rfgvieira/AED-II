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
    int chave[2];
    int endereco;
    struct tabela *prox;
} TABELA;

TABELA* ultimo(TABELA* tab){
    TABELA* p = tab;
    while(p){
        if(p->prox == NULL){
            return p;
        }
        p = p->prox;
    }
    return NULL;
}

void insereTabela(TABELA* *tab,int c1,int c2,int end){
    TABELA* novo = (TABELA*) malloc(sizeof(TABELA));
    TABELA* ult = ultimo(*tab);
    novo->chave[0] = c1;
    novo->chave[1] = c2;
    novo->prox = NULL;
    novo->endereco = end;
    if (ult)
        ult->prox = novo;
    else
        *tab = novo;
}

int procuraTabela(TABELA* tab,int vi,int vf){
    while (tab){
        if(tab->chave[0] == vi && tab->chave[1] == vf){
            return tab->endereco;
        }
        tab = tab->prox;
    }
    return -1;
}

int custoIndex(FILE* arq,int vi,int vf){
    int prox = 0;
    TABELA* tabela = NULL;
    
    fseek(arq,sizeof(int),SEEK_SET);
    registro r;

    while (!feof(arq)){
        fread(&r,sizeof(registro),1,arq);
        insereTabela(&tabela,r.v1,r.v2,prox);
        prox++;
    }

    int endereco = procuraTabela(tabela,vi,vf);
    fseek(arq,sizeof(int),SEEK_SET);
    fseek(arq,sizeof(REGISTRO) * endereco,SEEK_CUR);
    fread(&r,sizeof(REGISTRO),1,arq);
    
    return (endereco == -1) ? -1 : r.custo;
    
}

int main(){

    FILE* arq;
    arq = fopen("grafo.dad","rb");
    int resp = custoIndex(arq,2,4);
    printf("%d", resp);
}