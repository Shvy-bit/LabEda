#pragma once
using namespace std;
namespace Card {
    class Card {
        private:
            int repeticiones;
        public:
            Card(int num): repeticiones(num) {}
            int repet() {
                return repeticiones;
            }
    };
}