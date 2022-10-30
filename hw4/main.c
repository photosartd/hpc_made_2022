#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <stdbool.h>

void zeroMatrix(double * A, int N)
{
    int i, j;
#pragma omp parallel for private(i,j) shared(A)
    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        {
            A[i * N + j] = 0.0;
        }
    }
}

void printMatrix(double* M, int N)
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            printf("%f\t", M[i * N + j]);
        }
        printf("\n");
    }
}

void printVector(double* M, int N)
{
    for(int i = 0; i < N; i++)
    {
        printf("%f\n", M[i]);
    }
}

double* generateRandomGraph(int N, double prob)
{
    double *G = (double *) malloc(N * N * sizeof(double));
    srand(time(NULL));

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            double randn = (double)rand() / RAND_MAX;
            if (randn < prob && i != j) 
                G[i * N + j] = 1.0;
            else 
                G[i * N + j] = 0.0;
        }
    }

    return G;
}

double* matmul(const double* A, const double* B, int N)
{
    double *C = (double *) malloc(N * N * sizeof(double));
    zeroMatrix(C, N);
    int i, j, k;
    #pragma omp parallel for private(i,j,k) shared(A,B,C) num_threads(8)    
    for (k = 0; k < N; k++)
            for(i = 0; i < N; i++)
            {
                for(j = 0; j < N; j++)
                    C[i * N + j] = C[i * N + j] + A[i * N + k] * B[k * N + j];
            }
    return C;
}

double* mat_pow(double* A, int N, int power) {
    if (power == 1) {
        return A;
    }
    else if (power == 2) {
        return matmul(A, A, N);
    }
    else {
        int pow1 = power / 2;
        int pow2 = power - pow1;
        return matmul(mat_pow(A, N, pow1), mat_pow(A, N, pow2), N);
    }
}

double* readGraph(char* path, int N)
{
    double *G = (double *) malloc(N * N * sizeof(double));

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(path, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    int row = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        int col = 0;
        char *token = strtok(line, ",");
        while (token != NULL)
        {
            int t = atoi(token);
            G[row * N + col] = (double) t;
            token = strtok(NULL, ",");
            col++;
        }
        row++;
    }

    fclose(fp);
    if (line)
        free(line);
    return G;
}

double* sum(double* A, int N)
{
    double* SUM = (double*) malloc(N * sizeof(double));
    int i, j;
    double curr_sum = 0.0;

#pragma omp parallel for private(i, j, curr_sum) shared(A, SUM) num_threads(8)    
    for (j = 0; j < N; j++) {
        curr_sum = 0.0;
        for (i = 0; i < N; i++) {
            curr_sum += A[i * N + j];
        }
        SUM[j] = curr_sum;
    }
    return SUM;
}

void norm_col(double* A, int N)
{
    double* sum_col = sum(A, N);
    int i, j;

#pragma omp parallel for private(i, j) shared(A, sum_col) num_threads(8)    
    for (j = 0; j < N; j++) {
        for (i = 0; i < N; i++) {
            A[i * N + j] /= sum_col[j];
        }
    }
}

double* mult_num(double* A, int N, double num)
{
    double* C = (double*) malloc(N * N * sizeof(double));

    int i, j;

    #pragma omp parallel for private(i, j) shared(A, C, N, num) num_threads(8)   
    for (j = 0; j < N; j++) {
        for (i = 0; i < N; i++) {
            C[i * N + j] = A[i * N + j] * num;
        }
    }
    
    return C;
}

double* sum_num(double* A, int N, double num)
{
    double* C = (double*) malloc(N * N * sizeof(double));

    int i, j;

    #pragma omp parallel for private(i, j) shared(A, C, N, num) num_threads(8)   
    for (j = 0; j < N; j++) {
        for (i = 0; i < N; i++) {
            C[i * N + j] = A[i * N + j] + num;
        }
    }
    
    return C;
}

double* ones(int N, bool normed)
{
    double* vec = (double*) malloc(N * sizeof(double));
    int i;

#pragma omp parallel for private(i) shared(vec, N, normed) num_threads(8)
    for (i = 0; i < N; i++) {
        if (normed) {
            vec[i] = 1.0 / (double) N;
        }
        else {
            vec[i] = 1.0;
        }
    }
    return vec;
}

double* zeros(int N)
{
    double* vec = (double*) malloc(N * sizeof(double));
    int i;

#pragma omp parallel for private(i) shared(vec, N) num_threads(8)
    for (i = 0; i < N; i++) {
        vec[i] = 0.0;
    }
    return vec;
}

double* mat_vec_mul(double* mat, double* vec, int N)
{
    double* new_vec = zeros(N);
    int i, j;

    #pragma omp parallel for private(i, j) shared(vec, mat, new_vec, N) num_threads(8)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            new_vec[i] += vec[j] * mat[i * N + j];
        }
    }
    return new_vec;
}


int main(int argc, char** argv)
{
    int N = 194;
    double prob = 0.8;
    int num_iter = 20;
    //double* G = generateRandomGraph(N, prob);
    char* path = "./moscow_metro_graph.txt";
    double* G = readGraph(path, 194);
    norm_col(G, N);
    double* v = ones(N, true);

    //PageRank
    double d = 0.85;
    G = sum_num(mult_num(G, N, d), N, (1.0 - d) / (double) N);
    v = mat_vec_mul(mat_pow(G, N, num_iter), v, N);

    printf("PageRank:");
    for (int i = 0; i < N; i++) {
        printf("%d\t%f\n", i, v[i]);
    }
    printf("Naive:");
    double* GG = readGraph(path, 194);
    double* GG_sum = sum(GG, N);
    for (int i = 0; i < N; i++) {
        printf("%d\t%f\n", i, GG_sum[i]);
    }


    return 0;
}