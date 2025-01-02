#include <iostream>

using namespace std;

int N;

int main() {
    cin >> N;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cout << (N * i + j) % 9 + 1 << ' ';
        }
        cout << '\n';
    }

    return 0;
}