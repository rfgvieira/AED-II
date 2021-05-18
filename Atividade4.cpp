#include<stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool contemPalavra(char* palavra,FILE* arq,int tam){//Método que recebe a palavra a ser procurada, o arquivo e o tamanho da palavra a ser procurada
    char string[25];//Vetor para receber as palavras
    if (arq!=NULL){
        while(!feof(arq)){
            bool flag = false;
            bool igual = true;
            int i =0;
            while (!flag){//Atribuição das palavras ao vetor até encontrar um espaço uma quebra de linha ou um fim de arquivo
                string [i]= fgetc(arq);
                if (string[i] == '\n' || string[i] == ' ' || feof(arq))
                    flag = true;
                i++;
            }
            for (int j = 0; j < tam-1; j++){//Comparação da palavra desejada com a última palavra atribuida ao vetor
                if(string[j] != palavra[j]){
                    igual = false ;
                    j = tam;
                }
            }
            if(igual)
                return true;
        }
        return false;
    }
     return false;
}

int main(){ 
    FILE* arq;
    arq = fopen("teste.txt","r");//Abre o arquivo apenas pra leitura
    char palavra[] = "cachorro";//Palavra a ser procurada
    int  tam = sizeof(palavra);//Tamanho da palavra a ser procurada
    if (contemPalavra(palavra,arq,tam))
        printf("Contem palavra");
    else
        printf("Nao contem palavra");
    
}