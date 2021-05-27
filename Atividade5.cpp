#include<stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct registro{
    char nome[10];
    int notas;
};

void Exibir(struct registro vetor_alunos[], int proximo){
    int i;
    printf("\n--------------------------------------\n");
    printf("Ha %d alunos cadastrados.\n", proximo);
    printf("      Nome Nota\n", proximo);
    for (i=0; i< proximo; i++){
        printf("%10s ", vetor_alunos[i].nome);
        printf("%d\n", vetor_alunos[i].notas);
    }
    printf("\n--------------------------------------\n");
} 

int main() {
    int f;
    char nota[4];
    int cont = 0;
    FILE *arq;
    FILE *cop;
    struct registro vetor_alunos[30];
    if ((arq=fopen("notas.txt","rb"))==NULL)
        printf("Arquivo nao encontrado...\n");
    else {
        while (!feof(arq))//Enquanto não encontrar o fim do arquivo continua no loop
        {
            int prox = 0;
            int dec = 0;
            int j = 0;
            while (j < sizeof(vetor_alunos->nome)){//Loop para inserir os nomes dos alunos no registro percorrendo caracter a caracter até encontrar a divisória '/'
                vetor_alunos[cont].nome[j] = fgetc(arq);
                if (vetor_alunos[cont].nome[j] == '/'){
                    vetor_alunos[cont].nome[j] = '\000';
                    break;
                }  
                j++;
            }
            for (int i = j+1; i < sizeof(vetor_alunos->nome); i++)//Zera os bits não usados do registro
                vetor_alunos[cont].nome[i] = '\000';
       
            while (1==1){//Loop que atribui as notas para um vetor de caracteres
                nota[prox] = fgetc(arq);
                if (nota[prox] == '\n' || feof(arq))
                    break;
                prox++; 
            }
            vetor_alunos[cont].notas = 0;
            for (int i = prox-1; i >= 0; i--){//Loop para converter as notas em int
                dec = pow(10,prox-1-i);
                vetor_alunos[cont].notas += (nota[i] - 48) * dec; 
            }

            cont++;
        }
        fclose(arq);
        Exibir(vetor_alunos,cont);
    }
    //Cria o novo arquivo e insere os registros nele
    cop = fopen("notasF.txt","w");
    f = fwrite(vetor_alunos, sizeof(registro),cont,cop);
    fclose(cop);
}
