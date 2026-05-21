#include <iostream>
using namespace std;

enum class EstadoSemaforo {
    ROJO,
    AMARILLO,
    VERDE
};

int main() {

    EstadoSemaforo luzActual = EstadoSemaforo::ROJO;

    if (luzActual == EstadoSemaforo::ROJO) {
        cout << "¡Detente!" << endl;
    }

    return 0;
}