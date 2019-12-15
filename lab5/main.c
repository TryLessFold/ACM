#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/time.h>

#ifndef THREADS 
#define THREADS 4
#endif

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _b : _a; })

static struct timeval tvs, tve, tvd;

static int *matr[THREADS];
static int *vect, *res, *tmp_res[THREADS];
static pthread_mutex_t lock[THREADS];
static int *x, *y;

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
 
void* mul(void *arg)
{
    int i = *(int *)arg;
    while (!tmp_res[i]);
    while(tmp_res[i])
    {
        int temp = 0;
        for (int j = 0; j < *x; j++)
            temp += vect[j] * matr[i][j];
        *tmp_res[i] = temp;
       
        matr[i] = NULL;
        tmp_res[i] = NULL;
        while (!tmp_res[i]);
    }
}
 
void mult(int *a)
{
	int j;
    for (int i = 0; i < *y; i++){
        j = 0;
        while (tmp_res[j]) {
            j = (j + 1) % THREADS;
        }
        matr[j] = &a[i*(*x)];
        tmp_res[j] = &res[i];
    }
}
 
int main(int argc, char* argv[])
{
	if (argc < 3)
    {
        printf("Usage: ./prog x y \n");
        return 0;
    }

	srand(time(NULL));
	pthread_t tid[THREADS];
    int pth[THREADS];

    int *a;
    float k;

    int n = max(atoi(argv[1]), atoi(argv[2]));
    int m = min(atoi(argv[1]), atoi(argv[2]));

    x = &n;
    y = &m;

    a = malloc(sizeof(int) * n * m);
    vect = malloc(sizeof(int) * n);
    res = malloc(sizeof(int) * m);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            a[i * n + j] = rand() % 11 + 1;
            //printf("%4d", a[i * n + j]);
        }
        //printf("\n");
    }
    //printf("\n");

    for (int i = 0; i < n; i++) {
        vect[i] = rand() % 11 + 1;
        //printf("%4d", vect[i]);
    }
 	//printf("\n\n");
    //printf("1\n");

    for (int i = 0; i < THREADS; i++)
    {
        pth[i] = i;
        matr[i] = NULL;
        tmp_res[i] = NULL;

        if(pthread_create(&(tid[i]),NULL, &mul, &pth[i]))
        {
            printf("\n Thread Init Failed\n");
            return 1;
        }
    }

    //printf("2\n");
    gettimeofday(&tvs, NULL);
    mult(a);
	//printf("3\n");
    for(int i = 0; i < THREADS; i++)
    {
    	while(tmp_res[i]);
        pthread_cancel(tid[i]);
    }
    k = te();
    //printf("4\n");
    free(a);
    free(vect);
    free(res);
    //printf("5\n");
   	printf("%f \n", k);
    //for(int i = 0; i < m; i++) printf("%d ", res[i]);
    return 0;
}