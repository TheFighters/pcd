#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <mpi.h>
#include <stdbool.h>

//mpicc -g -Wall -o piMPIArvore piMPIArvore.c -std=gnu99 -lm &&  mpiexec -n 8 ./piMPIArvore

int main(void) {
	long long int n = 100000000, local_hit, local_n, total_hit;
	int comm_sz, my_rank;
	unsigned int my_seed;
	double x, y;

	/* Let the system do what it needs to start up MPI */
	MPI_Init(NULL, NULL);
	double oldTime = MPI_Wtime();

	/* Get my process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	/* Find out how many processes are being used */
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

	local_n = n / comm_sz;
	local_hit = 0;
	total_hit = 0;
	my_seed = my_rank * (unsigned)time(NULL);
	for (int i = 0; i < local_n; i++) {
		x = (double)rand_r(&my_seed) / (double)(unsigned)RAND_MAX;
		y = (double)rand_r(&my_seed) / (double)(unsigned)RAND_MAX;
		//printf("x: %f, y: %f\n", x, y);

		if (sqrt(pow(x - 0.5, 2) + pow(y - 0.5, 2)) < 0.5)
			local_hit++;
	}
	//printf("Local sum %d \n", local_hit);
	// 																cont (vetor)                    destino
	MPI_Reduce(&local_hit, &total_hit, 1, MPI_LONG_LONG_INT, MPI_SUM, 0,
	           MPI_COMM_WORLD);
	/* Print the result */
	if (my_rank == 0) {
		printf("pi: %f \n", (float)4 * total_hit / n);
		printf("Time: %f\n", MPI_Wtime() - oldTime);
	}

	/* Shut down MPI */
	MPI_Finalize();

	return 0;
} /*  main  */
