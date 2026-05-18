#include <iostream>
using namespace std;

class Animal {
    string nombre;
    public:
        Animal() {};
        Animal(string name):
            nombre(name) {}
            void dormir();
            string getNombre();
            void setNombre(string name);
};
string Animal::getNombre() {return nombre;}
void Animal::setNombre(string name) {nombre = name;};
void Animal::dormir() {
    cout << getNombre() << " esta durmiendo" << endl;
}

class Perro : public Animal {
    public:
        Perro() {};
        Perro(string name): Animal(name) {}
        void ladrar();
};
void Perro::ladrar() {
    cout << getNombre() << " esta ladrando" << endl;
};

int main() {
    Animal a1("Em");
    a1.dormir();
    Perro p1("El enorme perro");
    p1.dormir();
    p1.ladrar();
}