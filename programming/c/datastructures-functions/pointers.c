#include <stdio.h>

void function(int *a, int *b){

	*a += 1;
	*b += 1;
}


int main(){

	int a = 4;
	int b = 5;

	function(&a,&b);

	printf("Final values: %d, %d\n",a,b);

	return 0;
}
