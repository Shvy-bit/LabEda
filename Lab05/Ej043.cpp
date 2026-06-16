#include <iostream>
#include <stack>
#include <string>

using namespace std;

enum class TipoLlave {
    Apertura,
    Cierre,
    Desconocido
};

TipoLlave obtenerTipo(char c) {
    if (c == '(' || c == '[' || c == '{') return TipoLlave::Apertura;
    if (c == ')' || c == ']' || c == '}') return TipoLlave::Cierre;
    return TipoLlave::Desconocido;
}

bool coinciden(char apertura, char cierre) {
    return (apertura == '(' && cierre == ')') ||
           (apertura == '[' && cierre == ']') ||
           (apertura == '{' && cierre == '}');
}

bool estanEquilibrados(string s) {
    stack<char> pila;

    for (int i = 0; i < s.length(); i++) {
        char caracter = s[i];
        TipoLlave tipo = obtenerTipo(caracter);

        switch (tipo) {
            case TipoLlave::Apertura:
                pila.push(caracter);
                break;
            case TipoLlave::Cierre:
                if (pila.empty()) return false;
                if (coinciden(pila.top(), caracter)) pila.pop();
                else { return false; }
                break;
            case TipoLlave::Desconocido:
                break;
        }
    }
    return pila.empty();
}

int main() {
    string expresion1 = "{[()]}";
    string expresion2 = "{[(])}";

    cout << "Expresion 1 " << expresion1 << " esta: " 
         << (estanEquilibrados(expresion1) ? "Equilibrada" : "Desequilibrada") << endl;

    cout << "Expresion 2 " << expresion2 << " esta: " 
         << (estanEquilibrados(expresion2) ? "Equilibrada" : "Desequilibrada") << endl;

    return 0;
}