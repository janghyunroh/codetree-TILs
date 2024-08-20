#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n; cin >> n;
    vector<string> strs;
    for(int i = 0; i < n; i++) {
        string tmp; cin >> tmp;
        strs.push_back(tmp);
    }
    sort(strs.begin(), strs.end());
    for(string str : strs) cout << str << '\n'; 
    return 0;
}