#include <iostream>
#include <clocale>
#include "Matrix.h"
#include "Solver.h"
#include "Vector.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    size_t n;
    cout << "Введите размерность вектора и квадратной матрицы: ";
    cin >> n;

    int a;
    cout << "Выберите тип данных:\n 1. float\n 2. double\n";
    cin >> a;

    switch (a) {
    case 1: {
        solver<float>(n);
        break; }
    case 2: {
        solver<double>(n);
        break; }
    }
    return 0;
}