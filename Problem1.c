#include <stdio.h>
	#include <stdlib.h>
	#include <omp.h>
	#include <time.h>

	#define N 10000000

	//Comparator ASC
	int compare(const void *a, const void *b) {
	    return (*(int *)a - *(int *)b);
	}

	// Comparator DESC
	int compare_desc(const void *a, const void *b) {
	    return (*(int *)b - *(int *)a);
	}

	int main() {
	    //Allocate memory for array
	    int *a = (int *)malloc(N * sizeof(int));
	    int *b = (int *)malloc(N * sizeof(int));

	    if (a == NULL || b == NULL) {
		printf("Error: Unable to allocate memory for arrays.\n");
		return 1;
	    }

	    // Initialize arrays with random values
	    for (int i = 0; i < N; i++) {
		a[i] = rand() % 100;
		b[i] = rand() % 100;    //0-99 values
	    }

	    // Sort array `a` in ascending order
	    qsort(a, N, sizeof(int), compare);

	    // Sort array `b` in descending order
	    qsort(b, N, sizeof(int), compare_desc);

	    // Compute the minimum scalar product
	    long long int min_product = 0;
	    double start_time, end_time;

	    // Sequential computation
	    start_time = omp_get_wtime();  // Start time
	    for (int i = 0; i < N; i++) {
		min_product += (long long int)a[i] * b[i];
	    }
	    end_time = omp_get_wtime();    // End time
	    printf("Minimum scalar product (sequential): %lld\n", min_product);
	    printf("Time taken (sequential): %f seconds\n", end_time - start_time);

	    // Parallel computation
	    long long int parallel_product = 0;
	    start_time = omp_get_wtime();  // Start time

	    #pragma omp parallel for reduction(+:parallel_product)
	    for (int i = 0; i < N; i++) {
		parallel_product += (long long int)a[i] * b[i];
	    }

	    end_time = omp_get_wtime();    // End time
	    printf("Minimum scalar product (parallel): %lld\n", parallel_product);
	    printf("Time taken (parallel): %f seconds\n", end_time - start_time);

	    // Free allocated memory
	    free(a);
	    free(b);

	    return 0;
	}