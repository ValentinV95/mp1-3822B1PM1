#include <cmath>
float sins(int i, float x, float last) {
    if (i == 0) {
        return x;
    }
    else {
        return -last * x * x / ((2 * i) * (2 * i + 1));
    }
}
float coss(int i, float x, float last) {
    if (i == 0) {
        return 1;
    }
    else {
        return -last * x * x / ((2 * i) * (2 * i - 1));
    }
}
float lns(int i, float x, float last) {
    if (i == 0) {
        return x;
    }
    else {
        return -last * x * i / (i + 1);
    }
}
float exps(int i, float x, float last) {
    if (i == 0) {
        return 1;
    }
    else {
        return last * x / i;
    }
}

float sinb(int i, float x, float prev) {
    return  -prev * ((2 * i) * (2 * i + 1)) / (x * x);
}
float cosb(int i, float x, float prev) {
    return  -prev * (2 * i) * (2 * i - 1) / (x * x);
}
float lnb(int i, float x, float prev) {
    if (i == 0) {
        return 0;
    }
    return  -prev * (i + 1) / (x * i);
}
float expb(int i, float x, float prev) {
    return  prev * i / x;
}


float strway(int n, float x, float (*fun)(int, float, float)) {
    float sum = 0, cur = 0;
    for (int i = 0; i < n; i++) {
        cur = (*fun)(i, x, cur);
        sum += cur;
    }
    return sum;
}

float backway(int n, float x, float (*funs)(int, float, float), float (*funb)(int, float, float)) {
    float sum = 0, cur = 0, l=0;
    int i_l;
    for (int i = 0; i < n; i++) {
        cur = (*funs)(i, x, cur);
        if ((abs(cur)- pow(10, -38))<0) {
            cur = l;
            i_l = i;
            break;
        }
        l = cur;
        i_l = i+1;
    }
    sum += cur;
    for (int i = i_l-1; i > -1; i--) {
        cur = (*funb)(i, x, cur);
        sum += cur;
    }
    return sum;
}