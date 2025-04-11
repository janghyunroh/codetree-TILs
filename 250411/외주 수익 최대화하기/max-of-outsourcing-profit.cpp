#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int N;
    int * T;
    int * P;
    int * dp;
    
    //input
    cin >> N;
    T = new int[N + 1];
    P = new int[N + 1];
    dp = new int[N + 1];
    fill(dp, dp + N + 1, 0);
    for(int i = 0; i < N; i++) cin >> T[i] >> P[i];

    
    //dp
    int mx = 0;
    for(int i = 0; i <= N; i++) {
        dp[i] = max(mx, dp[i]);
        if(i + T[i] <= N) dp[i + T[i]] = max(dp[i] + P[i], dp[i + T[i]]);   
        mx = max(mx, dp[i]);
    }
    
    cout << mx;
}