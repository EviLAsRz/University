/*
Realize un programa que solicite al usuario que piense un numero entero entre en 1 y el 100. El programa debe generar un numero aleatorio en ese mismo rango[1-100], e indicarle
al usuario si el numero que digito es menor o mayor al numero aleatorio, asi hasta que lo adivine. Y por ultimo mostrarle el numero de intentos que les llevo.
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main(){
	int numero, dato, contador=0;
	
	srand(time(NULL)); //generar un numero aleatorio;	
	dato = 1 + rand()%(100);
	
	do{
		cout<<"Digite un numero: "; 
		cin>>numero;
		if(numero>dato){
			cout<<"EL numero a encontrar es menor.\n";
		}
		if(numero<dato){
			cout<<"El numero a encontrar es mayor.\n";
		}
		contador++;
	}while(numero != dato); //mientras el numero introducido sea distinto al numero generado.
	
	cout<<"Numero de intentos realizados: "<<contador;
	
	
	return 0;
}



