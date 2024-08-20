#include <iostream>
using namespace std;

int main() {
    int a, b, c; cin >> a >> b >> c;
    cout << ((a <= b && a <= c) ? 1 : 0) << ' ' << ((a==b && b == c) ? 1 : 0);
    return 0;
}