#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct expoente{//struct para os graus
int y;
struct expoente *prox;//aponta para o proximo grau
struct num *inicio;//aponta para o inicio dos coeficientes
}exp;



typedef struct num{//struct para os coeficientes
int x;
struct num *prox2;//aponta para o proximo coeficiente
}num;




void insereexp(exp **i, int c, int k)
{
	num *novo2=malloc(sizeof(num));//aloca espaco para um novo coeficiente
	if (novo2 == NULL) {
      	printf ("NULL!\n");
      	exit (EXIT_FAILURE);
  		 }

	if(*i==NULL)//verifica se a lista está vazia
	{
		exp *novo=malloc(sizeof(exp));//coloca o primeiro grau na lista e o seu coeficiente
		if (novo == NULL) {
      	printf ("NULL!\n");
      	exit (EXIT_FAILURE);
   	}
		novo->y=c;
		novo->prox=NULL;
		*i=novo;
		novo->inicio=novo2;
		novo2->x=k;
		novo2->prox2=NULL;
		return;
	}
	else
	{
		exp *aux=*i,*ant;
		while(*i)//percorre a lista
		{
			if((*i)->y==c)//procura algum grau igual
			{				//caso encontre um grau igual coloca o coeficiente na lista de coeficientes deste grau
				novo2->prox2=(*i)->inicio;
				(*i)->inicio=novo2;
				novo2->x=k;
				*i=aux;
				return ;
			}
			else
				(*i)=(*i)->prox;
		}
		*i=aux;//volta pro começo da lista se não encontrar nenhum grau igual
		exp *novo=malloc(sizeof(exp));//aloca espaco na memoria para um novo grau
		novo->y=c;
		novo->inicio=novo2;//insere o novo coeficiente
		novo2->x=k;
		novo2->prox2=NULL;
		if(c>(*i)->y){//verifica se o grau que deseja colocar é maior que o primeiro grau da lista
		*i=novo;		//caso seja maior insere o novo grau no inicio da lista e o seu coeficiente
		novo->prox=aux;}
		else{
			while(c<(*i)->y){//percorre a lista ate encontrar um grau menor do que o grau que vai entrar
				ant=*i;
				*i=(*i)->prox;
				if(*i==NULL)//caso tenha so um grau na lista
					break;
				if((*i)->prox==NULL)//caso não tenha nenhum grau menor na lista
					break;}
			if(*i==NULL){//insere o grau no final pois tem so um grau na lista e é maior que o grau que vai entrar
				*i=aux;
				(*i)->prox=novo;
				novo->prox=NULL;
				novo->y=c;
				novo->inicio=novo2;//insere o novo coeficiente
				novo2->x=k;
				novo2->prox2=NULL;
				*i=aux;
				return;}
			if(c>(*i)->y)//se encontrou algum grau menor do que o grau que vai entrar,insere antes deste grau
			{
				novo->prox=*i;
				*i=ant;
				(*i)->prox=novo;
				novo->inicio=novo2;//insere o novo coeficiente
				novo2->x=k;
				novo2->prox2=NULL;
				*i=aux;
				return;
			}

			//caso não tenha nenhum grau menor insere no final
			(*i)->prox=novo;
			novo->prox=NULL;
			novo->y=c;
			novo->inicio=novo2;//insere o novo coeficiente
			novo2->x=k;
			novo2->prox2=NULL;
			*i=aux;
	}
	}
}

int main()
{
	exp *lista=NULL,*busca;
	FILE *arquivo;
	arquivo = fopen("parametros.txt","r");//abri o arquivo para leitura

	if(arquivo==NULL)//verifica se o arquivo foi aberto
	{
		printf("Não foi possivel abrir o arquivo.\n");
		return 0;
	}
	int n,e;
	char esp, esp3;

	fscanf(arquivo,"%d%c",&n,&esp);
	while(!feof(arquivo))//verifica o final do arquivo
	{
		if(EOF != fscanf(arquivo,"%d%c%d%c",&n,&esp,&e,&esp3))//verifica se a leitura falhou
		insereexp(&lista,e,n);//coloca os graus e seus coeficientes respectivos

	}

	fclose(arquivo);

	exp *lista2=NULL,*busca2;
	arquivo = fopen("parametros.txt","r+");//abri o arquivo para leitura/escrita

	if(arquivo==NULL)//verifica se o arquivo foi aberto
	{
		printf("Não foi possivel abrir o arquivo.\n");
		return 0;
	}

	fscanf(arquivo,"%d%c",&n,&esp);
	while(!feof(arquivo))//le o pimeiro o polinomio e coloca ele na lista
	{
		if(EOF != fscanf(arquivo,"%d%c%d%c",&n,&esp,&e,&esp3))//verifica se a leitura falhou
			insereexp(&lista2,e,n);
		if(esp3=='\n')//verifica quando acabou o primeiro polinomio
			break;
	}

	while(!feof(arquivo))//le todos os outros e polinomios e coloca eles na lista
	{
		if(EOF != fscanf(arquivo,"%d%c%d%c",&n,&esp,&e,&esp3))//verifica se a leitura falhou
			insereexp(&lista2,e,n*(-1));
	}

	int soma=0;
	num *aux=lista->inicio;
	//O Proxímo while imprime no arquivo "parametros.txt" a soma de todos os polinomios
	while (lista) {//percorre a lista
		aux=lista->inicio;
		while(lista->inicio!=NULL){//percorre a lista dos coeficientes

			soma=soma+(lista->inicio->x);//soma todas os coeficientes
			lista->inicio=lista->inicio->prox2;//vai pra proximo coeficiente

		}
		lista->inicio=aux;
		if(soma!=0){//se a soma dos coeficientes for 0 nao imprime

		fprintf(arquivo,"%d ", soma);//imprime a soma dos coeficientes
		fprintf (arquivo,"%d ",lista->y);}//imprime o grau
		lista = lista->prox;//vai para o proximo grau
		soma=0;
	}
	fprintf (arquivo,"\n");//pula uma linha no arquivo
	soma=0;
	aux=lista2->inicio;
//O Proxímo while imprime no arquivo "parametros.txt" a subtracao de todos os polinomios
	while (lista2) {//percorre a lista 2
		aux=lista2->inicio;
		while(lista2->inicio!=NULL){//percorre a lista dos coeficientes

			soma=soma+(lista2->inicio->x);//soma todas os coeficientes
			lista2->inicio=lista2->inicio->prox2;	//vai pra proximo coeficiente

		}
		lista2->inicio=aux;
		if(soma!=0){	//se a soma dos coeficientes for 0 nao imprime

		fprintf(arquivo,"%d ", soma);	//imprime a soma dos coeficientes
		fprintf (arquivo,"%d ",lista2->y);}//imprime o grau
		lista2 = lista2->prox;//vai para o proximo grau
		soma=0;
	}

	fclose(arquivo);
}
