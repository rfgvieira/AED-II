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
}

