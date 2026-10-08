#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int data[8];
    int local_data[8];
    int local_count, i;

    int local_sum = 0, total_sum = 0;
    int local_max, global_max;
    int local_min, global_min;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size > 8 || 8 % size != 0) {
        if (rank == 0)
            printf("Use a number of processes that divides 8 (1, 2, 4, or 8).\n");
        MPI_Finalize();
        return 1;
    }

    if (rank == 0) {
        int temp[8] = {10, 20, 30, 40, 50, 60, 70, 80};
        for (i = 0; i < 8; i++)
            data[i] = temp[i];
    }

    local_count = 8 / size;

    MPI_Scatter(data, local_count, MPI_INT,
                local_data, local_count, MPI_INT,
                0, MPI_COMM_WORLD);

    local_sum = 0;
    local_min = local_data[0];
    local_max = local_data[0];

    for (i = 0; i < local_count; i++) {
        local_sum += local_data[i];

        if (local_data[i] < local_min)
            local_min = local_data[i];

        if (local_data[i] > local_max)
            local_max = local_data[i];
    }

    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM,
               0, MPI_COMM_WORLD);

    MPI_Reduce(&local_max, &global_max, 1, MPI_INT, MPI_MAX,
               0, MPI_COMM_WORLD);

    MPI_Reduce(&local_min, &global_min, 1, MPI_INT, MPI_MIN,
               0, MPI_COMM_WORLD);

    if (rank == 0) {
        double average = (double) total_sum / 8;

        printf("\nDistributed Dataset Statistics Using MPI\n");
        printf("-----------------------------------------\n");
        printf("Dataset: 10 20 30 40 50 60 70 80\n");
        printf("Number of MPI processes: %d\n", size);
        printf("Sum     : %d\n", total_sum);
        printf("Average : %.2f\n", average);
        printf("Maximum : %d\n", global_max);
        printf("Minimum : %d\n", global_min);
    }

    MPI_Finalize();
    return 0;
}
