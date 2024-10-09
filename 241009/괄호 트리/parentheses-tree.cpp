#include <iostream>
using namespace std;


// 스택 필요 없을 듯?

string s;
int main() {
    cin >> s;
    long long cur_depth = 0;
    long long ans = 0;
    char prev_par;
    for(int i =0; i < s.length(); i++) {
        if(s[i] == '(') {
            cur_depth += 1;
        }
        else {
            cur_depth -= 1;
            if(prev_par == '(') ans += cur_depth;
        }
        prev_par = s[i];
    }
    cout << ans;
    return 0;
}