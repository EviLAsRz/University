/*
IF AND IF ELSE utilizando las sentencias para resolver el siguiente problema: 

Sentencia if:

if(condicion) {
  instrucciones 1;
}else{
  instrucciones 2;
}
*/
#include <iostream>

using namespace std;

int main(){
	int n,dato=5;
	
	cout<<"Digite un numero: ";
	cin>>n;
	
	if(n != dato){
		cout<<"El numero ingresado no es 5.";
	}else{
		cout<<"El numero ingresado es 5."<<endl;
	}
	
	
	return 0;
}
