#include <iostream>
#include "matrix.h"
#include "vec.h"
#include "func.h"
using namespace std;


int main()
{
    setlocale(LC_ALL,"RUS");
    size_t n;
    cout << "Введите размерность вектора:";
   cin >> n;
   
   int c;
   cout << "1. float\n2. double\nВведите желаемый тип данных:";
   cin >> c;
   
   switch (c)
   {
   case 1:
   {
       vec<float> X(n);
       solver<float>(n);
       break;
   }
   case 2:
   {
       vec<double> X(n);
       solver<double>(n);
       break;
   }
   }
   
}

