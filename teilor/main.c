#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

const int N = 101;


float mysin(float x, int ind, float ap) { //ap = a past == a i-1
    float ai;
    ai = (-1) * x * x * ap / (2 * (float)ind * (2 * (float)ind + 1));
    return ai;
}

float mysinR(float x, int ind, float an) {
    float ai;
    ai = (-an) * (2 * (float)ind + 2) * (2 * (float)ind + 3) / pow(x, 2);
    return ai;
}

float mycos(float x, int ind, float ap) { //ap = a past == a i-1
    float ai;
    ai = (-1) * x * x * ap / (2 * (float)ind * (2 * (float)ind - 1));
    return ai;
}

float mycosR(float x, int ind, float an) {
    float ai;
    ai = (-1) * ((2 * (float)ind) + 1) * ((2 * (float)ind) + 2) * an / (x * x);
    return ai;
}

float myexp(float x, int ind, float ap) { //ap = a past == a i-1
    float ai;
    ai = x * ap / (float)ind;
    return ai;
}

float myexpR(float x, int ind, float an) {
    float ai;
    ai = (float)(ind + 1) * an / x;
    return ai;
}

float myln(float x, int ind, float ap) { //ap = a past == a i-1
    float ai;
    ai = (-1) * x * (float)ind * ap / (float)(ind + 1);
    return ai;
}

float mylnR(float x, int ind, float an) {
    float ai;
    ai = (-1) * (float)(ind + 1) * an / (float)(ind)*x;
    return ai;
}

float sumstr(float (*anything)(float, int, float), float x, float ap) {
    float s = ap;
    float ai;
    for (int i = 1; i < N; i++) {
        ai = anything(x, i, ap);
        ap = ai;
        s += ai;
    }
    return s;
}

float sumback(float (*revers)(float, int, float), float (*straight)(float, int, float), float x, float ap) {
    float ai;
    float an;
    int ind_a;
    for (int i = 1; i < N; i++) {
        ai = straight(x, i, ap);
        if (fabsf(ai) - pow(10, -38) < 0) {
            break;
        }
        else {
            an = ai;
            ind_a = i;
        }
        ap = ai;
    }

    float s = an;
    for (int i = ind_a - 1; i > 0; i--) {
        ai = revers(x, i, an);
        an = ai;
        s += ai;
    }
    return s;
}

int main() {
    float sin0, cos0, exp0, ln0, x, sinl, cosl, expl, lnl, sin1, sin2, cos1, cos2, exp1, exp2, ln1, ln2;
    int c; //choice
    printf("Which fun you want to use?\n1.sin(x)\n2.cos(x)\n3.exp(x)\n4.ln(x)\n");
    scanf_s("%d", &c);
    printf("Enter x: ");
    scanf_s("%f", &x);
    sin0 = x;
    cos0 = 1;
    exp0 = 1;
    ln0 = x;
    float err1;
    float err2;
    switch (c) {
    case 1:
        if (x == 0) {
            x = 2 * (float)M_PI;
        }
        sin1 = sumstr(mysin, x, sin0);
        sin2 = sumback(mysinR, mysin, x, sin0) + sin0;
        printf("sin1 = %f\n", sin1);
        printf("sin2 = %f\n", sin2);
        err1 = fabsf(sinf(x) - sin1) / fabsf(sinf(x));
        err2 = fabsf(sinf(x) - sin2) / fabsf(sinf(x));
        break;
    case 2:
        if (x == 0) {
            x = 2 * (float)M_PI;
        }
        cos1 = sumstr(mycos, x, cos0);
        cos2 = sumback(mycosR, mycos, x, cos0) + cos0;
        printf("%f\n", cos1);
        printf("%f\n", cos2);
        fabsf(cosf(x) - cos1) / fabsf(cosf(x));
        err2 = fabsf(cosf(x) - cos2) / fabsf(cosf(x));
        break;
    case 3:
        if (x == 0) {
            x = 0;
        }
        exp1 = sumstr(myexp, x, exp0);
        exp2 = sumback(myexpR, myexp, x, exp0) + exp0;
        printf("%f\n", exp1);
        printf("%f\n", exp2);
        err1 = fabsf(expf(x) - exp1) / fabsf(expf(x));
        err2 = fabsf(expf(x) - exp1) / fabsf(expf(x));
        break;
    case 4:
        if (x <= 0) {
            printf("ERROR!");
            break;
        }
        ln1 = sumstr(myln, x, ln0);
        ln2 = sumback(mylnR, myln, x, ln0) + ln0;
        printf("%f\n", ln1);
        printf("%f\n", ln2);
        err1 = fabsf(logf(x + 1) - ln1) / fabsf(logf(x + 1));
        err2 = fabsf(logf(x + 1) - ln2) / fabsf(logf(x + 1));
        break;
    }
}
