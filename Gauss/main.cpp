#include <iostream>
#include "vector.h"
#include "funcs.h"
using namespace std;


int main() {
    int choice;
    int n;
    cout << "Enter typename:\n 1. double;\n 2. float;\n 3. int\n";
    cin >> choice;
    cout << "Enter size: ";
    cin >> n;
    switch (choice) {
        case 1:
            solver<double>(n);
            break;
        case 2:
            solver<float>(n);
            break;
        case 3:
            solver<int>(n);
            break;
        default:
            solver<double>(n);
            break;
    }
    return 0;
}
