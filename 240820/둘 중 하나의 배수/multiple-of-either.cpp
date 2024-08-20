#include <iostream>
using namespace std;

int main() {
    int a; cin >> a;
    cout << ((a % 3 == 0 || a % 5 == 0) ? 1 : 0);
    return 0;
}