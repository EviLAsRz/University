#include <iostream>

using namespace std;

int main(){
	float a,b,c,d;
	float exp=0;
	
	cout<<"Introduce cuatro valores: ";
	cin>>a>>b>>c>>d;
	
	exp=(a+b)/(c+d);
	
	
	cout.precision(3);
	cout<<"\nEl resultado de la expresion es: "<<exp<<endl;
	
	return 0;
}
