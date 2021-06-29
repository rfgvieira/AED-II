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
    int vi;
    int vf;
    int endereco;
} TABELA;

//Muda a posição de duas arestas na tabela
void mudaPos(TABELA tab[], int esq, int dir){
    int auxvi = tab[esq].vi;
    int auxvf = tab[esq].vf;
    int auxend = tab[esq].endereco;
    tab[esq].vi = tab[dir].vi;
    tab[esq].vf = tab[dir].vf;
    tab[esq].endereco = tab[dir].endereco;
    tab[dir].vi = auxvi;
    tab[dir].vf = auxvf;
    tab[dir].endereco = auxend;
}

//Particiona os elementos em dois grupos
int dividi(TABELA tab[],int inicio,int fim,int tipo){
    int esq = inicio;
    int dir = fim;
    int pivo,compesq,compdir;

    if (tipo == 0)
        pivo = tab[inicio].vi;
    else
        pivo = tab[inicio].vf;

    while (esq < dir){
        if (tipo == 0){
            compesq = tab[esq].vi;
            compdir = tab[dir].vi;
        }
        else{
            compesq = tab[esq].vf;
            compdir = tab[dir].vf;
        }
            
        while(compesq <= pivo){
            esq++;
            if (tipo == 0)
                compesq = tab[esq].vi;
            else
                compesq = tab[esq].vf;
        }
            
        while(compdir > pivo){
            dir--;
            if (tipo == 0)
                compdir = tab[dir].vi;
            else
                compdir = tab[dir].vf;
        }
            
        if (esq < dir){
            mudaPos(tab,esq,dir);
        }
    }
    mudaPos(tab,inicio,dir);
    return dir;
}

//Ordena os elementos atraves de quicksort, além disso o método possui um paramentro "tipo" que identifica se é para ordenar os vertices iniciais(0) ou os finais(1)
void ordena(TABELA tab[],int inicio,int fim,int tipo){
    int pivo;
    if (fim > inicio){
        pivo = dividi(tab,inicio,fim,tipo);
        ordena(tab,inicio,pivo-1,tipo);
        ordena(tab,pivo+1,fim,tipo);
    }
    
}

//Pega um sub-array de todos os vertices iniciais iguais a "vi" na tabela
void corta(TABELA* tab,int vi,int tam){
    int ini = 0;
    int fim = 0;
    int flag = 0;
    for (int i = 0; i <= tam; i++)
    {
        if (tab[i].vi == vi && flag == 0){
            ini = i;
            flag = 1;
        }
        if(tab[i+1].vi != vi && flag == 1){
            fim = i;
            break;
        }
    }

    ordena(tab,ini,fim,1);
}

//Insere os registros na tabela ordenando eles
void insereTabela(TABELA tab[],int c1,int c2,int end){
    tab[end].vi=c1;
    tab[end].vf=c2;
    tab[end].endereco=end;
    ordena(tab,0,end,0);
    for (int i = 0; i <= tab[end].vi; i++)
        corta(tab,i,end);
}

//Le o arquivo e insere os registros na tabela
void tab(FILE* arq){
    int prox = 0;

    TABELA tabela[100];
    
    fseek(arq,sizeof(int),SEEK_SET);
    registro r;

    while (!feof(arq)){
        fread(&r,sizeof(registro),1,arq);
        insereTabela(tabela,r.v1,r.v2,prox);
        prox++;
    }   
}

int main(){

    FILE* arq;
    arq = fopen("grafo.dad","rb");
    tab(arq);
}