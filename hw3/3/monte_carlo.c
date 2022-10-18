#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
    const size_t N = 1000000000;
    int i, tid;
    int hits = 0;

    #pragma omp parallel default(none) shared(N) private(i, tid) reduction(+ : hits)
    {
        tid = omp_get_thread_num();
        unsigned int seed = 1234 * tid;
        double x, y;

        #pragma omp for private(x, y)
        for (i = 0; i < N; i++) {
            x = ((double) rand_r(&seed) / RAND_MAX) - 0.5;
            y = ((double) rand_r(&seed) / RAND_MAX) - 0.5;
            double circle = x * x + y * y;
            if (circle <= 0.25) {
                hits += 1;
            }
        }
    }
    printf("npoints: %d \n", N);
    printf("n_hits: %d \n", hits);
    double res = 4 * (double) hits / N;
    printf("p_est: %f \n", res);

    return 0;
}