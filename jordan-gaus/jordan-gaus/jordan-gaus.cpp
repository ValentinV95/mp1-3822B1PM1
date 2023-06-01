#include <iostream>
#include <cmath>
#include "soluem.h"
#include "vector.h"
#include "matrix.h"
using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    int m, n;
    cout << "Введите тип данных" << endl;
    cout << "1 - int" << endl;
    cout << "2 - float" << endl;
    cout << "3 - double" << endl;
    cin >> n;
    cout << "Введите число строк квадратной матрицы" << endl;
    cin >> m;
    if (n == 1) {
        matrix <int> A(m);
        vector <int> B(m);
        soluem <int> a;
        a.zero(m, A, B);
    }
    if (n == 2) {
        matrix <float> A(m);
        vector <float> B(m);
        soluem<float> a;
        a.zero(m, A, B);
    }
    if (n == 3) {
        matrix <double> A(m);
        vector <double> B(m);
        soluem<double> a;
        a.zero(m, A, B);
    }
    return 0;
}

