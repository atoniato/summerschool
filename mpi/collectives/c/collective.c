#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define NTASKS 4

void print_buffers(int *printbuffer, int *sendbuffer, int buffersize);
void init_buffers(int *sendbuffer, int *recvbuffer, int buffersize);


int main(int argc, char *argv[])
{
    int ntasks, rank, color,i;
    int sendbuf[2 * NTASKS], recvbuf[2 * NTASKS];
    int printbuf[2 * NTASKS * NTASKS];

    MPI_Comm sub_comm;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (ntasks != NTASKS) {
        if (rank == 0) {
            fprintf(stderr, "Run this program with %i tasks.\n", NTASKS);
        }
        MPI_Abort(MPI_COMM_WORLD, -1);
    }

    /* Initialize message buffers */
    init_buffers(sendbuf, recvbuf, 2 * NTASKS);

    /* Print data that will be sent */
    print_buffers(printbuf, sendbuf, 2 * NTASKS);

    /* TODO: use a single collective communication call (and maybe prepare
     *       some parameters for the call) */

	MPI_Request request;
	MPI_Status status;
//(5a)    MPI_Bcast(sendbuf,2*NTASKS,MPI_INT,0,MPI_COMM_WORLD);
//(5a,non-bl)	MPI_Ibcast(sendbuf,2*NTASKS,MPI_INT,0,MPI_COMM_WORLD,&request);
//(5b)    MPI_Scatter(sendbuf,2,MPI_INT,recvbuf,2,MPI_INT,0,MPI_COMM_WORLD);
//(5b,non-bl)	MPI_Iscatter(sendbuf,2,MPI_INT,recvbuf,2,MPI_INT,0,MPI_COMM_WORLD,&request);
//(5c)    int sendcount[NTASKS] = {1,1,2,4};
//(5c)    int displs[NTASKS] = {0,1,2,4};
//(5c)    MPI_Gatherv(sendbuf,sendcount[rank],MPI_INT,recvbuf,sendcount,displs,MPI_INT,1,MPI_COMM_WORLD);
//(5c,non-bl)	int sendcount[NTASKS] = {1,1,2,4};
//(5c,non-bl)	int displs[NTASKS] = {0,1,2,4};
//(5c,non-bl)	MPI_Igatherv(sendbuf,sendcount[rank],MPI_INT,recvbuf,sendcount,displs,MPI_INT,1,MPI_COMM_WORLD,&request);

//(6)    for(i=0;i<NTASKS;i++){
//(6)	if (rank < 2){color = 1;}
//(6)	else{color = 2;}
//(6)    }
//(6)    MPI_Comm my_comm;
//(6)    MPI_Comm_split(MPI_COMM_WORLD,color,rank,&my_comm);
//(6)    MPI_Reduce(sendbuf,recvbuf,2*NTASKS,MPI_INT,MPI_SUM,0,my_comm);

    for(i=0;i<NTASKS;i++){
	if (rank < 2){color = 1;}
	else{color = 2;}
    }
    MPI_Comm my_comm;
    MPI_Comm_split(MPI_COMM_WORLD,color,rank,&my_comm);
    MPI_Ireduce(sendbuf,recvbuf,2*NTASKS,MPI_INT,MPI_SUM,0,my_comm,&request);

    /* Print data that was received */
    /* TODO: add correct buffer */
	MPI_Wait(&request,&status);
//(5a)    print_buffers(printbuf,sendbuf, 2 * NTASKS);
    print_buffers(printbuf,recvbuf, 2 * NTASKS);

    MPI_Finalize();
    return 0;
}


void init_buffers(int *sendbuffer, int *recvbuffer, int buffersize)
{
    int rank, i;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    for (i = 0; i < buffersize; i++) {
        recvbuffer[i] = -1;
        sendbuffer[i] = i + buffersize * rank;
    }
}


void print_buffers(int *printbuffer, int *sendbuffer, int buffersize)
{
    int i, j, rank, ntasks;

    MPI_Gather(sendbuffer, buffersize, MPI_INT,
               printbuffer, buffersize, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);

    if (rank == 0) {
        for (j = 0; j < ntasks; j++) {
            printf("Task %i:", j);
            for (i = 0; i < buffersize; i++) {
                printf(" %2i", printbuffer[i + buffersize * j]);
            }
            printf("\n");
        }
        printf("\n");
    }
}
