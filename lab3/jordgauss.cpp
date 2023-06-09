// fff.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cstdlib>
#include <locale>
#include <math.h>
#include "class.h"

int main()
{
    setlocale(LC_ALL, "Rus");
    int m;
    cout << "Введите размер матрицы" << endl;
    cin >> m;
    int choice;
    cout << "Введите тип элементов матрицы:" << endl << "1 - float" << endl << "2 - double" << endl;
    cin >> choice;
    if (choice == 1)
    {
        matrix<float> a(m);
        vector<float> b(m);
        solver<float> x;
        cout << "Введите данные матрицы A" << endl;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < m; j++)
            {
                cin >> a.A[i][j];
            }
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < m; j++)
                cout << a.A[i][j] << " ";
            cout << endl;
        }
        cout << "Введите данные вектора B" << endl;
        for (int i = 0; i < m; i++)
        {
            cin >> b.B[i];
        }
        for (int i = 0; i < m; i++)
        {
            cout << b.B[i] << " ";
            cout << endl;
        }
        x.joga(m, a, b);
    }
    if (choice == 2)
    {
        matrix<double> a(m);
        vector<double> b(m);
        solver<double> x;
        cout << "Введите данные матрицы A" << endl;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < m; j++)
            {
                cin >> a.A[i][j];
            }
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < m; j++)
                cout << a.A[i][j] << " ";
            cout << endl;
        }
        cout << "Введите данные вектора B" << endl;
        for (int i = 0; i < m; i++)
        {
            cin >> b.B[i];
        }
        for (int i = 0; i < m; i++)
        {
            cout << b.B[i] << " ";
            cout << endl;
        }
        x.joga(m, a, b);
    }
    return 0;
}
