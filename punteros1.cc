#include <stdio.h>
#include <stdlib.h>
int *p, *q,numero1=10,numero2=20;

void funcion(){
  int local=100,local2=200;
  p=&local;
  q=&local2;
  printf("%p %p %d \n",p,&p,*p);
  printf("%p %p %d \n",q,&q,*q);
}
int main(int argc, char const *argv[]) {
  printf(" Variables lcoales a funcion\n");
  funcion();
  printf("Variables  globales\n");
  p=&numero1;
  q=&numero2;
  printf("%p %p %d \n",p,&p,*p);
  printf("%p %p %d \n",q,&q,*q);
  return 0;
}
