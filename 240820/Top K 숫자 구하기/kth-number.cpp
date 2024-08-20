#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

    int N, k; cin >> N >> k;
    vector<int> arr;

    for(int i = 0; i < N; i++) {
        int tmp; cin >> tmp;
        arr.push_back(tmp);
    }
    sort(arr.begin(), arr.end());
    cout << arr[k - 1];
    return 0;
}