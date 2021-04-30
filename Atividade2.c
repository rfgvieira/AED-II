#include<stdio.h>
#include<malloc.h>
#include<stdbool.h>

typedef struct aresta {
    int vertice;
    struct aresta *prox;
} NO;

typedef struct {
    bool chave;
    int flag;
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

void exibirl(NO* n){
    NO* p = n;
    while (p)
    {
        printf("%d ",p->vertice);
        p = p ->prox;
    }
    
}

void criaAdj(VERTICE* g, int vi, int vf){
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->vertice = vf;
    novo->prox = g[vi].inicio;
    g[vi].inicio = novo;
}


NO* ultimo(NO* resp){
    NO* p = resp;
    while(p){
        if(p->prox == NULL){
            return p;
        }
        p = p->prox;
    }
    return NULL;
}

void criaResp(NO** resp, int i){
    NO* novo = (NO*) malloc(sizeof(NO));
    NO* ult = ultimo(*resp);
    novo->vertice = i ;
    novo->prox = NULL;
    if(!ult)
        *resp = novo;
    else
        ult->prox = novo;
}

void salasComChaves(VERTICE* g, int i, NO* *resp){
    g[i].flag = 1;
    NO* n = g[i].inicio;
    if(g[i].chave == true)
        criaResp(&*resp, i);
    while (n){
        if(g[n->vertice].flag == 0){
            NO* ant = n;
            salasComChaves(g,n->vertice,&*resp);
        }
        n = n->prox;
    }
    g[i].flag = 2;
}


int main(){
    VERTICE* graf = (VERTICE*) malloc(sizeof(VERTICE)*5);
    for (int i = 0; i < 5; i++){
        graf[i].inicio = NULL;
        graf[i].flag = 0;
        if(i%2 == 0 )
            graf[i].chave = true;
        else
            graf[i].chave = false;
    }
    criaAdj(graf,0,2);
    criaAdj(graf,0,1);
    criaAdj(graf,2,1);
    criaAdj(graf,2,4);
    criaAdj(graf,3,1);
    criaAdj(graf,3,2);
    criaAdj(graf,4,3);
    NO* resp = NULL;
    salasComChaves(graf,1,&resp);
    exibirl(resp);
}