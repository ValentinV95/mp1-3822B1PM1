#include "func.h"

float mysin(float inp, float x, int i, int mod) {
    return inp * pow(-x * x / (2 * i * (2 * i + 1)), mod);
};
float mycos(float inp, float x, int i, int mod) {
    return inp * pow(-x * x / (2 * i * (2 * i - 1)), mod);
};
float myexp(float inp, float x, int i, int mod) {
    return inp * pow(x / i, mod);
};
float ln(float inp, float x, int i, int mod) {
    return inp * pow(-x / (i + 1) * i, mod);
};
struct res sum(float first, float x, int numb, float (*fun)(float, float, int, int)) {
    struct res res;
    float tmp, eps = pow(10, -8);
    res.str = tmp = first;
    for (int i = 1; i < numb; i++) {
        if (fabsf(fun(tmp, x, i, 1)) >= eps) tmp = fun(tmp, x, i, 1);
        else {
            numb = i;
            break;
        }
        res.str += tmp;
    }
    res.rev = tmp;
    for (int i = numb - 1; i > 0; i--) {
        tmp = fun(tmp, x, i, -1);
        res.rev += tmp;
    }
    return res;
};