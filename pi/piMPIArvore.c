#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <mpi.h>
#include <stdbool.h>

//mpicc -g -Wall -o piMPI piMPI.c -std=gnu99 -lm &&  mpiexec -n 8 ./piMPI

int main(void) {
		int my_rank, comm_sz, n = 100000000, local_hit, local_n, local_divisor, local_dif, local_length;
		unsigned int my_seed;
		bool local_sent;  

		/* Let the system do what it needs to start up MPI */
		MPI_Init(NULL, NULL);

		/* Get my process rank */
		MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

		/* Find out how many processes are being used */
		MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

		local_n = n/comm_sz;
git 
		double x,y;
		local_hit = 0;
		local_sent = false;
		local_divisor = 2;
		local_dif = 1;
		local_length = 0;
		my_seed = my_rank + (unsigned)time(NULL);
		for (int i = 0; i < local_n; i++){
			x = (double)rand_r(&my_seed)/(double)(unsigned)RAND_MAX;
			y = (double)rand_r(&my_seed)/(double)(unsigned)RAND_MAX;
			//printf("x: %f, y: %f\n", x, y);

			if (sqrt(pow(x-0.5,2)+pow(y-0.5,2)) < 0.5)
			local_hit++;
		}
		while(!local_sent && local_length < log(comm_sz)/log(2)){
			if(my_rank % local_divisor == local_dif){
				MPI_Send(&local_hit, 1, MPI_INT, my_rank-local_dif, 0, 
            MPI_COMM_WORLD);
				local_sent = true;
			}
			else {
				MPI_Recv(&local_hit, 1, MPI_INT, my_rank+local_dif, 0,
            MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				local_hit += local_hit;
			}
			local_divisor *= 2;
			local_dif *= 2;
			local_length++;
		}
		//printf("Local sum %d \n", local_hit);
			
   /* Print the result */
   if (my_rank == 0) {
      printf("pi: %f \n", (float)4*local_hit/n);
   }

   /* Shut down MPI */
   MPI_Finalize();

   return 0;
} /*  main  */






