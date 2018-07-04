#include <stdio.h>
#include <omp.h>

#define NX 102400

int main(void)
{
    double vecA[NX], vecB[NX], vecC[NX];
    double sum;
    double sum_check=0;
    int i;

    /* Initialization of the vectors */
    for (i = 0; i < NX; i++) {
        vecA[i] = 1.0 / ((double)(NX - i));
        vecB[i] = vecA[i] * vecA[i];
	sum_check += vecA[i] + vecB[i];
    }

    printf("Non parallelized sum = %18.16g\n",sum_check);

    /* TODO:
     *   Implement here a parallelized version of vector addition,
     *   vecC = vecA + vecB
     */
    #pragma omp parallel for schedule(runtime) 
	for(i=0;i<NX;i++){
		vecC[i] = vecA[i] + vecB[i];
	}

    sum = 0.0;
    /* Compute the check value */
    for (i = 0; i < NX; i++) {
        sum += vecC[i];
    }
    printf("Reduction sum: %18.16f\n", sum);

    return 0;
}
