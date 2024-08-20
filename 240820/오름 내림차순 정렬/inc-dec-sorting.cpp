#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool comp(int a, int b) {
    return a > b;
}

int main() {
    vector<int> arr;
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        int tmp; cin >> tmp;
        arr.push_back(tmp);
    }
    sort(arr.begin(), arr.end()); for(int i = 0; i < n; i++) cout << arr[i] << ' ';
    cout << '\n';
    sort(arr.begin(), arr.end(), comp); for(int i = 0; i < n; i++) cout << arr[i] << ' ';
    return 0;
}