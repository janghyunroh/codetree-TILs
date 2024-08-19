#include <iostream>
using namespace std;

int main() {
    int tmp; cin >> tmp;
    if(tmp < 0) cout << "ice";
    else if(tmp >=100) cout << "vapor";
    else cout << "water";
    return 0;
}