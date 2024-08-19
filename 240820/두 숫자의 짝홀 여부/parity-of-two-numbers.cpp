#include <iostream>
using namespace std;

int main() {
    int a, b; cin >> a >> b;
    cout << (a % 2 == 0 ? "even" : "odd") << '\n' << (b % 2 == 0 ? "even" : "odd");
    return 0;
}