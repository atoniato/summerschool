#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <mpi.h>

//RUN ON AT LEAST THREE PROCESSES!

int main(int argc, char *argv[])
{
    int my_id, omp_rank;
    int provided, required = MPI_THREAD_MULTIPLE;

    /* TODO: Initialize MPI with thread support. */
    MPI_Init_thread(&argc,&argv,required,&provided);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_id);
    int *sendbuf;

#pragma omp parallel private(omp_rank)
{
	int *recvbuf;
        int var=-1;
	recvbuf = &var;
	omp_rank = omp_get_thread_num();
	sendbuf= &omp_rank;

	if(my_id == 0){
		MPI_Send(sendbuf,1,MPI_INT,1,omp_rank,MPI_COMM_WORLD);
		MPI_Send(sendbuf,1,MPI_INT,2,omp_rank,MPI_COMM_WORLD);
	}
	if(my_id == 1){
		MPI_Recv(recvbuf,1,MPI_INT,0,omp_rank,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	}
	if(my_id == 2){
		MPI_Recv(recvbuf,1,MPI_INT,0,omp_rank,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	}
	printf("Rank %d, receive = %d\n",my_id,*recvbuf);

}

    MPI_Finalize();
    return 0;
}
