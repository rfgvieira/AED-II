//--------------------------------------------------------------
// NOME : Rodrigo Fernandes Gomes Vieira
//--------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>

// ######### ESCREVA O NROUSP AQUI
int nroUSP() {
    return 11796548;
}

//-------------------------------------------

// nos das listas de adjacencias
typedef struct adj {
	int v;
	struct adj* prox;
} NO;

// vertices
typedef struct {
	NO* inicio;
} VERTICE;

void exibir(NO* l){
    if(l!=NULL){
        printf("[");
        while (l->prox != NULL)
        {
            printf("%d,", l->v);
            l = l->prox;
        }
        printf("%d]", l->v);
    }
    else
        printf("NULL");
    
}

void criaAdj(VERTICE* g, int vi, int vf){
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->v = vf;
    novo->prox = g[vi].inicio;
    g[vi].inicio = novo;
}

// funcao principal
NO* caminhos_max_d(VERTICE* g, int n, int x, int y, int d);

NO* ultimo(NO* p){
    while(p){
        if(p->prox == NULL){
            return p;
        }
        p = p->prox;
    }
    return NULL;
}

void removeUlt(NO* *caminho,int* *flag){
    NO* ult = ultimo(*caminho);
    int ultvert = ult->v;
    NO* p = *caminho;
    while (p){
        if (p->prox == ult){
            p->prox = NULL;
            free(ult);
            break;
        }
        
        p = p->prox;
    }
    // *flag[ultvert-1] = 0;
}

void addLista(NO* *caminho, NO* *l){
    NO* p = *caminho;
	while (p){
        NO* ult = ultimo(*l);
        NO* novo = (NO*) malloc(sizeof(NO));
        novo->v = p->v;
        novo->prox = NULL;
        p = p->prox;
        if (ult)
		    ult->prox = novo;
	    else
		    *l = novo;
    }	
}

void criaCaminho(NO* *caminho, int v){
	NO* novo = (NO*) malloc(sizeof(NO));
    NO* ult = ultimo(*caminho);
    novo->v = v;
    novo->prox = NULL;
    if(!ult)
        *caminho = novo;
    else
        ult->prox = novo;	
}

void percorre(VERTICE* g, int x, int y, int d,int cont,NO* *l,int* flag,NO* caminho){
    criaCaminho(&caminho,x);
    flag[x-1] = 1;

	if (cont > d){
        removeUlt(&caminho,&flag);
        flag[x-1] = 0;
		return;
	}
	if(x == y){
		addLista(&caminho, &*l);
        removeUlt(&caminho,&flag);
        flag[x-1] = 0;
        return;
	}

	NO* n = g[x].inicio;
	while (n){
		if (flag[(n->v)-1] == 0){
            percorre(g,n->v,y,d,cont+1,&*l,flag,caminho);
        }
		    
        n = n->prox;
    }
    removeUlt(&caminho,&flag);
    flag[x-1] = 2;
}

NO* caminhos_max_d(VERTICE* g, int n, int x, int y, int d){
	int cont = 0;
    NO* lista = NULL;
	NO* caminho = NULL;
    int *flag = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
         flag[i] = 0;
    }
	percorre(g,x,y,d,cont,&lista,flag,caminho);
    
    return lista;
}

int main()
{
	if (nroUSP()==0)
	 printf("\n\nNro USP nao informado!!!\n\n");
	
	VERTICE* graf = (VERTICE*) malloc(sizeof(VERTICE)*5);
    int tamg = 5;
	for (int i = 1; i <= tamg; i++)
        graf[i].inicio = NULL;
    NO* lista = NULL;
    criaAdj(graf,1,3);
    criaAdj(graf,1,2);
    criaAdj(graf,3,2);
    criaAdj(graf,3,5);
    criaAdj(graf,4,2);
    criaAdj(graf,4,3);
    criaAdj(graf,5,4);
    lista = caminhos_max_d(graf,tamg,1,4,1);
    exibir(lista);
}

