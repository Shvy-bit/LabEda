#include <iostream>
#include <string>
using namespace std;

class Auto {
    string modelo;
    int year;
    public:
        Auto():
            modelo("Desconocido"), year(0) {};
        Auto(string _modelo, int _year):
            modelo(_modelo),year(_year) {}
        void mostrar() {
            cout << "El auto creado es de modelo " << modelo << " y del año " << year << endl;
        }
};
int main() {
    Auto* miAuto = new Auto();
    miAuto->mostrar();
    delete miAuto;
    miAuto = new Auto("Toyota", 2025);
    miAuto->mostrar();
    delete miAuto;
    return 0;
}