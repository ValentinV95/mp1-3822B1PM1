#include "solver.h"

template<class T>
void menu(bool flag, bool flag2) 
{
    int size = 3; int mod = 0;

    std::cout << "size\n";
    std::cin >> size;
    std::cout << "0 - manual fill, 1 - random auto-fill\n";
    std::cin >> mod;

    vector<T> vec(size);
    matrix<T> mat(size);

    if (mod == 0) std::cout << "A\n";
    mat.fill(mod);

    if (mod == 0) std::cout << "b\n";
    vec.fill(mod);

    if (flag) std::cout << std::setprecision(8) << mat << vec;

    solver<T> s(mat, vec, size);

    auto begin = std::chrono::steady_clock::now();

    int b = s.solution();

    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    if (flag2) std::cout << "The time: " << elapsed_ms.count() << " ms\n";

    if (b == 2)
    {
        std::cout << "det = 0 & no solutions\n";
    }
    else if (b == 0)
    {
        std::cout << "the only one solution\n";
        if (flag)
        {
            std::cout << std::setprecision(8) << s.get_v();

            std::cout << "checking precision: Ax-b\n";
            s.check(mat, vec);
        }
    }
    else
    {
        std::cout << "det = 0 & infinity solutions\n";
        if (flag)
        {
            std::cout << "one of these\n";
            std::cout << std::setprecision(8) << s.get_v();

            std::cout << "checking precision: Ax-b\n";
            s.check(mat, vec);
        }
    }
}