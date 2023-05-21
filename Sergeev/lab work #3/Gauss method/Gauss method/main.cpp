#include <iostream>
#include <chrono>
#include <iomanip>
#include "menu.h"
#include "solver.h"
#include "vector.h"
#include "matrix.h"

const bool flag = 1; //menu.cpp std::cout   0 - minimal info about solution, 1 - maximal info
const bool flag2 = 0; //show time 0 - off, 1 - on

int main()
{
    while (1)
    {
        int type = 0;
        std::cout << "---------------------------------------------------------Ax=b---------------------------------------------------------\n";
        std::cout << "0 - double, 1 - float, 2 - exit\n";
        std::cin >> type;

        switch (type)
        {
        case 0:
        {
            menu<double>(flag, flag2);
            break;
        }
        case 1:
        {
            menu<float>(flag, flag2);
            break;
        }
        case 2:
            exit(0);
        }

    }

    return 0;
}