#include "Solver.h"

int main()
{
    int choose=1, size=1, choose2=0;
    setlocale(LC_ALL, "Russian");
    do {
        system("cls");
        do {
            if ((choose != 1) && (choose != 2)) {
                system("cls");
                std::cout << "Выбранного вами типа данных не существует, попробуйте ещё раз" << std::endl;
            }
            std::cout << "Выберите тип данных для вашей матрицы:" << std::endl << "1.float" << std::endl << "2.double" << std::endl;
            std::cin >> choose;
        } while ((choose != 1) && (choose != 2));
        do {
            if (size <= 0) {
                system("cls");
                std::cout << "Матрица выбранного вами размера не может быть создана, попробуйте снова:" << std::endl;
            }
            std::cout << "Введите размер матрицы:" << std::endl;
            std::cin >> size;
        } while (size <= 0);
        switch (choose) {
        case (1): {
            Linear_system<float>(size);
            break;
        }
        case (2): {
            Linear_system<double>(size);
            break;
        }
        }
        do {
            if ((choose2 != 1) && (choose2 != 0)) {
                system("cls");
                std::cout << "Выбранного вами варианта не существует, попробуйте ещё раз" << std::endl;
            }
            std::cout << "Что вы собираетесь делать?" << std::endl << "1.Решить ещё одну систему" << std::endl << "0. Закончить работу программы" << std::endl;
            std::cin >> choose2;
        } while ((choose2 != 1) && (choose2 != 0));
    } while (choose2 != 0);
}