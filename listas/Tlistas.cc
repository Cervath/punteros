#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define TLista TNodo
struct TNodo{
int info;
TNodo *prox;
};

bool EsvaciaLista(TNodo *Lista){
    //Comprobación lista está vacía
    return (Lista==nullptr);
}

TNodo *BuscaEnLista(TLista *l, int a, int b){

bool encontrado=false;
TNodo *auxLista=l;


do {
  switch (b) {
    case 0:encontrado=(auxLista->info==a);break;
    case -1:encontrado=(auxLista->prox->info==a);break;
  }
  if(!encontrado)auxLista=auxLista->prox;
} while(auxLista!=nullptr&&!encontrado);

    return auxLista;

}

TNodo *IndexaLista(TLista *lista, int n){
int vuelta=0;
TNodo *auxIndex=nullptr;
  for (auxIndex=lista; vuelta<n; auxIndex=auxIndex->prox) {
    vuelta++;
  }
return auxIndex;
}

void EliminaEnLista(TLista **lista, int n){
  TNodo *p,*q;
  	if(!EsvaciaLista(*lista)){
  		 p=*lista;
  		 if(p->info==n){
  		 	*lista=p->prox;
  		 	free(p);
  		 }else{
              //Utilizamos BuscarEnLista con parámetro -1 para que el puntero de rastreo se quede en el nodo
              //anterior al que contiene el valor
  		 	p=BuscaEnLista(*lista,n,-1);
              //Ubicamos q en el nodo a elminar  (..será el siguiente del anterior ...)
  		 	q=p->prox;
  		 	if(p!=nullptr){
  		 		p->prox=q->prox;
  		 		free(q);//Liberamos la memoria ocupada por el nodo a borrar.
  		 	}
  		 }

  	}
}

void MuestraLista(TNodo *lista){

  for (TNodo *aux=lista; aux!=nullptr; aux=aux->prox) {
    printf("%d\n",aux->info);
  }
}

void InsertarLista(TNodo **lista, int n){

TNodo * aux=(TNodo*)malloc(sizeof(TNodo*));
aux->info=n;
aux->prox=*lista;
*lista=aux;

}

void CrearLista(TNodo **lista){
*lista=nullptr;

}
