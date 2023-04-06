#include "funcs.h"

int main() {
	float out1;
	float out2;
	double out3;
	float arg;
	for (int i = -20; i < 201; i++) {
		//arg = PI * i / 180.0f;
		arg = (float)i;
		out1 = mysum(arg, 100, 0, mysin1);
		printf("1)sin(%.8f) = %.32f\n", arg, out1);
		out2 = mysum(arg, 100, 1, mysin1);
		printf("2)sin(%.8f) = %.32f\n", arg, out2);
		out3 = sin((double)arg);
		printf("3)sin(%.8f) = %.32lf (double)\n", arg, out3);
		out1 = mysum(arg, 100, 0, mycos1);
		printf("1)cos(%.8f) = %.32f\n", arg, out1);
		out2 = mysum(arg, 100, 1, mycos1);
		printf("2)cos(%.8f) = %.32f\n", arg, out2);
		out3 = cos((double)arg);
		printf("3)cos(%.8f) = %.32lf (double)\n", arg, out3);
		out1 = mysum(arg, 1000, 0, myexp1);
		printf("1)exp(%.8f) = %.32f\n", arg, out1);
		out2 = mysum(arg, 1000, 1, myexp1);
		printf("2)exp(%.8f) = %.32f\n", arg, out2);
		out3 = exp((double)arg);
		printf("3)exp(%.8f) = %.32lf (double)\n", arg, out3);
		out1 = mysum(arg, 1000, 0, myln1);
		printf("1)ln(%.8f) = %.32f\n", 1.0f + arg, out1);
		out2 = mysum(arg, 1000, 1, myln1);
		printf("2)ln(%.8f) = %.32f\n", 1.0f + arg, out2);
		out1 = myln2(1.0f + arg, 1000, 0);
		printf("3)ln(%.8f) = %.32f\n", 1.0f + arg, out1);
		out2 = myln2(1.0f + arg, 1000, 1);
		printf("4)ln(%.8f) = %.32f\n", 1.0f + arg, out2);
		out3 = log((double)(1.0f+arg));
		printf("5)ln(%.8f) = %.32lf (double)\n", 1.0f + arg, out3);
	}
	return 0;
}

// sin, cos:
// 8 correct digits near 0
// 5-6 correct digits at pi distance from 0