# Distributed Dataset Statistics Using MPI

## Objective
Calculate the **sum, average, maximum, and minimum** of a dataset using multiple MPI processes.

## Technology Used
- C
- MPI (Message Passing Interface)
- Open MPI
- Ubuntu Linux
- VMware

## Dataset
The program uses the following sample dataset:

`10 20 30 40 50 60 70 80`

## MPI Functions Used
- `MPI_Init()` - Initializes MPI.
- `MPI_Comm_rank()` - Gets the rank of each process.
- `MPI_Comm_size()` - Gets the total number of processes.
- `MPI_Scatter()` - Distributes the dataset among processes.
- `MPI_Reduce()` - Combines local results.
- `MPI_Finalize()` - Terminates MPI.

## How to Compile

```bash
mpicc dataset_statistics.c -o statistics
```

## How to Run

Use 1, 2, 4, or 8 processes:

```bash
mpirun -np 4 ./statistics
```

If your Ubuntu system requires it:

```bash
mpirun --allow-run-as-root -np 4 ./statistics
```

## Expected Output

```text
Distributed Dataset Statistics Using MPI
-----------------------------------------
Dataset: 10 20 30 40 50 60 70 80
Number of MPI processes: 4
Sum     : 360
Average : 45.00
Maximum : 80
Minimum : 10
```

## Working
1. The master process contains the dataset.
2. `MPI_Scatter()` divides the dataset among MPI processes.
3. Each process calculates its local sum, maximum, and minimum.
4. `MPI_Reduce()` combines the local results at the master process.
5. The master calculates the final average.

## Conclusion
MPI allows the dataset to be processed in parallel by multiple processes. This demonstrates distributed statistical computation using the Master-Worker approach.
