//--------------------------------------------------------------
// NOME : Rodrigo Fernandes Gomes
//--------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

// ######### ESCREVA O NROUSP AQUI
int nroUSP() {
    return 11796548;
}

//-------------------------------------------

// CHLINK eh um par <chave,link> - dentro de cada página há 3 CHLINKs
typedef struct {
	int chave;
	int linkdir;
} CHLINK;

// definicao de pagina da árvore / registro do arquivo
typedef struct {
	int np; // armazene aqui o nro da pagina no arquivo
	int cont; // armazene aqui a quantidade de chaves existentes no vetor CHLINK[]
	CHLINK item[3]; // a chave[0] eh desprezada, e o linkdir[0] eh na verdade o link esquerdo da chave[1]
} PAGINA;


// funcao principal
void inserir(char nomearq[], int* raiz, int ch);


//------------------------------------------
// O EP consiste em implementar esta funcao
// e outras funcoes auxiliares que esta
// necessitar
//------------------------------------------

void inserir(char nomearq[], int* raiz, int ch) {
    FILE* arq;
	arq = fopen(nomearq,"w+b");
    if(arq != NULL){
		
		fclose(arq);
	}
	// abra o arquivo
	// faca a insercao / divisao / promocao etc.
	// atualize o nro da *raiz se necessario
	// feche o arquivo
}



//---------------------------------------------------------
// use main() para fazer chamadas de teste ao seu programa
// mas nao entregue o codigo de main() nem inclua nada
// abaixo deste ponto
//---------------------------------------------------------
int main()
{
	if (nroUSP()==0 )
		printf("\n\nNro USP nao informado!!!\n\n");

	char nomearq[] = "minhaarvore.bin";
	int raiz = 0;
	int chave = 666;

	// chame a insercao aqui
	inserir(nomearq, &raiz, chave);

}


