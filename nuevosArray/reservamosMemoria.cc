#include <stdio.h>
#include <stdlib.h>

int *p=nullptr,num=0,numeros=0;

void verEspacio(){
for (size_t i = 0; i < num; i++) {
  printf("%d\n",*p +i);
}

}
void rellenarEspacio(){
for (size_t i = 0; i < num; i++) {
  printf("Escriba un numero\n");
  scanf("%d",p + i);
}

}

void preguntarUsuario(){

scanf("%d",&num);

p=(int*) malloc(sizeof(int*)+num);

rellenarEspacio();
}
void liberarPuntero(){
  if (p) {
      free(p);p=nullptr;
  }

}
int main(int argc, char const *argv[]) {

preguntarUsuario();
verEspacio();
liberarPuntero();
  return 0;
}
