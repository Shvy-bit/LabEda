#include <iostream>
#include <string>
using namespace std;
class Vehiculo {
    public:
        virtual ~Vehiculo() {}
        virtual void iniciar() = 0;
        virtual void detener() = 0;
}; //Clase abstracta pura, sus metodos no se pueden instanciar sin modificarse antes

class Auto : public Vehiculo {
    private:
        string marca;
    public:
        Auto(string _marca) : marca(_marca) {}
            void iniciar() override {
            cout << "El auto " << marca << " ha encendido el motor." << endl;
        }
        void detener() override {
            cout << "El auto " << marca << " ha frenado y se ha detenido." << endl;
        }
}; //Clase auto que usa Vehiculo como base para crearse
int main() {
    Vehiculo* miAuto = new Auto("Toyota");

    miAuto->iniciar();
    miAuto->detener();
    delete miAuto;

    return 0;
}