/*

승패가 다르려면 1차이 나야 함!

D = |1라 승수 - 2라 승수| 배열


k, k + 1번째 승패 따지기
-> k - 1, k번쨰 승패 

dp[i][k] : i와 i + 1 사이의 승패에 대해서 
1라, 2라 승수가 같을 수 있으면 k = 0일 때 true
1라, 2라 승수가 다를 수 있으면 k = 1일 때 true


*/
#include <iostream>

using namespace std;

int n;
int D[1000001];

bool dp[1000001][2];


string solve() {

    // init
    if(D[1] == 0) dp[1][0] = true;
    else if(D[1] == 1) dp[1][1] = true;
    else return "NO";

    for(int i = 2; i <= n; i++) {

        if(D[i] == 0) {
            if(dp[i - 1][0]) dp[i][0] = true;
            if(dp[i - 1][1]) dp[i][1] = true;
        }

        else if(D[i] == 1) {
            if(dp[i - 1][0]) dp[i][1] = true;
            if(dp[i - 1][1]) dp[i][0] = true;
        }

        else if(D[i] == 2 && dp[i - 1][1]) dp[i][1] = true;

        else return "NO";
    }

    if((D[n] == 0 && dp[n - 1][0]) || (D[n] == 1 && dp[n - 1][1])) return "YES";
    else return "NO";
}
int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    for(int i = 1; i <= n; ++i) cin >> D[i];
    
    cout << solve() << '\n';
    return 0;
}