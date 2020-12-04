/*
Escribe un programa en C++ que lea de la entrada estandar dos número 
y muestre en la salida estándar su suma, resta, multiplicación y división.
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
	cout<<"La multiplicación es: "<<mul<<endl;
	cout<<"La división es: "<<div<<endl;
	
	return 0;
}
