#include <iostream>
#include "funcs.h"
#include "matrix.h"
#include "vec.h"

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
    default:
        return 0;
    }

}