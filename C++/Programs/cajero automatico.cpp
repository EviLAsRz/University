#include <iostream>

using namespace std;

int main(){
	int saldo_inicial=1000;
	int op;
	float extra,retiro,saldo = 0;
	cout<<"Bienvenido a tu cajero virtual"<<endl;
	cout<<"1. Ingresar dinero en la cuenta."<<endl;
	cout<<"2. Retirar dinero de la cuenta."<<endl;
	cout<<"3. Salir del menu.\n"<<endl;
	cout<<"Opcion: ";
	cin>>op;
	
	
	switch(op){
		case 1: cout<<"Por favor, indique la cantidad a ingresar: ";
				cin>>extra;
				saldo=saldo_inicial+extra;	
				cout<<"Dinero actual en la cuenta: "<<saldo;break;
				
		case 2:	cout<<"Por favor, indique la cantidad a retirar: ";
				cin>>retiro;
				if(retiro > saldo_inicial){
					cout<<"Error.";
				}else {
					saldo=saldo_inicial-retiro;
					cout<<"Dinero actual en la cuenta: "<<saldo;
				}
				break;
		case 3: break;
		}
	return 0;
}
