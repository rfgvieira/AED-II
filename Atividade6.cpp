#include<stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct registro {
    char nrousp[7];
    char nome[20];
    int idade;
    int valido; 
};
void trocaReg(registro r1, registro r2, FILE* arq){

}
int main(){
    FILE* arq;
    registro r1;
    registro r2;
    int b1,b2;
    arq = fopen("teste.dad","w+")
    while (1==fread(&r1,sizeof(registro),1,arq)) {
        if (strcmp(r1.nome,"guilherme") == 0)
        {
           
        }
        
    }
    
    fseek(arq,+,SEEK_SET)
}
