#include<stdio.h>
#include<malloc.h>
#include<stdbool.h>

typedef struct aresta {
    int vertice;
    bool flag;
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
    novo->flag = false;
    g[vi].inicio = novo;
}

void adjacencia2incidencia(VERTICE* g, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(i != j) {
                NO* ini = g[j].inicio;
                int marcador = 0;// variavel pra verificar se achou algum vértice apontando pra o vértice atual
                NO* ant = NULL;
                while (ini && marcador == 0) {
                    if (ini->vertice == i && ini->flag == false) {//Propriedade falg, que indica se o nó ja foi mudado de adjacente pra incidente
                        if (ini == g[j].inicio)
                            g[j].inicio = g[j].inicio->prox;
                        else
                            ant->prox = ini->prox;
                        NO* temp = g[i].inicio;
                        g[i].inicio = ini;
                        ini->vertice = j;
                        ini->flag = true;
                        ini->prox = temp;
                        marcador = 1;
                    }
                    else
                        ant = ini;
                        ini = ini->prox;
                }
            }
        }
    }
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
     printf(" Adjacencia: \n");
    exibir(graf, 5);
    printf("\n Incidencia: \n");
    adjacencia2incidencia(graf, 5);
    exibir(graf, 5);
}