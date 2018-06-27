#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = -3;

    // write the control structure as described in the exercise
	if (i<0){ printf("Negative\n");}
	if (i>100){ printf("Larger than 100\n");}
	if (!i){ printf("0\n");}
	
    // and run the code with different values for i

    return 0;
}
