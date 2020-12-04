#include <iostream>

using namespace std;

int main(){
    int numeros[100],n;
    cout<<"Introduce el numero de elementos del vector: ";
    cin>>n;
    for(int i=0;i<n;i++){
        cout<<"Digite un numero: ";
        cin>>numeros[i];
    }

    for(int i=0;i<n;i++){
        cout<<"Elemento "<<i<<" del vector: "<<numeros[i];
    }
    return 0;
}
