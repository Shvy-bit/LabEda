#include <iostream>
#include "PaqueteSimple/Card.h"

using namespace std;
using namespace Card;
int main() {
    Card::Card card1(3);
    cout << "El tamaño de la tarjeta creada es " << card1.repet() << endl;
    return 0;
}