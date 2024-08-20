#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> A, B;
    for(int i = 0; i < n; i++) {
        int tmp; cin >> tmp; A.push_back(tmp);
    }
    for(int i = 0; i < n; i++) {
        int tmp; cin >> tmp; B.push_back(tmp);
    }
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    for(int i = 0; i < n; i++) {
        if(A[i] != B[i]) {
            cout << "No";
            return 0;
        }
    }
    cout << "Yes";
    return 0;
}