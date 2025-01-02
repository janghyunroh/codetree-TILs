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
    cout << GCD(n, m);
    return 0;
}