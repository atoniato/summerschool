#include <stdio.h>

int main(int argc, char *argv[])
{
    // declare integers, floats, and doubles

	int a,b;
	float fa, fb;
	double da, db;
	
	a = 2;
	fa = 0.1;
	da = 0.1;

    // evaluate expressions, e.g. c = a + 2.5 * b

	b = a - 1;
	fb = (float)a*da;
	db = (double) (a+4)/3;

    // and print out results. Try to combine integers, floats

	printf("Integer variables = %d, %d \n",a,b);
	printf("Floating point variables = %.4f, %.6f \n",fa,fb);
	printf("Double variables = %.4f, %.6f \n",da,db);

    // and doubles and investigate what happens in type conversions

	switch(a){
		case 1:
		printf("one\n");		

		case 2:
		printf("two\n");

		default:
		printf("Many\n");

	}

    return 0;
}
