#include <iostream>
#include <ctime>

using namespace std;

clock_t s;

void saxpy(const int A, int* x, int *y, int n)
{
    s = clock();
    // Ax + y -> y
    for (int j = 0; j < n; j++) {
        y[j] += x[j] * A;
    }
    s = clock() - s;
}

int main()
{
    int n, A;
    cout << "n" << endl;
    cin >> n;

    cout << "A" << endl;
    cin >> A;

    //cout << endl << "X: ";
    int* Y;
    int* X;
    Y = new int[n];
    X = new int[n];

    for (int i = 0; i < n; i++) {
        X[i] = 2 * i;
    //  cout << 2 * i << " ";
    }

    // cout << endl << "Y: ";
    for (int i = 0; i < n; i++) {
        Y[i] = 10 * i;
    //  cout << 10 * i << " ";
    }

    // cout << endl << "R: ";
    saxpy(A, X, Y, n);
    cout << "time spent: " << ((float)s) / CLOCKS_PER_SEC << endl;
    //for (int i = 0; i < n; i++) {
    //  cout << Y[i] << " ";
    //}
    cout << endl;
    delete (X);
    delete (Y);
    return 0;
}