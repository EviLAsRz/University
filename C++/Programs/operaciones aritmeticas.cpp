/*
Escribe un programa en C++ que lea de la entrada estandar dos n�mero 
y muestre en la salida est�ndar su suma, resta, multiplicaci�n y divisi�n.
*/
#include <iostream>

using namespace std;

int main(){
	
	int n1,n2,suma=0,resta=0,mul=0,div=0;
	
	cout<<"Introduce dos numeros: ";
	cin>>n1>>n2;
	
	suma=n1+n2;
	resta=n1-n2;
	mul=n1*n2;
	div=n1/n2;
	
	cout<<"La suma es: "<<suma<<endl;
	cout<<"La resta es: "<<resta<<endl;
	cout<<"La multiplicaci�n es: "<<mul<<endl;
	cout<<"La divisi�n es: "<<div<<endl;
	
	return 0;
}
