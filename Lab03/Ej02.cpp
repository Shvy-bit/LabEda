#include <iostream> //
using namespace std;
int main() {
    int valor;
    cout << "Ingrese un numero: ";
    cin >> valor;

    int *puntero = &valor;

    cout << "Direccion de memoria: " << puntero << endl;
    cout << "Contenido en esa direccion: " << *puntero << endl;

    return 0;
}
