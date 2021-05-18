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

//Lista
typedef struct lista {
	struct lista* prox;
	NO* inicio;
}LISTA;


void criaAdj(VERTICE* g, int vi, int vf){
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->v = vf;
    novo->prox = g[vi].inicio;
    g[vi].inicio = novo;
}

// funcao principal
NO* caminhos_max_d(VERTICE* g, int n, int x, int y, int d);

LISTA* ultimoL(LISTA* p){
    while(p){
        if(p->prox == NULL){
            return p;
        }
        p = p->prox;
    }
    return NULL;
}

void addLista(NO* *caminho, LISTA* *l){
	LISTA* novo = (LISTA*) malloc(sizeof(LISTA));
	LISTA* ult = ultimoL(*l);
	NO* temp = *caminho;
	novo->inicio = temp;
	caminho = NULL;
	if (ult)
		ult->prox = novo;
	else
		*l = novo;
}

void verificar(LISTA l){

}

NO* ultimoN(NO* p){
    while(p){
        if(p->prox == NULL){
            return p;
        }
        p = p->prox;
    }
    return NULL;
}

void criaCaminho(NO* *caminho, int v){
	NO* novo = (NO*) malloc(sizeof(NO));
    NO* ult = ultimoN(*caminho);
    novo->v = v;
    novo->prox = NULL;
    if(!ult)
        *caminho = novo;
    else
        ult->prox = novo;	
}

void percorre(VERTICE* g, int x, int y, int d,int cont){
    
	NO* caminho;
	LISTA* l;

	if (cont > d){
		return;
	}
	if(x == y){
		addLista(&caminho, &l);
	}

	NO* n = g[x].inicio;
	while (n){
		NO* ant = n;
		criaCaminho(&caminho,x);
		percorre(g,n->v,y,d,cont+1);
        n = n->prox;
    }
}

NO* caminhos_max_d(VERTICE* g, int n, int x, int y, int d){
	int cont = 1;
	percorre(g,x,y,d,cont);
}

int main()
{
	if (nroUSP()==0)
	 printf("\n\nNro USP nao informado!!!\n\n");
	
	VERTICE* graf = (VERTICE*) malloc(sizeof(VERTICE)*5);
    int tamg = 5;
	for (int i = 1; i <= tamg; i++)
        graf[i].inicio = NULL;

    criaAdj(graf,1,3);
    criaAdj(graf,1,2);
    criaAdj(graf,3,2);
    criaAdj(graf,3,5);
    criaAdj(graf,4,2);
    criaAdj(graf,4,3);
    criaAdj(graf,5,4);
}

