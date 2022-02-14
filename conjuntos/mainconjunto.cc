#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include "conjunto.cc"

TConjunto *conjunto1=nullptr, *conjunto2=nullptr, *resultadoU=nullptr, *resultadoI=nullptr;

int main(){

    conjunto1=CrearConjunto();
    conjunto2=CrearConjunto();
    resultadoU=CrearConjunto();
    resultadoI=CrearConjunto();

    IncluirConjunto(&conjunto1,3);
    IncluirConjunto(&conjunto1,10);
    IncluirConjunto(&conjunto1,3);
    IncluirConjunto(&conjunto1,15);
    IncluirConjunto(&conjunto1,3);
    IncluirConjunto(&conjunto1,30);

    printf("\n\nVolcado conjunto 1\n");
    MuestraConjunto(conjunto1);

    IncluirConjunto(&conjunto2,18);
    IncluirConjunto(&conjunto2,10);
    IncluirConjunto(&conjunto2,35);
    IncluirConjunto(&conjunto2,1);
    IncluirConjunto(&conjunto2,3);
    IncluirConjunto(&conjunto2,45);

    printf("\n\nVolcado conjunto 2\n");
    MuestraConjunto(conjunto2);

    UnionConjunto(conjunto1,conjunto2,&resultadoU);

    printf("\n\nVolcado Union\n");
    MuestraConjunto(resultadoU);

    InterseccionConjunto(conjunto1,conjunto2,&resultadoI);

    printf("\n\nVolcado Interseccion\n");
    MuestraConjunto(resultadoI);

	return 0;
}
