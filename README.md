# Monte-Carlo-mpi
Program written in C with the use of MPI

### Description 
A program that estimates the value of π by using the Monte Carlo method

The program was designed with the **tree-structured** point-to-point communication

It also uses the MPI built in function to time the computation of the program

### Program Functions
- **Toss(long long int slicedTosses, int id)**
  - Tosses a dart onto the square *slicedTosses amount of times*
  - If it lands inside the circle area (calculated using (x\*x + y\*y <= 1.0)), it increments total count value
  - Returns the total count value when finished
- **main(int argc, char \*argv[])**
  - Main function of the program

### Sections of The Program
The program can be organized into different sections
- **Initialization of the variable and functions**
- **Tree structured broadcast**
  - Process 0 reads in the total number of tosses then broadcasts it to other processors
  - The broadcast is made with **point-to-point** communication
  - Starts with Processor 0, and eventually it forms a tree structure
- **Function to calculate the toss of the darts**
  - Every processor will be tossing their own darts and having their own calculations
- **Tree structured global sum**
  - The global sum is added by using **point-to-point** communication 
  - All the processors send their results to **processor 0** 
- **Finalization of the program**
  - Prints the final sum
  - Prints the total time it took to run the program

### List of MPI Functions Used
- MPI_Init()
- MPI_Status()
- MPI_Comm_rank()
- MPI_Comm_Size()
- MPI_Wtime()
- MPI_Send()
- MPI_Recv()
- MPI_Finalize()
- MPI_Barrier

### Compilation
`mpiicc -o problem2.out problem2.c`
### Execution
`mpiexec -n (# of processors) problem2.out`
## Results
![Image of a graph](https://github.com/Karen-W-2002/Monte-Carlo-mpi/blob/main/Graph.png)
### Analysis on the results
It is obvious that its a negative slope, which means that the more amount of processors you have running this program, the faster the program runs

You can see that there is a significant increase in the running time when the processor goes from 1 to 2, however the slope does gradually decrease so the new time change isn't as dramatic as more processors are added, but it does make a huge difference the more you add.

### My thoughts
I think the part that was the most interesting was the barriers. It isn't too difficult to learn, however understanding is a bit harder. Sometimes it does not make a difference if you use it or not (at least when you look at the results) but knowing how to use it can improve the code by a lot. There was something I read that quoted "Would the results still be the same if processor 1 ran 100x faster than processor 2" and by thinking about this, that's when you know you have to use barriers.
