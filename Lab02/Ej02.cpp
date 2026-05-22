#include <iostream>
using namespace std;

class Dispositivo {
public:
    virtual void encender() {
        cout << "Iniciando sistema del dispositivo..." << endl;
    }
    virtual ~Dispositivo() {}
};

class Smartphone : public Dispositivo {
public:
    void encender() override {
        cout << "Mostrando logotipo de Android en la pantalla." << endl;
    }
};

int main() {
    Dispositivo* miCelular = new Smartphone();

    miCelular->encender();
    
    delete miCelular;

    return 0;
}