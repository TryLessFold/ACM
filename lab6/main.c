#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/time.h>
#include<time.h>

static struct timeval tvs, tve, tvd;

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

void init(double *a, double *b, double *c, int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i * n + j] = (rand()%100+1)/11.0;
            b[i * n + j] = (rand()%100+1)/11.0;
            c[i * n + j] = 0.0;
        }
    }
}

void print(double *a, int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%5.2f ", a[i * n + j]);
        }
        printf("\n");
    }
    printf("\n");
}

void dgemm_std(double *a, double *b, double *c, int n)
{
    int i, j, k;

    for (i = 0; i < n; i++) {
	for (j = 0; j < n; j++) {
		for (k = 0; k < n; k++) {
			c[i * n + j] += a[i* n + k] * b[k * n + j];
		}
	}
}

}

void dgemm_transpose(double *a, double *b, double *c, int n)
{
    int i, j, k;

    for (i = 0; i < n; i++) {
        for (k = 0; k < n; k++) {
            for (j = 0; j < n; j++) {
                c[i * n + j] += a[i * n + k] * b[k * n + j];
            }
        }
    }
}

int dgemm_block(double *a, double *b, double *c, int n, int BS)
{
    int i, j, k, i0, j0, k0;
    double *c0, *a0, *b0;

    if (BS<1) return -1;

    for (i = 0; i < n; i += BS) {
        for (j = 0; j < n; j += BS) {
            for (k = 0; k < n; k += BS) {
                for (i0 = 0, c0 = (c + i * n + j), a0 = (a + i * n + k); i0 < BS; ++i0, c0 += n, a0 += n) {
                    for (k0 = 0, b0 = (b + k * n + j); k0 < BS; ++k0, b0 += n) {
                        for (j0 = 0; j0 < BS; ++j0) {
                            c0[j0] += a0[k0] * b0[j0];
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
	if (argc < 3) return -1;

	srand(time(NULL));
	
	int n = atoi(argv[1]);
	int BS = atoi(argv[2]); 

	double *a, *b, *c;
	float timer;

	a = malloc(n*n*(sizeof(double)));
	b = malloc(n*n*(sizeof(double)));
	c = malloc(n*n*(sizeof(double)));
	
	init(a, b, c, n);

	gettimeofday(&tvs, NULL);
	dgemm_std(a, b, c, n);
	timer = te();

	printf("%f ", timer);
	
	init(a, b, c, n);

	gettimeofday(&tvs, NULL);
	dgemm_transpose(a, b, c, n);
	timer = te();

	printf("%f ", timer);

	init(a, b, c, n);

	gettimeofday(&tvs, NULL);
	dgemm_block(a, b, c, n, BS);
	timer = te();

	printf("%f\n", timer);

	return 0;
}
