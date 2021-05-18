#include<stdio.h>
#include<malloc.h>
#include<stdbool.h>

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
NO* ultimo(NO* n){
    while (n){
        if (n->prox == NULL){
            return n;
        }
        n = n->prox;
    }
    return NULL;
}

void push(NO* *n, int v){
    NO* novo = (NO*) malloc(sizeof(NO));
    NO* ult = ultimo(*n);
    novo->vertice = v;
    novo->peso = -999;
    novo->prox = NULL;
    if (ult){
        ult->prox = novo;
    }
    else{
        *n = novo;
    }
}


int custoChaveMaisProxima(VERTICE* g, int i,int n){
    for (int i = 0; i < n; i++){
        g[i].flag = 0;
    }
    NO* fila = NULL;
    int contador = 0;
    g[i].flag = 1;
    push(&fila,i);

    while (fila){
        int ult;
        NO* temp;
        if (fila == NULL){
            return -999;
        }
        
        ult = fila->vertice;
        temp = fila;
        fila = fila->prox;
        free(temp);

        NO* p = g[i].inicio;
        while (p){
            if (g[p->vertice].flag == 0){
                g[p->vertice].flag = 1;
                push(&fila,p->vertice);
                if(g[p->vertice].chave){
                    contador++;
                  return contador;
                }
            }
            p = p->prox;
        }
        contador++;
    } 
}

int main(){
    VERTICE* graf = (VERTICE*) malloc(sizeof(VERTICE)*5);
    for (int i = 0; i < 5; i++){
        graf[i].inicio = NULL;
        if(i == 4 )
            graf[i].chave = true;
        else
            graf[i].chave = false;
    }
    criaAdj(graf,0,2,3);
    criaAdj(graf,0,1,8);
    criaAdj(graf,2,1,4);
    criaAdj(graf,2,4,1);
    criaAdj(graf,3,1,3);
    criaAdj(graf,3,2,3);
    criaAdj(graf,4,3,8);
    int custo = custoChaveMaisProxima(graf,0,5);
    printf("Custo: %d",custo);
}