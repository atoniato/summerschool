#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int i, myid, ntasks;
    int snd, dest;
    int size = 10000000;
    int *message;
    int *receiveBuffer;

    double t0, t1;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    /* Allocate message buffers */
    message = malloc(sizeof(int) * size);
    receiveBuffer = malloc(sizeof(int) * size);
    /* Initialize message */
    for (i = 0; i < size; i++) {
        message[i] = myid;
    }

    /* Start measuring the time spent in communication */
    MPI_Barrier(MPI_COMM_WORLD);
    t0 = MPI_Wtime();
	
    /* TODO start */
    /* With sendrecv */
    dest = myid + 1;
    snd = myid - 1;
    if (myid==0) {snd=MPI_PROC_NULL;}
    if (myid==ntasks-1){dest=MPI_PROC_NULL;}

//    MPI_Sendrecv(message,size,MPI_INT,dest,myid+1,receiveBuffer,size,MPI_INT,snd,myid,MPI_COMM_WORLD,&status);

//    MPI_Request request1,request2;
//    MPI_Status status1,status2;
//    /* Send and receive messages as defined in exercise */
//    if (myid < ntasks - 1) {
//	    MPI_Isend(message,size,MPI_INT,myid+1,myid+1,MPI_COMM_WORLD,&request1);
//	   // MPI_Wait(&request1,&status1);
//	    printf("Sender: %d. Sent elements: %d. Tag: %d. Receiver: %d\n",
//			    myid, size, myid + 1, myid + 1);
//    }
//
//    if (myid > 0) {
//	    MPI_Irecv(receiveBuffer,size,MPI_INT,myid-1,myid,MPI_COMM_WORLD,&request2);
//	    MPI_Wait(&request2,&status2);
//	    printf("Receiver: %d. first element %d.\n",
//			    myid, receiveBuffer[0]);
//    }

   /* with persistent communication */
    MPI_Request recv_obj, send_obj;
    /* Send and receive messages as defined in exercise */
   
   
    if (myid < ntasks - 1) {
	    MPI_Send_init(message,size,MPI_INT,myid+1,myid+1,MPI_COMM_WORLD,&send_obj);
	    MPI_Start(&send_obj);
    }

    if (myid > 0) {
	    MPI_Recv_init(receiveBuffer,size,MPI_INT,myid-1,myid,MPI_COMM_WORLD,&recv_obj);
	    MPI_Start(&recv_obj);
    }


    if (myid < ntasks - 1) {
	    MPI_Wait(&send_obj,MPI_STATUS_IGNORE);
	    MPI_Request_free(&send_obj);
	    printf("Sender: %d. Sent elements: %d. Tag: %d. Receiver: %d\n",
			    myid, size, myid + 1, myid + 1);
    }

    if (myid > 0) {
	    MPI_Wait(&recv_obj,MPI_STATUS_IGNORE);
	    MPI_Request_free(&recv_obj);
	    printf("Receiver: %d. first element %d.\n",
			    myid, receiveBuffer[0]);
    }
    /* TODO end */


    /* Finalize measuring the time and print it out */
    t1 = MPI_Wtime();
    MPI_Barrier(MPI_COMM_WORLD);
    fflush(stdout);

    printf("Time elapsed in rank %2d: %6.3f\n", myid, t1 - t0);

    free(message);
    free(receiveBuffer);
    MPI_Finalize();
    return 0;
}
