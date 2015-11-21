/*
** TRABALHO 1 DE TEORIA DOS GRAFOS - UFSCAR CAMPUS SOROCABA
**
** NOME: RAFAEL DANILO DOS SANTOS RA 408654
**
** DESCRIÇÃO: Resolve o problema "Is it a tree" - Problem code: PT07Y do SPOJ
**						recebe um grafo como entrada e diz se é uma arvore("YES") ou nao("NO")
**
**
*/
#include<stdio.h>
#define MAX 1000
#define NULO 0
#define TRUE 1
#define FALSE 0

enum cores {branco, cinza, preto};

//verifica se o grafo é conexo, percorrendo o vetor cor e procurando um posicao branca, se houver, o grafo é desconexo
int conexo(enum cores cor[MAX], int tam){
 int i;
	for (i=0;i<tam;i++){
		if(cor[i]==branco){
			return 0;
		}
	}
	return 1;
}
//busca em profundidade adaptado para informar se há ciclos a partir da raiz
int dfs(int grafo[MAX][MAX], int raiz, enum cores cor[MAX], int pred[MAX], int arvore, int tam){
int i;
	cor[raiz] = cinza;
	for(i=0;i<tam;i++){
		if(grafo[raiz][i]==1){
				if(cor[i] != branco) {
					arvore = FALSE;
				}
				else{pred[i]=i;dfs(grafo,i,cor,pred,arvore,tam);}
		}
	}
	cor[raiz]=preto;
return arvore;
}

//inicia o grafo
void inicia_grafo(int grafo[MAX][MAX], enum cores cor[MAX],int pred[MAX]){
	int i,j;
	for(i=0;i<MAX;i++){
	cor[i]=branco;
	pred[i]=NULO;
		for (j=0;j<MAX;j++){
			grafo[i][j]=0;
		}
	}
}

int main () {
	int n, m, //n eh o numero de vertices e m o de arestas
			u, v, i, //u e v sao os vertices do grafo
			grafo[MAX][MAX], //matriz de incidencia
			pred[MAX],
			caso_base,
			arvore,
			tam=0,//tamanho do grafo.
			dfs_saida;//

	enum cores cor[MAX];

	//entrada
	while(1){
		arvore=TRUE; //assume que o grafo é uma arvore.
		caso_base=FALSE;
		scanf("%d %d", &n, &m);
		if(n==0 && m==0) break;
		if((n==1 && m==0)){caso_base=TRUE;}//caso base
		if((n - 1 > m)){arvore=FALSE;}
		inicia_grafo(grafo,cor,pred);
		for(i=0;i<m;i++){
			scanf("%d %d", &u, &v);
			if(u != v){
				if(grafo[u-1][v-1]==0){ //faz o teste para saber se existem arestas paralelas
					grafo[u-1][v-1]=1;
					grafo[v-1][u-1]=1;}
				else{arvore=FALSE;}
		
				if(tam < u || tam < v){
					if(v < u){tam=u;}
					else{tam=v;}
				}
			}	else if (u!=0){
				arvore=FALSE;
				}
		}

	dfs_saida = dfs(grafo, 0, cor, pred, arvore, tam);

	//saida
	if((dfs_saida && conexo(cor,tam)) || caso_base){printf("YES\n");}
	else{printf("NO\n");}
	}
}
