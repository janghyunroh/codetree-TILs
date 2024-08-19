#include <iostream>
using namespace std;

int main() {
    int a; cin >> a;
    int arr[4]; for(int i = 0; i < 4; i++) cin >> arr[i];
    for(int i = 0; i < 4; i++) cout << (a > arr[i]) << '\n';
    return 0;
}