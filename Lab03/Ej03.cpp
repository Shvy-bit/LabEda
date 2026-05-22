#include <iostream>
using namespace std;

int main() {
    int n = 5;
    int* arr = new int[n];
    int i = 0;
    while (i < n) {
        arr[i] = i + 1;
        i++;
    }
    i = 0;
    while (i < n) {
        cout << arr[i] << " ";
        i++;
    }
    delete[] arr;
    return 0;
}
