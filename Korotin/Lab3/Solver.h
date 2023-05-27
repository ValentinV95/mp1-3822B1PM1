#pragma once
#include "Matrix.h"
template <class T>
class Solver {
    Vec<T> solve;
public:
    Vec<T> Gauss(Matrix<T>& A, Vec<T>& b) {
        if (A.GetSize() == b.GetSize()) {
            int max, j = 0;
            double eps = pow(10, -8);
            T d;
            size_t size = b.GetSize();
            Vec<T>* string = new Vec<T>[size];
            for (int i = 0; i < size; ++i) {
                (string[i]).setVec(size, &(A[size * i]));
            }
            for (int i = 0; i < size; ++j, ++i) {
                max = i;
                while (j < size) {
                    for (int k = i; k < size; ++k) if (abs(string[max][j]) < abs(string[k][j])) max = k;
                    if (abs(string[max][j]) < eps) j++;
                    else break;
                }
                if (j < size) {
                    string[max].swap(string[i]);
                    std::swap(b[max], b[i]);
                    for (int k = 0; k < i; ++k) {
                        d = string[k][j] / string[i][j];
                        string[k] -= string[i] * d;
                        b[k] -= b[i] * d;
                    };
                    for (int k = i + 1; k < size; ++k) {
                        d = string[k][j] / string[i][j];
                        string[k] -= string[i] * d;
                        b[k] -= b[i] * d;
                    };
                }
                else break;
            };
            for (int i = 0; i < size; ++i) {
                j = i;
                while ((abs(string[i][j]) < eps) && (j < size)) j++;
                if (j < size) {
                    b[i] /= string[i][j];
                    string[i] *= (1 / string[i][j]);
                }
                else {
                    for (int k = i; k < size; ++k)
                        if (b[k] != 0) {
                            std::cout << "Система несовместна" << std::endl;
                            for (int k = 0; k < size; ++k) b[k] = NAN;
                            break;
                        }
                    break;
                }
            };
            for (int i = 0; i < size; ++i) string[i].GetMas() = nullptr;
            delete[] string;
            return b;
        }
    }
};

template <typename T>
void Linear_system(int size) {
    int choose=1;
    Matrix<T> A(size);
    Vec<T> b(size);
    Solver<T> solve;
    Vec<T> X;
    setlocale(LC_ALL, "Russian");
    system("cls");
    do {
        if ((choose != 1) && (choose != 2)) {
            system("cls");
            std::cout << "Выбранного вами варианта не существует, попробуйте ещё раз" << std::endl;
        }
        std::cout << "Выберите, как вы хотите ввести элементы матрицы и вектора:" << std::endl << "1.Самостоятельно" << std::endl << "2.Ввести случайные элементы" << std::endl;
        std::cin >> choose;
    } while ((choose != 1) && (choose != 2));
    if (choose == 1) {
        std::cout << "Введите элементы матрицы (по строкам):" << std::endl;
        std::cin >> A;
        std::cout << A << std::endl;
        std::cout << "Введите элементы вектора:" << std::endl;
        std::cin >> b;
    }
    else {
        for (int i = 0; i < size * size; ++i) A[i] = ((T)rand())/100;
        for (int i = 0; i < size; ++i) b[i] = ((T)rand()) / 100;
    }
    system("cls");
    std::cout << "Введённая матрица:" << std::endl << A << "Введённый вектор:" << std::endl << b << std::endl;
    X = solve.Gauss(A, b);
    std::cout<< "Результат:" << std::endl << X << std::endl;
}