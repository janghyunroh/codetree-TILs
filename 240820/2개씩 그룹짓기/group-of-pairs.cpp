#include <iostream>
#include <algorithm>
using namespace std;

int N;
int arr[2000];

int main() {
    int N; cin >> N;
    for(int i = 0; i < N * 2; i++) {
        cin >> arr[i];
    }
    sort(arr, arr + (N * 2));
    int max_sum = 0;
    for(int i=0;i<N;i++) {
        max_sum = max(max_sum, arr[i] + arr[N*2 - i - 1]);
    }
    cout << max_sum;
    return 0;
}