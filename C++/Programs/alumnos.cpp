/*
	En una clase de 5 alumnos se han realizado tres examenes y se requiere determinar el numero de:
	a) Alumnos que aprobaron todos los examenes
	b) Alumnos que aprobaron al menos un examen
	c) Alumnos que aprobaron solo el ultimo examen
*/
#include <iostream>

using namespace std;

int main(){
	
	int n=5;
	bool var;
	for(int i=0;i<n;i++){
		for(int j=0;j<3;j++){
		cout<<"Alumno "<<i+1<<" aprobo "<<"el examen "<<j+1<<"?"<<endl;
		cin>>var;
		}
	}
	
	return 0;
}



