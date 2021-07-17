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

//Definição de uma pilha que armazena os endereços dos antecedentes de uma determinada folha
typedef struct PILHA{
	int endereco;
	PILHA* prox;
} NO;


void exibir(char nomearq[]){
	FILE* arq;
	arq = fopen(nomearq,"rb");
	PAGINA pag;
	while (fread(&pag,sizeof(PAGINA),1,arq))
	{
		printf("Endereco:%d Chaves/Link: -/%d ", pag.np,pag.item[0].linkdir);
		for (int i = 1; i <= pag.cont; i++)
			printf("%d/%d ",pag.item[i].chave, pag.item[i].linkdir);
		printf("\n");
	}
	
	fclose(arq);
}

// funcao principal
void inserir(char nomearq[], int* raiz, int ch);

//Função que retorna o endereço da última página do arquivo
int ultimoEnd(FILE* arq){
	int cont = -1;
	PAGINA pag;
	fseek(arq,0,SEEK_SET);
	while (fread(&pag,sizeof(PAGINA),1,arq))
		cont++;
	return cont;	
}

//Função push da pilha
void push(PILHA* *p, int end){
	PILHA* novo = (PILHA*) malloc(sizeof(PILHA));
	novo->endereco = end;

	if (p == NULL)
		*p = novo;
	else{
		novo->prox = *p;
		*p = novo;
	}
}

//Função pop da pilha retornando o endereço do pai de uma folha
PILHA* pop(int* end, PILHA* p){//corrigir
	if (p == NULL) 
		return NULL;
	PAGINA pai;
	*end = p->endereco;
	PILHA* aux = p;
	p = p->prox;
	aux->prox = NULL;
	free(aux);
	return p;
}

//Cria uma nova página
PAGINA* criaPag(FILE* arq){
	PAGINA* pag = (PAGINA*) malloc(sizeof(PAGINA));
	CHLINK* zero =  (CHLINK*) malloc(sizeof(CHLINK));

	zero->chave = -1;
	zero->linkdir = -1;

	pag->cont = 0;
	pag->np = ultimoEnd(arq)+1;
	pag->item[0] = *zero;
	pag->item[1].linkdir = -1;
	pag->item[2].linkdir = -1;
	
	return pag;
}

//Função que busca em que folha uma determinada chave deve ser inserida
int buscaFolha(FILE* arq, int ch, int pai, PILHA* *p){
	PAGINA pag;
	fseek(arq,sizeof(PAGINA) * pai,SEEK_SET);
	fread(&pag,sizeof(PAGINA),1,arq);

	if (ch == pag.item[1].chave || ch == pag.item[2].chave)//Verifica se a chave ja existe na árvore, caso exista retorna -1 como endereço
		return -1;

	if (ch < pag.item[1].chave && pag.item[0].linkdir != -1){
			push(&*p,pag.np);
			return buscaFolha(arq, ch, pag.item[0].linkdir,p);
	}

	if (pag.cont == 2)
	{
		if (ch > pag.item[2].chave && pag.item[2].linkdir != -1){
			push(&*p,pag.np);
			return buscaFolha(arq, ch, pag.item[2].linkdir,p);
		}
		if (ch < pag.item[2].chave &&  ch > pag.item[1].chave && pag.item[1].linkdir != -1){
			push(&*p,pag.np);
			return buscaFolha(arq, ch, pag.item[1].linkdir,p);
		}
	}
	else{
		if (ch > pag.item[1].chave && pag.item[1].linkdir != -1){
			push(&*p,pag.np);
			return buscaFolha(arq, ch, pag.item[1].linkdir,p);
		}
	}

	return pag.np;
}

//Cria um novo par chave-link e insere na página verificando se a chave é maior ou menor que o par ja contido na pagina caso for menor ele irá trocar os dois de lugares
void inserePaginaExistente(FILE* arq, PAGINA pag, int ch,CHLINK* meio){
	CHLINK* link;
	if (!meio)
	{
		link = (CHLINK*) malloc(sizeof(CHLINK));
		link->chave = ch;
		link->linkdir = -1;
	}
	else
		link = meio;

	if (pag.item[1].chave > ch){
		CHLINK aux;
		aux = pag.item[1];
		pag.item[1] = *link;
		pag.item[2] = aux;
	}
	else{
		pag.item[2] = *link;
	}

	pag.cont++;

	fseek(arq,-sizeof(PAGINA),SEEK_CUR);
	fwrite(&pag,sizeof(PAGINA),1,arq);
}

