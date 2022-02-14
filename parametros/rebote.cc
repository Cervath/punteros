#include <esat/window.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/sprite.h>
#include <esat/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ESAT/math.h>

//ESTRUCTURAS
struct Burbuja{
esat::Vec2 posicion,direccion;
int color,forma;

};

//DATOS
//bloques
Burbuja *burbujas=nullptr;
esat::SpriteHandle *spritesBurbujas=nullptr,*spritesColores=nullptr;
//
unsigned char fps=25;
//
double current_time,last_time;
//
int g_numeroBurbujas=0,g_ancho,g_alto;


//FUNCIONES
//
void cargarSprites(){
spritesBurbujas=(esat::SpriteHandle*) malloc(sizeof(esat::SpriteHandle*)+2);
spritesColores=(esat::SpriteHandle*) malloc(sizeof(esat::SpriteHandle*)+2);

	*spritesBurbujas=esat::SpriteFromFile("./recursos/bola1.png");
	*(spritesBurbujas+1)=esat::SpriteFromFile("./recursos/bola2.png");
	*spritesColores=esat::SpriteFromFile("./recursos/azul.png");
	*(spritesColores+1)=esat::SpriteFromFile("./recursos/verde.png");


}
//
void cargarElementos(){

burbujas=(Burbuja*) malloc(sizeof(Burbuja*)*g_numeroBurbujas);

	for (size_t i = 0; i < g_numeroBurbujas; i++) {
		(*(burbujas+i)).posicion.x=rand()%g_ancho;
		(*(burbujas+i)).posicion.y=rand()%g_alto;
		(*(burbujas+i)).direccion.x=2-rand()%6;
		(*(burbujas+i)).direccion.y=2-rand()%6;
		if (rand()%2==0) {
			(*(burbujas+i)).forma=0;
		}
		else (*(burbujas+i)).forma=1;
		if (rand()%2==0) {
			(*(burbujas+i)).color=0;
		}
		else (*(burbujas+i)).color=1;
	}

}
//Dibujamos el sprite de una bola
void dibujarBurbujas(Burbuja *b){
	b->posicion.x+=b->direccion.x;b->posicion.y+=b->direccion.y;
	esat::DrawSprite(*(spritesColores+b->color),(int)b->posicion.x,(int)b->posicion.y);
	esat::DrawSprite(*(spritesBurbujas+b->forma),(int)b->posicion.x,(int)b->posicion.y);

}
//Miramos su una figura he tocado un borde
void detectarBorde(Burbuja *b){
	if(b->posicion.x>g_ancho||b->posicion.x<0)b->direccion.x*=-1;
	if(b->posicion.y>g_alto||b->posicion.y<0)b->direccion.y*=-1;
}
//Dibujamos los elementos del bloque de burbujas
void dibujarElementos(){
	for (size_t i = 0; i < g_numeroBurbujas; i++) {
		detectarBorde(burbujas+i);
		dibujarBurbujas(burbujas+i);
}
	//esat::DrawSprite(*(spritesBurbujas+0),200,200);
}

//Liberamos los punteros del programa
void liberarSprites(){
	for (size_t i = 0; i < 2; i++) {
		esat::SpriteRelease((spritesBurbujas+1));
	}
	for (size_t j = 0; j < 2; j++) {
		esat::SpriteRelease((spritesColores+1));
	}
}

void liberarBloques(){
	free(burbujas);burbujas=nullptr;
	free(spritesBurbujas);spritesBurbujas=nullptr;
	free(spritesColores);spritesColores=nullptr;
}

int esat::main(int argc, char **argv) {

//
g_ancho=atoi(*(argv+1)),g_alto=atoi(*(argv+2)),g_numeroBurbujas=atoi(*(argv+3));


	esat::WindowInit(g_ancho,g_alto);
	WindowSetMouseVisibility(true);

	cargarSprites();
	cargarElementos();
	srand (time(NULL));

    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	last_time = esat::Time();
    	esat::DrawBegin();
    	esat::DrawClear(0,0,0);

			dibujarElementos();

    	esat::DrawEnd();
    	//Control fps
    	do{
    		current_time = esat::Time();
    	}while((current_time-last_time)<=1000.0/fps);
    	esat::WindowFrame();
  }


  esat::WindowDestroy();
	liberarBloques();
	liberarSprites();

  return 0;

}
