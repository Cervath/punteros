#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define TConjunto TNodo

struct TNodo{
int info;
TNodo *prox;
};
//
bool EsvaciaPila(TNodo *pila){return (pila==nullptr);}

TNodo *BuscaEnPila(TNodo *l, int a, int b){

bool encontrado=false;
TNodo *auxpila=l;


do {
  switch (b) {
    case 0:encontrado=(auxpila->info==a);break;
    case -1:encontrado=(auxpila->prox->info==a);break;
  }
  if(!encontrado)auxpila=auxpila->prox;
} while(auxpila!=nullptr&&!encontrado);

    return auxpila;

}

void EliminaEnpila(TNodo **pila, int n){
  TNodo *p,*q;
  if(!EsvaciaPila(*pila)){
    p=*pila;
    if(p->info==n){
      *pila=p->prox;
      free(p);
    }else{

      p=BuscaEnPila(*pila,n,-1);

      q=p->prox;
      if(p!=nullptr){
        p->prox=q->prox;
        free(q);
      }
    }

  }
}

void IncluirConjunto(TNodo **pila, int n){

TNodo *aux=(TNodo*)malloc(sizeof(TNodo*));

  if(!EsvaciaPila(*pila)){
    if (!BuscaEnPila(*pila,n,0)) {
      aux->info=n;
      aux->prox=*pila;
      *pila=aux;
    }
  }
  else{
    aux->info=n;
    aux->prox=*pila;
    *pila=aux;
  }

}

void InterseccionConjunto(TNodo *c1,TNodo *c2, TNodo **r){
  for (TNodo *aux = c1; aux!=nullptr; aux=aux->prox) {
      if(!BuscaEnPila(c2,aux->info,0)){
        IncluirConjunto(r,aux->info);
      }
  }
}

void UnionConjunto(TNodo *c1, TNodo *c2, TNodo **r){
*r=c1;
  for (TNodo *aux=c2; aux!=nullptr; aux=aux->prox) {
    if(!BuscaEnPila(c1,aux->info,0)){
        IncluirConjunto(r,aux->info);
    }
  }

}

void MuestraConjunto(TNodo *pila){

  for (TNodo *aux=pila; aux!=nullptr; aux=aux->prox) {
    printf("%d, ",aux->info);
  }
}


TNodo *CrearConjunto(){
TNodo *aux=nullptr;

return aux;
}
