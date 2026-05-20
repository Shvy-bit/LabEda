#include <iostream>
#include <string>

class Vehiculo {
    public:
        virtual ~Vehiculo() {}
        virtual void iniciar() = 0;
        virtual void detener() = 0;
}; //Clase abstracta pura, sus metodos no se pueden instanciar sin modificarse antes

class Auto : public Vehiculo {
    private:
        std::string marca;
    public:
        Auto(std::string _marca) : marca(_marca) {}
            void iniciar() override {
            std::cout << "El auto " << marca << " ha encendido el motor." << std::endl;
        }
        void detener() override {
            std::cout << "El auto " << marca << " ha frenado y se ha detenido." << std::endl;
        }
}; //Clase auto que usa Vehiculo como base para crearse
int main() {
    Vehiculo* miAuto = new Auto("Toyota");

    miAuto->iniciar();
    miAuto->detener();
    delete miAuto;

    return 0;
}