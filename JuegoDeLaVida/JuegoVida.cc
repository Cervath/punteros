#include <esat/window.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/sprite.h>
#include <esat/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ESAT/math.h>

struct Valores{
  int vida1,vida2,dimension;
  float tamano;
};
struct Celula{
bool lifeNow,lifeAfter;
};

Valores valores;
Celula *celula=nullptr;
//
unsigned char fps=2;
//
double current_time,last_time;
//
bool stop=true;
//FUNCIONES
int acceso(int i, int j){
  int dim=valores.dimension+2;
  return i*dim+j;
}

bool seeGeneration2(Celula c,int i,int j){

int celulasVivas=0;
int posX=0,posY=0;
if ((*(celula+acceso(i-1,j-1))).lifeNow)celulasVivas++;
if ((*(celula+acceso(i-1,j))).lifeNow)celulasVivas++;
if ((*(celula+acceso(i-1,j+1))).lifeNow)celulasVivas++;
if ((*(celula+acceso(i,j-1))).lifeNow)celulasVivas++;
if ((*(celula+acceso(i,j+1))).lifeNow)celulasVivas++;
if ((*(celula+acceso(i+1,j-1))).lifeNow)celulasVivas++;
if ((*(celula+acceso(i+1,j))).lifeNow)celulasVivas++;
if ((*(celula+acceso(i+1,j+1))).lifeNow)celulasVivas++;

if(celulasVivas==3)return true;

return false;
}

bool seeGeneration(Celula c,int i,int j){

int celulasVivas=0;
int posX=0,posY=0;
if ((*(celula+acceso(i-1,j-1))).lifeNow)celulasVivas++;
if ((*(celula+acceso(i-1,j))).lifeNow)celulasVivas++;
if ((*(celula+acceso(i-1,j+1))).lifeNow)celulasVivas++;
if ((*(celula+acceso(i,j-1))).lifeNow)celulasVivas++;
if ((*(celula+acceso(i,j+1))).lifeNow)celulasVivas++;
if ((*(celula+acceso(i+1,j-1))).lifeNow)celulasVivas++;
if ((*(celula+acceso(i+1,j))).lifeNow)celulasVivas++;
if ((*(celula+acceso(i+1,j+1))).lifeNow)celulasVivas++;

if(celulasVivas==4)return true;

return false;
}

void drawCell(float x,float y){
  float square[10]{x,y,x+valores.tamano,y,x+valores.tamano,y+valores.tamano,x,y+valores.tamano,x,y};
  esat::DrawSetFillColor(255,0,0);
  esat::DrawSolidPath(square,4,1);
}

void drawLife(){
int x=0,y=0;
if (esat::IsSpecialKeyDown(esat::kSpecialKey_Space)) {
  if(stop)stop=false;
  else stop=true;
}


for (size_t i =0; i < valores.dimension; i++) {
  for (size_t j =0; j < valores.dimension; j++) {
      if ((*(celula+acceso(i,j))).lifeNow) {
        drawCell(x,y);
        if(seeGeneration((*(celula+acceso(i,j))),i,j))(*(celula+acceso(i,j))).lifeAfter=true;
        else (*(celula+acceso(i,j))).lifeAfter=false;
      }
      else{
        if(seeGeneration2((*(celula+acceso(i,j))),i,j))(*(celula+acceso(i,j))).lifeAfter=true;
      }

      x+=valores.tamano;
    }
    x=0;
    y+=valores.tamano;
  }
  for (size_t i = 0; i < valores.dimension; i++) {
    for (size_t j = 0; j < valores.dimension; j++) {
      (*(celula+acceso(i,j))).lifeNow=(*(celula+acceso(i,j))).lifeAfter;
    }
  }

}

int bringLife(){
  if(rand()%2==0)return true;
  else return false;
}

void crearPoblacion(){
  int d=(valores.dimension*valores.dimension)+2;
  celula=(Celula*) malloc(sizeof(Celula*)*d);

  for (size_t i = 0; i < d; i++) {
    (*(celula+i)).lifeNow=false;
    (*(celula+i)).lifeAfter=false;
  }
  for (size_t i = 2; i < valores.dimension; i++) {
    for (size_t j = 2; j < valores.dimension; j++) {
      (*(celula+acceso(i,j))).lifeNow=bringLife();
    }
  }

}

void liberarPunteros(){
  free(celula);celula=nullptr;
}

int esat::main(int argc, char **argv) {


	esat::WindowInit(800,800);
	WindowSetMouseVisibility(true);

valores.tamano=(800)/atoi(*(argv+1));
valores.dimension=atoi(*(argv+1));
	srand (time(NULL));
  crearPoblacion();
    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	last_time = esat::Time();
    	esat::DrawBegin();
    	esat::DrawClear(0,0,0);


      drawLife();


    	esat::DrawEnd();
    	//Control fps
    	do{
    		current_time = esat::Time();
    	}while((current_time-last_time)<=1000.0/fps);
    	esat::WindowFrame();
  }


  esat::WindowDestroy();

  return 0;

}
