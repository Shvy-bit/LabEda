#include <iostream>
#include <queue>

using namespace std;

int main() {
    priority_queue<int> pq;

    pq.push(10);
    pq.push(20);
    pq.push(15);

    cout << "Cima despues de insertar (10, 20, 15): " << pq.top() << endl;

    pq.pop();

    cout << "Cima despues de eliminar el elemento superior: " << pq.top() << endl;

    return 0;
}