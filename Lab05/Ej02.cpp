#include <iostream>
#include <stack>

using namespace std;

class ColaConPilas {
    private:
        stack<int> pilaPrincipal;
        stack<int> pilaAuxiliar;
    public:
        void queue_push(int x) {
            while (!pilaPrincipal.empty()) {
                pilaAuxiliar.push(pilaPrincipal.top());
                pilaPrincipal.pop();
            }
            pilaPrincipal.push(x);
            while (!pilaAuxiliar.empty()) {
                pilaPrincipal.push(pilaAuxiliar.top());
                pilaAuxiliar.pop();
            }
        }
        void queue_pop() {
            if (pilaPrincipal.empty()) {
                cout << "La cola esta vacia." << endl;
                return;
            }
            pilaPrincipal.pop();
        }
        int queue_front() {
            if (pilaPrincipal.empty()) {
                return -1; 
            }
            return pilaPrincipal.top();
        }
        bool empty() {
            return pilaPrincipal.empty();
        }
};
int main() {
    ColaConPilas miCola;
    
    miCola.queue_push(5);
    miCola.queue_push(10);
    miCola.queue_push(15);

    cout << "Frente de la cola: " << miCola.queue_front() << endl; 
    miCola.queue_pop();
    cout << "Frente despues de un pop: " << miCola.queue_front() << endl; 

    return 0;
}