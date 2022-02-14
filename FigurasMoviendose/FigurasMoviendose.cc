#include <esat/window.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/sprite.h>
#include <esat/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ESAT/math.h>


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
