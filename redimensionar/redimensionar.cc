
#include <stdio.h>
#include <stdlib.h>

int *p=nullptr,num=20;
void iniciarEspacio(){
  p=(int*) malloc(sizeof(int)+20);
}

void redimensionarEspacio(){
  num+=10;
p=(Figura*)realloc(p,num * sizeof(Figura));

}

void llenarEspacio() {
  for (size_t i = 0; i < num; i++) {
    *(p+i)=100+i;
  }
}

void verEspacio(){
for (size_t i = 0; i < num; i++) {
  printf("[%p] %d\n",&p+i,*p +i);
}
}
void liberarPuntero(){
  free(p);p=nullptr;
}

int main(int argc, char const *argv[]) {
iniciarEspacio();
llenarEspacio();
verEspacio();
redimensionarEspacio();
verEspacio();
liberarPuntero();
  return 0;
}
