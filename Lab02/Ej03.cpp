#include <iostream>
#include <concepts>
using namespace std;

template <typename T>
requires std::integral<T> || std::floating_point<T>
class ArregloNumerico {
private:
    T datos[5];
public:
    void modificar(int posicion, T valor) {
        datos[posicion] = valor;
    }
    T obtener(int posicion) {
        return datos[posicion];
    }
};

int main() {
    ArregloNumerico<int> notas;
    notas.modificar(0, 20);
    
    ArregloNumerico<double> precios;
    precios.modificar(0, 19.99);

    ArregloNumerico<string> listaNombres;
    
    cout << "Nota guardada: " << notas.obtener(0) << endl;
    return 0;
}