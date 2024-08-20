#include <iostream>
using namespace std;

int main() {
    int a, b;
    char ax, bx;
    cin >> a >> ax >> b >> bx;
    if((a >=19 && ax == 'M') || (b >= 19 && bx == 'M')) cout << 1;
    else cout << 0;
    return 0;
}