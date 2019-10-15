#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

struct timeval tvs, tve, tvd;
struct timezone tz;

long f(int n) {if (n == 0) return 1; else return (n * f(n - 1)); }

void ts()
{
    gettimeofday(&tvs, &tz);
}

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

int prime(int n)
{
    int lala = 0;
    int j;
    for(int i = 2; i<n; i++)
    {
        for(j = 2; j<=i/2; j++)
            if (i%j==0) break;
        if (j>i/2) lala++;
    }
    return lala;
}

int main(int argc, char* argv[]){
    double v;
    if ((argc <=1)||(argc>2)) return 0;

    ts();
    int r = prime(atoi(argv[1]));
    float a = te();

    printf("%d\n", r);
    printf("%f\n", a);

    return 0;
}
