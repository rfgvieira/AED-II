#include<stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct registro{
    char nrousp[7];
    char nome[20];
    int idade;
    int valido; // 1=ok; 0=excluido.
};

void Exibir(struct registro vetor_alunos[], int proximo){
    int i;
    printf("\n--------------------------------------\n");
    printf("Ha %d alunos cadastrados.\n", proximo);
    printf("      Nome Nota\n", proximo);
    for (i=0; i< proximo; i++){
        if(vetor_alunos[i].valido == 1){
            printf("%8s ", vetor_alunos[i].nrousp);
            printf("%20s ", vetor_alunos[i].nome);
            printf("%d\n", vetor_alunos[i].idade);
        }
    }
    printf("\n--------------------------------------\n");
} 

int main() {
    int f;
    char c;
    int i;
    FILE *arq;
    struct registro vetor_alunos[30];
    int proximo = 0;
    if ((arq=fopen("teste.dad","rb"))==NULL)
        printf("Arquivo nao encontrado...\n");
    else {
        proximo = fread(vetor_alunos, sizeof(registro), 30, arq);
        if (proximo < 1) printf("Arquivo vazio...\n");
        fclose(arq);
    }
    do 
    {
        Exibir(vetor_alunos, proximo);
        printf("\nInforme o nro. USP:");
        fflush(stdin);
        fgets(vetor_alunos[proximo].nrousp,sizeof(vetor_alunos->nrousp),stdin);
        if (vetor_alunos[proximo].nrousp[0]== '0')
            break;
        printf("\nInforme o nome do aluno:");
        fflush(stdin);
        fgets(vetor_alunos[proximo].nome,sizeof(vetor_alunos->nome),stdin);
        printf("\nInforma a idade:");
        fflush(stdin);
        scanf("%d", &vetor_alunos[proximo].idade);
        vetor_alunos[proximo].valido = 1;
        proximo++;

    } while (proximo < 30);    
    fclose(arq);
    Exibir(vetor_alunos,proximo);
    
    arq = fopen("teste.dad","w");
    i = fwrite(vetor_alunos, sizeof(registro),proximo,arq);
    fclose(arq);
    printf("\nTecle algo para encerrar...");
    c = getchar(); 
}
