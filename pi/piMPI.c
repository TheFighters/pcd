#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <mpi.h>

//mpicc -g -Wall -o piMPI piMPI.c -std=gnu99 -lm &&  mpiexec -n 8 ./piMPI

int main(void) {
   int my_rank, comm_sz, n = 10000000, local_hit, total_hit,source,local_n;   

   /* Let the system do what it needs to start up MPI */
   MPI_Init(NULL, NULL);

   /* Get my process rank */
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

   /* Find out how many processes are being used */
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

   local_n = n/comm_sz;

		double x,y;
		local_hit=0;  
		srand((unsigned)time(NULL)+my_rank*1000);
		for (int i = 0; i < local_n; i++){
			x = (double)rand()/(double)(unsigned)RAND_MAX;
			y = (double)rand()/(double)(unsigned)RAND_MAX;

			if (sqrt(pow(x-0.5,2)+pow(y-0.5,2)) < 0.5)
			local_hit++;
		}
	printf("Local sum %d \n", local_hit);



   /* Add up the integrals calculated by each process */
   if (my_rank != 0) { 
      MPI_Send(&local_hit, 1, MPI_INT, 0, 0, 
            MPI_COMM_WORLD); 
   } else {
      total_hit = local_hit;
      for (source = 1; source < comm_sz; source++) {
         MPI_Recv(&local_hit, 1, MPI_INT, source, 0,
            MPI_COMM_WORLD, MPI_STATUS_IGNORE);
         total_hit += local_hit;
      }
   } 

			
   /* Print the result */
   if (my_rank == 0) {
      printf("pi: %f \n", (float)4*total_hit/n);
   }

   /* Shut down MPI */
   MPI_Finalize();

   return 0;
} /*  main  */






