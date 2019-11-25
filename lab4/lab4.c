#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

#define MRAND 100000

struct timeval tvs, tve, tvd;

float te()
{
    gettimeofday(&tve, &tz);
    tvd.tv_sec = tve.tv_sec - tvs.tv_sec;
    tvd.tv_usec = tve.tv_usec - tvs.tv_usec;
    if (tvd.tv_usec < 0) {
        tvd.tv_sec--;
        tvd.tv_usec += 1000000;
     }
    return tvd.tv_sec + (float)tvd.tv_usec/1000000;
}

void saxpy(const int A, int* x, int *y, int n)
{
    // Ax + y -> y
    for (int j = 0; j < n; j++) {
        y[j] += x[j] * A;
    }
}

int main()
{
    int n, a;
    printf("n\n");
    scanf("%d", &n);

    a = rand() % 5000;

    int* x = (int*) malloc(n * sizeof(int));
    int* y = (int*) malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        x[i] = rand() % MRAND;
        y[i] = rand() % MRAND;
    }

    // time
    gettimeofday(&tvs, NULL);
    saxpy(a, x, y, n);
    float a = te();

    printf("time spent: %f\n", a);
    return 0;
}