//Efetua o split de uma página quando a página foi designada para uma chave, porém a página ja está lotada
CHLINK dividir(FILE* arq, PAGINA* pag, int ch,int * np,CHLINK* mid,int pagant){
	CHLINK* link;
	CHLINK meio;
	PAGINA* novapag = criaPag(arq);
	*np = novapag->np;

	if(!mid) {
		link = (CHLINK*) malloc(sizeof(CHLINK));
		link->chave = ch;
		link->linkdir = -1;
	}	
	else
		link = mid;

	if (ch < pag->item[1].chave){
		meio = pag->item[1];
		pag->item[1] = *link;
		novapag->item[1] = pag->item[2];
		novapag->item[0].linkdir = pagant ;
		pag->item[2] = novapag->item[2];
		novapag->cont++;
		pag->cont--;
	}
	else if(ch > pag->item[2].chave){
		meio = pag->item[2];
		novapag->item[1] = *link;
		novapag->item[0].linkdir = pagant ;
		pag->item[2] = novapag->item[2];
		novapag->cont++;
		pag->cont--;
	}
	else{
		meio = *link;
		novapag->item[1] = pag->item[2];
		novapag->item[0].linkdir = pagant ;
		pag->item[2] = novapag->item[2];
		novapag->cont++;
		pag->cont--;
	}
	
	fseek(arq,sizeof(PAGINA)*pag->np, SEEK_SET);
	fwrite(pag,sizeof(PAGINA),1,arq);
	fseek(arq,sizeof(PAGINA)*novapag->np, SEEK_SET);
	fwrite(novapag,sizeof(PAGINA),1,arq);

	return meio;
}

//Após o split efetua a promoção da chave do meio entre as tres chaves para um nível superior na árvore
//Caso seja necessário efetuar esse processo multiplas vezes chama essa função recursivamente
void promover(FILE* arq, PILHA* *pilha, PAGINA pag,int ch,int* raiz,CHLINK* mid,int pagant){
	int np = -1;
	CHLINK meio = dividir(arq,&pag,ch,&np,mid,pagant);
	meio.linkdir = np;
	int endereco = -1;
	*pilha = pop(&endereco,*pilha);

	if (endereco == -1)
	{
		PAGINA* pai = criaPag(arq);
		pai->item[1] = meio;
		pai->cont++;
		pai->item[0].linkdir = pag.np;
		*raiz = pai->np;
		fseek(arq,0, SEEK_END);
		fwrite(pai,sizeof(PAGINA),1,arq);
	}
	else{
		PAGINA pai;
		fseek(arq,sizeof(PAGINA)*endereco,SEEK_SET);
		fread(&pai,sizeof(PAGINA),1,arq);

		if(pai.cont < 2){
			inserePaginaExistente(arq,pai,meio.chave,&meio);
		}
		else{
			promover(arq,pilha,pai,meio.chave,&*raiz,&meio,pag.np);
		}
	}
}

//Função principal
void inserir(char nomearq[], int* raiz, int ch) {
	if (nomearq == NULL)
		return;
	PILHA* p = NULL;
    FILE* arq;
	int n = -1;
	
	if (*raiz == -1) //Verifica se existe o arquivo, caso existir abre ele, caso contrário cria o arquivo e abre ele, em ambos os casos a abertura e do tipo escrita/leitura
		arq = fopen(nomearq,"w+b");
	else
		arq = fopen(nomearq,"r+b");

    if(arq == NULL) {
		fclose(arq);
		return;
	}
		
	if (*raiz != -1)	//Se a árvore não estiver vazia busca a página em que a chave deve ser inserida
		n = buscaFolha(arq, ch, *raiz, &p);
	else {	//Caso contrário cria uma página inicial e insere o par chave-link inicial nela setando como a raiz
		CHLINK* link = (CHLINK*) malloc(sizeof(CHLINK));
		PAGINA* pag = criaPag(arq);
		pag->cont++;
		link->chave = ch;
		link->linkdir = -1;
		pag->item[1] = *link;
		*raiz = pag->np;
		fwrite(pag, sizeof(PAGINA), 1, arq);
	}
	if (n != -1) { //Caso exista um endereço para inserir a chave faz o seek dessa página
		PAGINA pag;
		fseek(arq, sizeof(PAGINA)*n, SEEK_SET);
		fread(&pag, sizeof(PAGINA), 1, arq);
		if (pag.cont < 2) //Caso a página não esteja lotada chama afunção de inserir na página
			inserePaginaExistente(arq, pag, ch, NULL);
		else //Caso contrário, faz o split e a promoção na página
			promover(arq, &p, pag, ch, raiz, NULL, -1);	
	}		

	fclose(arq);
}

int main() {
	if (nroUSP()==0 )
		printf("\n\nNro USP nao informado!!!\n\n");

	char nomearq[] = "minhaarvore.dad";
	int raiz = -1;

	// chame a insercao aqui
	inserir(nomearq, &raiz, 1);
	inserir(nomearq, &raiz, 2);
	inserir(nomearq, &raiz, 3);
	inserir(nomearq, &raiz, 4);
	inserir(nomearq, &raiz, 5);
	inserir(nomearq, &raiz, 6);
	inserir(nomearq, &raiz, 7);
	inserir(nomearq, &raiz, 8);
	inserir(nomearq, &raiz, 9);
	inserir(nomearq, &raiz, 10);
	inserir(nomearq, &raiz, 11);
	inserir(nomearq, &raiz, 12);
	inserir(nomearq, &raiz, 13);
	inserir(nomearq, &raiz, 14);
	inserir(nomearq, &raiz, 15);
	exibir(nomearq);
}