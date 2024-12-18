#include <iostream>

#define MAXN 60005

using namespace std;

int N;
double x[MAXN], v[MAXN];

int main() {
    cin >> N;

    for (int i=0; i < N; i++) cin >> x[i];
    for (int i=0; i < N; i++) cin >> v[i];

    double low = 0, high = 1e10;
    double eps = 1e-8;

    while (high-low > eps) {
        double mid = (high + low) / 2;

        double left = 0, right = 1e9;

        for (int i=0; i<N; i++) {
            left = max(left, x[i] - mid*v[i]);
            right = min(right, x[i] + mid*v[i]);
        }

        if (left < right) high = mid;
        else low = mid;
    }

    printf("%.12f\n", low);

    return 0;
}