#include "solver.h"

static bool flag = 0; //std::cout   0 - minimal info about solution, 1 - maximal info
static bool flag2 = 1; //show time 0 - off, 1 - on

int main()
{
    while (1)
    {
        int type = 0, size = 3000, mod = 0;
        time_t start = 0, end = 0;

        std::cout << "---------------------------------------------------------Ax=b---------------------------------------------------------\n";
        std::cout << "0 - double, 1 - float, 2 - exit\n";
        std::cin >> type;

        switch (type)
        {
        case 0:
        {
            std::cout << "size\n";
            std::cin >> size;
            std::cout << "0 - manual fill, 1 - random auto-fill\n";
            std::cin >> mod;

            vector<double> vec(size);
            matrix<double> mat(size);

            if (mod == 0) std::cout << "A\n";
            mat.fill(mod);

            if (mod == 0) std::cout << "b\n";
            vec.fill(mod);

            if (flag) std::cout << std::setprecision(8) << mat << vec;

            solver<double> s(mat, vec, size);

            auto begin = std::chrono::steady_clock::now();

            int b = s.solution();

            auto end = std::chrono::steady_clock::now();
            auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            if (flag2) std::cout << "The time: " << elapsed_ms.count() << " ms\n";

            if (b == 2)
            {
                std::cout << "det = 0 & no solutions\n";
                break;
            }
            else if (b == 0)
            {
                std::cout << "the only one solution\n";
                if (flag)
                {
                    std::cout << std::setprecision(8) << s.get_v();
                    std::cout << "checking: Ax, b, Ax-b\n";
                    s.check(mat, vec);
                }
            }
            else
            {
                std::cout << "det = 0 & infinity solutions\n";
                if (flag)
                {
                    std::cout << std::setprecision(8) << "one of these\n";
                    std::cout << s.get_v();
                    std::cout << "checking: Ax, b, Ax-b\n";
                    s.check(mat, vec);
                }
            }
            break;
        }
        case 1:
        {
            std::cout << "size\n";
            std::cin >> size;
            std::cout << "0 - manual fill, 1 - random auto-fill\n";
            std::cin >> mod;

            vector<float> vec(size);
            matrix<float> mat(size);

            if (mod == 0) std::cout << "A\n";
            mat.fill(mod);

            if (mod == 0) std::cout << "b\n";
            vec.fill(mod);

            if (flag) std::cout << std::setprecision(8) << mat << vec;

            solver<float> s(mat, vec, size);

            auto begin = std::chrono::steady_clock::now();

            int b = s.solution();

            auto end = std::chrono::steady_clock::now();
            auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            if (flag2) std::cout << "The time: " << elapsed_ms.count() << " ms\n";

            if (b == 2)
            {
                std::cout << "det = 0 & no solutions\n";
                break;
            }
            else if (b == 0)
            {
                std::cout << "the only one solution\n";
                if (flag)
                {
                    std::cout << std::setprecision(8) << s.get_v();
                    std::cout << "checking: Ax, b, Ax-b\n";
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
                    std::cout << "checking: Ax, b, Ax-b\n";
                    s.check(mat, vec);
                }
            }
            break;
        }
        case 2:
            exit(0);
        }

    }

    return 0;
}