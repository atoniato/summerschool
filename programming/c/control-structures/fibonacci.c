#include <stdio.h>

int main(int argc, char *argv[])
{
    int f0, f1, f2;
    int i = 0;
    // initialize variables and write the while loop
    f0 = 0;
    f1 = 1;
    f2 = f0;
    // Remember to update all variables within the loop
    while(f2<100){

	    printf("f%d = %d\n",i,f2);
	    f0 = f1;
	    f1 = f2;
	    f2 = f0 + f1;
	    i++;

    }

    return 0;
}
