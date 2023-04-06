#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int N = 101;


double mysin(double x, int ind, double ap){ //ap = a past == a i-1
    double ai;
    ai = (-1)*x*x*ap/(2*(double)ind*(2*(double)ind+1));
    return ai;
}

double mysinR(double x, int ind, double an){
    double ai;
    ai = (-an) *(2*ind+2)*(2*(ind+3))/pow(x,2);
    return ai;
}

double mycos(double x, int ind, double ap){ //ap = a past == a i-1
    double ai;
    ai = (-1)*x*x*ap/(2*(double)ind*(2*(double)ind-1));
    return ai;
}

double mycosR(double x, int ind, double an){
    double ai;
    ai = (-1) * ((2*(double)ind) + 1)*((2*(double)ind)+2)* an / (x*x);
    return ai;
}

double myexp(double x, int ind, double ap){ //ap = a past == a i-1
    double ai;
    ai = x*ap/(double)ind;
    return ai;
}

double myexpR(double x, int ind, double an){
    double ai;
    ai = (double)(ind+1)*an/x;
    return ai;
}

double myln(double x, int ind, double ap){ //ap = a past == a i-1
    double ai;
    ai = (-1)* x*(double)ind*ap/(double)(ind+1);
    return ai;
}

double mylnR(double x, int ind, double an){
    double ai;
    ai = (-1) * (double)(ind+1)* an/ (double)(ind)*x;
    return ai;
}

double sumstr(double (*anything)(double, int, double), double x, double ap){
    double s = ap;
    double ai;
    for (int i = 1; i < N;i++){
       ai = anything(x, i, ap);
       ap = ai;
       s += ai;
    }
    return s;
}

double sumback(double (*revers)(double, int, double), double (*straight)(double, int, double), double x, double ap){
    double ai;
    double an;
    int ind_a;
    for (int i = 1; i < N;i++){
        ai = straight(x, i, ap);
        if (fabs(ai) - pow(10, -38) < 0){
            break;
        }
        else{
            an = ai;
            ind_a = i;
        }
        ap = ai;
    }

    double s = an;
    for (int i = ind_a-1; i > 0; i--){
        ai = revers(x, i, an);
        an = ai;
        s+=ai;
    }
    return s;
}

int main() {
    double sin0, cos0, exp0, ln0, x, sinl, cosl, expl, lnl;
    int c; //choice
    printf("Which fun you want to use?\n1.sin(x)\n2.cos(x)\n3.exp(x)\n4.ln(x)\n");
    scanf("%d", &c);
    printf("Enter x: ");
    scanf("%lf", &x);
    sin0 = x;
    cos0 = 1;
    exp0 = 1;
    ln0 = x;
    double err1;
    double err2;
    switch (c) {
        case 1:
            if(x == 0){
                x = 2*M_PI;
            }
            double sin1 = sumstr(mysin, x, sin0);
            double sin2 = sumback(mysinR,mysin, x,  sin0) + sin0;
            printf("sin1 = %lf\n", sin1 );
            printf("sin2 = %lf\n", sin2);
            err1 = fabs(sin(x) - sin1)/ fabs(sin(x));
            err2 = fabs(sin(x) - sin2)/ fabs(sin(x));
            break;
        case 2:
            if(x == 0){
                x = 2*M_PI;
            }
            double cos1 = sumstr(mycos, x, cos0);
            double cos2 = sumback(mycosR,mycos, x,  cos0)+cos0;
            printf("%lf\n", cos1);
            printf("%lf\n", cos2);
            err1 = fabs(cos(x) - cos1)/ fabs(cos(x));
            err2 = fabs(cos(x) - cos2)/ fabs(cos(x));
            break;
        case 3:
            if(x==0){
                x = 0;
            }
            double exp1 = sumstr(myexp, x, exp0);
            double exp2 = sumback (myexpR,myexp, x,  exp0)+exp0;
            printf("%lf\n", exp1);
            printf("%lf\n", exp2);
            err1 = fabs(exp(x) - exp1)/ fabs(exp(x));
            err2 = fabs(exp(x) - exp1)/ fabs(exp(x));
            break;
        case 4:
            if (x <=0){
                printf("ERROR!");
                break;
            }
            double ln1 = sumstr(myln, x, ln0);
            double ln2 = sumback(mylnR,myln, x,  ln0)+ln0;
            printf("%lf\n", ln1);
            printf("%lf\n", ln2);
            err1 = fabs(log(x+1) - ln1)/ fabs(log(x+1));
            err2 = fabs(log(x+1) - exp1)/ fabs(log(x+1));
            break;
    }

}
