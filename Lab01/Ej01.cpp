#include <iostream>
#include <string>
using namespace std;

class Animal {
    string nombre;
    public:
        Animal() {};
        Animal(string name): nombre(name) {}
        virtual void dormir() = 0;
        string getNombre();
        void setNombre(string name);
};
string Animal::getNombre() {return nombre;}
void Animal::setNombre(string name) {nombre = name;}

class Perro : public Animal {
    public:
        Perro() {};
        Perro(string name): Animal(name) {}
        void dormir() override {cout << getNombre() << " esta durmiendo" << endl;}
        void ladrar();
};
void Perro::ladrar() {cout << getNombre() << " esta ladrando" << endl;}

int main() {
    Perro p1("El enorme perro");
    p1.dormir();
    p1.ladrar();
}