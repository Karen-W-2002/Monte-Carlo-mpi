# Monte-Carlo-mpi
Program written in C with the use of MPI

### Description 


### Program Functions

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
- **Tree structured global sum**
  - The global sum is added by using **point-to-point** communication 
  - All the processors send their results to **processor 0** 
- **Finalization of the program**

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

