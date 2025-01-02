#include <iostream>

using namespace std;

int n, m;

int GCD(int a, int b) {
    int r = 1;
    while(r != 0) {
        r = a % b;
        a = b; 
        b = r;
    }
    return a;
}

int main() {
    cin >> n >> m;

    int g = GCD(n, m);
    cout << (n / g) * (m / g) * g;

    return 0;
}