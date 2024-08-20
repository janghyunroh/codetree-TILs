#include <iostream>
using namespace std;

int main() {
    int n; cin >> n;
    if(n==2) cout << 28;
    else if(n < 8) {
        if(n % 2 == 0) cout << 30;
        else cout << 31;
    }
    else {
        if(n%2==0) cout << 31;
        else cout << 30;
    }
    return 0;
}