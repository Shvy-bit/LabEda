#include <iostream>
using namespace std;
class CircularList {
    public:
    class Node {
        public:
        int data;
        Node* next;
        Node(int d): data(d), next(nullptr) {}
    };
    Node* head = nullptr;
    CircularList() {
        head = nullptr;
    }
    void insert(int data);
    void printList();
};
void CircularList::insert(int data) {
    Node* newNode = new Node(data);
    if (head == nullptr) {
        head = newNode;
        newNode->next = head;
    } else {
        Node* last = head;
        while (last->next != head) {
            last = last->next;
        }
        last->next = newNode;
        newNode->next = head;
    }
}
void CircularList::printList() {
    if (head == nullptr) return;
    Node* current = head;
    cout << "CircularList: ";
    do {
        cout << current->data << " ";
        current = current->next;
    } while (current != head);
    cout << endl;
}
int main() {
    CircularList list;
    for(int i = 0; i < 12; i++) {
        list.insert(i + 1);
    }
    list.printList();
    return 0;
}