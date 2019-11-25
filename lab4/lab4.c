#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <malloc.h>

#define MRAND 100000

struct timeval tvs, tve, tvd;

float te()
{
    gettimeofday(&tve, NULL);
    tvd.tv_sec = tve.tv_sec - tvs.tv_sec;
    tvd.tv_usec = tve.tv_usec - tvs.tv_usec;
    if (tvd.tv_usec < 0)
    {
        tvd.tv_sec--;
        tvd.tv_usec += 1000000;
    }
    return tvd.tv_sec + (float)tvd.tv_usec / 1000000;
}

void saxpy(const int A, int *x, int *y, int n)
{
    // Ax + y -> y
    for (int j = 0; j < n; j++)
    {
        y[j] += x[j] * A;
    }
}

void DGEMM(int M, int N, int K, const double *A, const double *B, double *C)
{
    for (int i = 0; i < M; ++i)
    {
        double *c = C + i * N;
        for (int j = 0; j < N; ++j)
            c[j] = 0;
        for (int k = 0; k < K; ++k)
        {
            const double *b = B + k * N;
            double a = A[i * K + k];
            for (int j = 0; j < N; ++j)
                c[j] += a * b[j];
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 1;
    float k = 0;
    if (atoi(argv[1]) == 0)
    {
        int n, a;
        n = atoi(argv[2]);
        a = rand() % 5000;
        int *x = (int *)malloc(n * sizeof(int));
        int *y = (int *)malloc(n * sizeof(int));

        for (int i = 0; i < n; i++)
        {
            x[i] = rand() % MRAND;
            y[i] = rand() % MRAND;
        }

        //time
        gettimeofday(&tvs, NULL);
        saxpy(a, x, y, n);
        k = te();
        printf("SAXPY");
    }
    else
    {
        if (argc < 3)
            return 1;
        int M, N, K;
        M = atoi(argv[1]);
        N = atoi(argv[2]);
        K = atoi(argv[3]);
        double *A, *B, *C;
        A = malloc((sizeof(double) * K) * M);
        B = malloc((sizeof(double) * N) * K);
        C = malloc((sizeof(double) * N) * M);
        for (int i = 0; i < M; i++)
            for (int j = 0; j < K; j++)
            {
                A[i * K + j] = (rand() % 10000) / 123.23;
            }
        for (int i = 0; i < K; i++)
            for (int j = 0; j < N; j++)
            {
                B[i * N + j] = (rand() % 10000) / 123.12;
            }
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
            {
                C[i * N + j] = 0;
            }
        gettimeofday(&tvs, NULL);
        DGEMM(M, N, K, A, B, C);
        k = te();
        // for (int i = 0; i < M; i++)
        // {
        //     for (int j = 0; j < K; j++)
        //     {
        //         printf("%5.3f ", A[i * K + j]);
        //     }
        //     printf("\n");
        // }
        // printf("\n");
        // for (int i = 0; i < K; i++)
        // {
        //     for (int j = 0; j < N; j++)
        //     {
        //         printf("%5.3f ", B[i * N + j]);
        //     }
        //     printf("\n");
        // }
        // printf("\n");
        // for (int i = 0; i < M; i++)
        // {
        //     for (int j = 0; j < N; j++)
        //     {
        //         printf("%5.3f ", C[i * N + j]);
        //     }
        //     printf("\n");
        // }
        printf("DGEMM");
    }

    printf(" time spent: %f\n", k);
    return 0;
}