#include <iostream>

using namespace std;

int main(){
	float a,b;
	float exp=0;
	cout<<"Ingrese dos numeros: ";
	cin>>a>>b;
	
	exp=(a/b)+1;
	
	cout.precision(2);
	cout<<"\nEl resultado de la operacion es: "<< exp<<endl;
	
	return 0;
}
