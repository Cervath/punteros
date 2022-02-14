#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv) {
	//   argc continene el número de parámetros donde el primero es el nombre del programa
	// **argv contiene la lista de argumentos
	// *(argv+0) el el nombre del programa, *(argv+1) primer parámetro, etc

	if(argc!=3){
		printf("\n >> Error: Necesitas indicar dos operandos.\n");
		//exit(1); //Salida del programa o utilziamos condicional.

	}else{
		printf("Programa en ejecución:  %s , la suma de %s y %s es %d\n",*(argv+0), *(argv+1),*(argv+2),atoi(*(argv+1))+atoi(*(argv+2)));
	}

return 0;
}


/*

int main(int argc, char **argv) {
	//argc continene el número de parámetros donde el primero es el nombre del programa
	//**argv contiene la lista de argumentos *(argv+0) el el nombre del programa, *(argv+1) primer parámetro, etc

	if(argc!=3){
		printf("\n >> Error: Necesitas indicar dos operandos.\n");
		exit(1); //Salida del programa o utilziamos condicional.
	}

	printf("La suma de %s y %s es %d\n",*(argv+1),*(argv+2),atoi(*(argv+1))+atoi(*(argv+2)));


return 0;
}

*/
