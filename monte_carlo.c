#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long int Toss(long long int slicedTosses, int id);

// Random toss function
long long int Toss(long long int slicedTosses, int id)
{
	long long int numberInCircle = 0, toss;
	double x, y;
	unsigned int seed = (unsigned)time(NULL);
	srand(seed + id);
	for(toss = 0; toss < slicedTosses; toss++)
	{
		x = rand_r(&seed)/(double)RAND_MAX;
		y = rand_r(&seed)/(double)RAND_MAX;
		if ((x*x + y*y) <= 1.0) numberInCircle++;
	}
	return numberInCircle;
}

int main(int argc,char *argv[])
{
	// variables
	long long int numTosses, numHits, totalHits;
	long long int slice;
	int id, p, i, m;
	float n;
	double PI25DT = 3.141592653589793238462643; // 25 digit PI
	double pi;
	double startwtime = 0.0, endwtime;
	int src, dest;

	// Initializing MPI
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&p);
	MPI_Comm_rank(MPI_COMM_WORLD,&id);
	MPI_Status status;

	// process 0 reading the num of tosses
	if(id == 0) 
	{
		numTosses = 100000000;
		startwtime = MPI_Wtime();
	}
	
	// tree structured broadcast (broadcasting numTosses to all processors)
	m = 1;
	n = p;
	for(i = 0; i < ((n/2) + 0.5); i++)
	{
		if(id < m) // broadcasters
		{
			dest = id + m;
			if(dest < p) // makes sure the destination is valid
				MPI_Send(&numTosses, 1, MPI_LONG_LONG, dest, 0, MPI_COMM_WORLD);	
		} else if(id >= m && id < m * 2) //recievers
		{
			src = id - m;
			MPI_Recv(&numTosses, 1, MPI_LONG_LONG, src, 0, MPI_COMM_WORLD, &status);
		}
		m = m * 2;
	}

	// function to toss the darts
	slice = numTosses/p;
	totalHits = Toss(slice, id); // total hits for each processor

	// tree structured global sum
	n = p;

	for(i = 0; i < ((n/2) + 0.5); i++)
	{
		n = ceil(n/2);
		m = (int)n;
	
		if(id < m)
		{
			src = id + m;
			if(src < p)
			{
				MPI_Recv(&numHits, 1, MPI_LONG_LONG, src, 0, MPI_COMM_WORLD, &status);
				totalHits += numHits;
			}
		} else if (id >= m && id < 2*m)
		{
			dest = id - m;
			MPI_Send(&totalHits, 1, MPI_LONG_LONG, dest, 0, MPI_COMM_WORLD);
		}
		MPI_Barrier(MPI_COMM_WORLD);
	}

	// the solution processed by processor 0
	if (id == 0) 
	{
		pi = (4*totalHits)/((double)numTosses);
		endwtime = MPI_Wtime();
		printf("pi is approximately %.16f, Error is %.16f\n", pi, fabs(pi - PI25DT));
		printf("wall clock time = %f\n", endwtime-startwtime);	       
		fflush(stdout);
	}

	MPI_Finalize();
	return 0;
}
