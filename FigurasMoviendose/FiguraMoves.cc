#include <esat/window.h>
#include <esat/draw.h>
#include <esat/sprite.h>
#include <esat/input.h>
#include <esat/time.h>

#include <stdio.h>
#include <stdlib.h>

#include <math.h>

struct TColor{
  int r, g, b;
};

struct TCoordenadas{
  float x, y;
};

struct TFigura{
  int puntos;
  TCoordenadas posicion;
  TColor color;
  int peso,angulo;
};



const int ventanaX=800;
const int ventanaY=600;

const int gravedad=2;

#define M_PI 3.14159265358979323846;

TFigura r,*BloqueFiguras;

int TotalFiguras=0;
int velocidad=2,incremento=25;

FILE *f;

void Rotar(float *x, float *y, float cx, float cy, float dangulo){

  float dx = *x - cx, dy = *y - cy, r = sqrt(dx*dx + dy*dy), a = atan2(dy, dx);
  a -= dangulo / 180 * M_PI;
  *x = cx + r*cos(a);
  *y = cy + r*sin(a);
}

void CargaFiguras(){

  if((f=fopen("figuras.dat","rb"))==NULL){
    //Creacción fichero figuras
    f=fopen("figuras.dat","wb");
    fclose(f);
  }else{
    while(fread(&r,sizeof(r),1,f)){
      *(BloqueFiguras+TotalFiguras)=r;
      TotalFiguras++;
      BloqueFiguras=(TFigura*)realloc(BloqueFiguras,(TotalFiguras+1)*sizeof(TFigura));
      //TotalFiguras+1 para reservar tamaño desde 1 no desde cero.
    }
  }
}

void DibujaFigura(TFigura r){

  float *p=NULL;

  p=(float*)malloc((r.puntos+1)*2*sizeof(float));

  switch(r.puntos){
    //Cuadrado 4 puntos
    case 4:*(p+0)=r.posicion.x;
           *(p+1)=r.posicion.y;
           *(p+2)=r.posicion.x+incremento;
           *(p+3)=r.posicion.y;
           *(p+4)=r.posicion.x+incremento;
           *(p+5)=r.posicion.y+incremento;
           *(p+6)=r.posicion.x;
           *(p+7)=r.posicion.y+incremento;
           *(p+8)=*(p+0);
           *(p+9)=*(p+1);
            break;
    //Triangulo 3 puntos
    case 3:*(p+0)=r.posicion.x;
           *(p+1)=r.posicion.y;
           *(p+2)=r.posicion.x+incremento/2;
           *(p+3)=r.posicion.y+incremento;
           *(p+4)=r.posicion.x-incremento/2;
           *(p+5)=r.posicion.y+incremento;
           *(p+6)=*(p+0);
           *(p+7)=*(p+1);
            break;
  }


//Rotación de los puntos generados por pares (x,y)
  for (int i = 0; i <r.puntos*2;i+=2){
    Rotar((p+i),(p+i+1),*(p+0),*(p+1),r.angulo);
  }


  esat::DrawSetStrokeColor(r.color.r,r.color.g,r.color.b,255);
  esat::DrawSetFillColor(r.color.r,r.color.g,r.color.b);
  esat::DrawSolidPath(p,r.puntos+1);
  free(p);
}

void ComprobarGuardado(){

  if (esat::IsKeyDown('S')){
    f=fopen("figuras.dat","wb");
    for(int i=0;i<TotalFiguras;++i){
    	fwrite(BloqueFiguras+i,sizeof(TFigura),1,f);


    }
    fclose(f);
    }
}

void ComprobarLado(){

	if (esat::IsKeyPressed('Z')&&incremento>1){
    incremento--;

    }
	if (esat::IsKeyPressed('X')){
    incremento++;

    }
}

void AplicaDesplazamiento(TFigura *f){


	if (esat::IsSpecialKeyPressed(esat::kSpecialKey_Right)){
		if ((*f).posicion.x>800){
			(*f).posicion.x = 0;
		}

		(*f).posicion.x += velocidad;
	}
	if (esat::IsSpecialKeyPressed(esat::kSpecialKey_Left)){
		if ((*f).posicion.x < 0){
			(*f).posicion.x = 800;
		}
		(*f).posicion.x -= velocidad;
	}

  if (esat::IsSpecialKeyPressed(esat::kSpecialKey_Space)){
      (*f).angulo += 4;
    }

  if ((*f).posicion.y>600){
      (*f).posicion.y = 0;
    }
  if ((*f).posicion.y<0){
      (*f).posicion.y = 600;
    }



  (*f).posicion.y+= gravedad+(*f).peso;
}

void DibujaTodasFiguras(){

 for(int i=0;i<TotalFiguras;i++){
  AplicaDesplazamiento((BloqueFiguras+i)); //&*(BloqueFiguras+i)
  DibujaFigura(*(BloqueFiguras+i));
 }
}


void DetectaPulscionRaton(){

  if(esat::MouseButtonDown(0)){
    *(BloqueFiguras+TotalFiguras)={4,(float)esat::MousePositionX(),(float)esat::MousePositionY(),
                                  {rand()%256,rand()%255,rand()%255},
                                   rand()%10,0};
      TotalFiguras++;
      BloqueFiguras=(TFigura*)realloc(BloqueFiguras,(TotalFiguras+1)*sizeof(TFigura));
      //TotalFiguras+1 para reservar tamaño desde 1 no desde cero.
    }

    if(esat::MouseButtonDown(1)){
    *(BloqueFiguras+TotalFiguras)={3,(float)esat::MousePositionX(),(float)esat::MousePositionY(),
                                  {rand()%256,rand()%255,rand()%255},
                                   rand()%10,0};
      TotalFiguras++;
      BloqueFiguras=(TFigura*)realloc(BloqueFiguras,(TotalFiguras+1)*sizeof(TFigura));
      //TotalFiguras+1 para reservar tamaño desde 1 no desde cero.
    }
}

int esat::main(int argc, char **argv) {

  double current_time,last_time;
  unsigned char fps=25;



  esat::WindowInit(ventanaX,ventanaY);
  WindowSetMouseVisibility(true);
  BloqueFiguras=(TFigura*)malloc(1*sizeof(TFigura));
  CargaFiguras();
  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {
    esat::DrawBegin();
    last_time = esat::Time();
    esat::DrawClear(0,0,0);
    esat::DrawSetStrokeColor(255,128,0, 255);

    DetectaPulscionRaton();
    ComprobarGuardado();
    ComprobarLado();
    DibujaTodasFiguras();

    esat::DrawEnd();
    do{
    current_time = esat::Time();
    }while((current_time-last_time)<=1000.0/fps);

    esat::WindowFrame();
  }
  free(BloqueFiguras);
  esat::WindowDestroy();
  return 0;
}



/* Ejemplo de sintaxis para acceso a contenido de puntero
   direccionado a struct con offset (desplazamiento) y accediendo a un campo concreto

    (*(BloqueFiguras+i)).peso=10;  Notación con punto

      (BloqueFiguras+i)->peso=10;  Notación con flecha

*/
