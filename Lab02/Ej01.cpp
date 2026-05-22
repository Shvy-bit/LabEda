#include <iostream>
using namespace std;

class Personaje {
public:
    void correr() { cout << "El personaje esta corriendo." << endl; }
};

class Hechizo {
public:
    void lanzarHechizo() { cout << "¡Lanzando una bola de fuego!" << endl; }
};

class MagoFuego : public Personaje, public Hechizo {};

int main() {
    MagoFuego miMago;
    miMago.correr();
    miMago.lanzarHechizo();
    return 0;
}