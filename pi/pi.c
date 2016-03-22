#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(){
	unsigned long int samples = 100000000, hit = 0, iterator;
	double x,y;
	srand((unsigned)time(NULL));
	
	for (iterator = 0; iterator < samples; iterator++){
		x = (double)rand()/(double)(unsigned)RAND_MAX;
		y = (double)rand()/(double)(unsigned)RAND_MAX;

	//printf("eudist: %f\n", euDist, x, );
	if (sqrt(pow(x-0.5,2)+pow(y-0.5,2)) < 0.5)
		hit++;
	}	
	
	printf("pi: %f \n", (float)4*hit/samples);
	return 0;
}
