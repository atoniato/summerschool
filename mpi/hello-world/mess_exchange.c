#include <stdio.h>
#include <mpi.h>

#define LEN 3

int main(int argc, char **argv){

	int rank,size,i;
	int tag1 = 1, tag2 =2;
	int array[LEN];
	int recv_array[LEN];
	MPI_Status status;

	MPI_Init(&argc,&argv);


	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);	

	//initialise vector
	for(i=0;i<LEN;i++){
		array[i] = rank;
		recv_array[i] = rank;
	}

	if(rank == 0){
		MPI_Send(array,LEN,MPI_INT,size-1,tag1,MPI_COMM_WORLD);
		MPI_Recv(recv_array,LEN,MPI_INT,size-1,tag2,MPI_COMM_WORLD,&status);
	}
	if(rank == size-1){
		MPI_Recv(recv_array,LEN,MPI_INT,0,tag1,MPI_COMM_WORLD,&status);
		MPI_Send(array,LEN,MPI_INT,0,tag2,MPI_COMM_WORLD);
	}


	printf("Process %d, array (first element) %d \n", rank, recv_array[0]);

	MPI_Finalize();
	return 0;
}
