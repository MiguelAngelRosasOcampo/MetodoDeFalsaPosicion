#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void mFalsaPosicion(int*,double*,double,short); //Prototipo de la funcion.

int main(void)
{	
	short grado, i, j, nuevoTam = 0;
	char coeficienteAscii = 'a';
	int *exponentes;
	double *coeficientes, terminoIndep;
	
	do //Bucle para que usuario ingrese el grado del polinomio.
	{
		setbuf(stdin,NULL); 
		
		printf("\n\nIngresa el grado del polinomio: ");
		scanf("%hd",&grado);
		
	}while(grado < 1 || grado > 12); //El grado debe de ser mayor a 0 y menor a 12.
	
	printf("\nEstructura de la expresi%cn algebraica\n\n        ",162);
	for(i=0; i<grado-1; i++) //Muestra el grado de la variable X.
		printf(" %2d  ",grado-i);
		
	printf("\n %c(x) = ",159);
	for(i=0; i<grado; i++) //Ciclo para mostrar el coeficiente y la variable X.
		printf("%cx + ",coeficienteAscii++);
		
	printf("%c\n",coeficienteAscii++);	//Muestra el término independiente.
	
	coeficientes = (double*) malloc(grado * sizeof(double)); //Reservar espacio en la memoria.

	if(!coeficientes) //Condicional en caso de que no haya suficiente espacio.
	{
		printf("",getchar(),getchar(),printf("\n\nNo se ha podido reservar suficiente memoria."));
		exit(-1);
	}

	exponentes = (int*) malloc(grado*sizeof(int));
	
	if(!exponentes) //Condicional en caso de que no haya suficiente espacio.
	{
		printf("",getchar(),getchar(),printf("\n\nNo se ha podido reservar suficiente memoria."));
		exit(-1);
	}
			
	for(i=0; i<grado; i++)//Bucle para pedirle al usuario los coeficientes de las variables.
		printf("",scanf("%lf",(coeficientes+i)), printf("\nIngresa el coeficiente de la variable de grado %d: ",grado-i));
	
	printf("\n\nAhora ingresa el t%crmino independiente: ",130);
	scanf("%lf",&terminoIndep);
	
	for(j=0,i=0; i<grado; i++) //Bucle guardar las posiciones donde el coeficiente no sea 0.
		if(*(coeficientes + i)) //Verifica que el coeficiente en esa posición no sea 0.
		{
			*(exponentes + (j)) = grado - i; //Se guarda el grado en la posición j.
			*(coeficientes + (j++)) = *(coeficientes + i); //Se guarda el coeficiente en la posición j.
			nuevoTam++; //Variable para el nuevo tamaño del arreglo.
		}
			
	coeficientes = (double*) realloc(coeficientes, (sizeof(double)*nuevoTam));//Nuevo tamaño
	
	if(!coeficientes)	
	{
		printf("",getchar(),getchar(),printf("\n\nNo se ha podido reservar suficiente memoria."));
		exit(-1);
	}
			
	mFalsaPosicion(exponentes, coeficientes, terminoIndep, nuevoTam); //Función que calcula la raíz.
	
	free(coeficientes); //Liberar la memoria dinámica.
	free(exponentes);
	
	return 0;
}

void mFalsaPosicion(int *exponentes, double *coeficientes , double terminoIndep, short nuevoTam)
{
	double xl, xu, xr, errorAprox, producto;
	double fxl, fxu, fxr, xAnterior, xNuevo;
	int nIteraciones, i = 0, j = 0;

	printf("\n\nIngresa el l%cmite inferior (Xl): ",161);
	scanf("%lf",&xl);
	
	do //Bucle para que usuario ingrese un valor mayor al límite inferior.
	{
		setbuf(stdin, NULL); //Limpiar el buffer.
		
		printf("\nIngresa el l%cmite superior (Xu): ",161);
		scanf("%lf",&xu);
		
		if(xu <= xl)//Condicional para verificar si el límite inferior es mayor que el límite superior.
			printf("",getchar(),getchar(), printf("Debes de ingresar un valor mayor a %lf.",xl));

	}while(xu <= xl);
	
	do //Bucle para pedir la cantidad de iteraciones.
	{
		printf("\n\nIngresa la cantidad de iteraciones: ");
		scanf("%d",&nIteraciones);
	
	}while(nIteraciones < 1);	
			
	printf("\nTu expresi%cn algebraica es: \n\n\t\t\t%c(x) = ",162, 159);
	for(j=0; j<nuevoTam; j++)//Ciclo para mostrar la expresión que usuario ingresó.
		if(*(exponentes + j))
			*(coeficientes+j)!=1 ? printf("%+gx^%d ",*(coeficientes+j), *(exponentes + j)) : printf("x^%d ",*(exponentes + j));
			
	if(terminoIndep != 0)
		printf("%+g\n",terminoIndep);
		
	else printf("\n");
	
	for(j=0; j<21; j++)
		printf("%c%c%c%c",(!j ? '\t': 95), 95, 95, 95);
		
	printf("\n\tIteraci%cn\tXl\t\tXu\t\tXr\t\tError Aproximado(%%)\n",162);
	
	for(j=0; j<21; j++)
		printf("%c%c%c%c",(!j ? '\t': 196), 196, 196, 196);
	
	while(nIteraciones > i)
	{
		fxl = 0, fxu = 0;

		printf("\n\n\t%d \t\t%lf \t%lf \t%lf",i, xl, xu, xr);//Muestra los datos.
				
		for(j=0; j<nuevoTam; j++) //Evalúa la función con el límite Xl.
			fxl += *(coeficientes+j) * pow(xl,*(exponentes+j));
			
		fxl += terminoIndep; //Le suma el término independiente.
	
		for(j=0; j<nuevoTam; j++) //Evalúa la función con el límite Xu.
			fxu += *(coeficientes+j) * pow(xu,*(exponentes+j));
						
		fxu += terminoIndep; //Le suma el término independiente.
		
		producto = fxu * fxl; //Hace el producto para verificar que exista al menos una raíz.
		
		if(producto > 0) //Si el producto es positivo, entonces no hay raices.
			break;
			
		if(fxl - fxu) //verifica que la diferencia entre fxl y fxu no sea 0.
			xr = xu - ( ((fxu)*(xl - xu)) / (fxl - fxu) ); //Fórmula del método de falsa posición.
		
		else break;
		
		for(j=0; j<nuevoTam; j++) //Evalúa la función con el valor de Xl.
			fxr += *(coeficientes+j) * pow(xr,*(exponentes+j));
			
		fxr += terminoIndep; //Le suma el término independiente.		
		
		producto = fxr * fxu; //realiza el producto de las evaluaciones.
		
		producto < 0 ? (xl = xr) : (xu = xr); //Asigna el nuevo límite.	
	
		xAnterior = xNuevo; //Asignará el valor anterior de xNuevo después de la segunda iteración.
		xNuevo = xr; //Asignar el nuevo valor de xR a xNuevo.
		
		if(i && xNuevo) //A partir de la segunda iteración, se obtendrá el error apróximado.
			errorAprox = ((xNuevo-xAnterior) / xNuevo) * 100;
			
		if(i++) //Muestra el error apróximado a partir de la segunda iteración.
			printf("\t%lf",errorAprox < 0 ? errorAprox*-1 : errorAprox);
	}
	
	getchar(); //Pausar.
	getchar();	
}
