#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Lista{
 char produto[20];
 struct Lista *prox;
}Lista;

void *insereProduto(Lista **prim, char *produto);
void imprimeLista (Lista *le);
int quantidadeProdutos(Lista *prim);
void removeProduto(Lista **prim);

void main(){
  Lista *p=NULL;
  int k;
insereProduto(&p, "Arroz");
insereProduto(&p, "Feijao");
insereProduto(&p, "Carne");
insereProduto(&p, "Sal");
  k = quantidadeProdutos(p);
  printf("Total de produtos na lista: %i\n\n", k);
  printf("Lista:*************\n");
  imprimeLista(p);
  printf("*******************");
  removeProduto(&p);
}

void removeProduto(Lista **prim){
      if (prim == NULL) return;
      Lista *aux = *prim;
      *prim = (*prim) -> prox;
      free(aux);
}

int quantidadeProdutos(Lista *prim){
  int cont=0;
  Lista *p;
  for (p = prim; p != NULL; p = p->prox){
     cont++;
  }
  return cont;
}

void *insereProduto(Lista **prim, char *produto){
  Lista* novo = (Lista *)malloc(sizeof(Lista));
  if (novo == NULL) printf("Falha ao alocar");
  strcpy(novo->produto, produto);
  novo->prox = *prim;
  *prim = novo;
}

void imprimeLista (Lista *le) {
   Lista *p;
   for (p = le; p != NULL; p = p->prox){
      printf ("%s\n", p->produto);
   }
}
