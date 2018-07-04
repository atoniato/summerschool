#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
	int numth;
	printf("Hello world!\n");
#pragma omp parallel
	{
		numth = omp_get_num_threads();
		int thnum;
		thnum = omp_get_thread_num();
		printf("Thread number: %d \n ",thnum);
		printf("X\n");
		
	}

	printf("Total number of threads: %d \n",numth);
	return 0;
}
