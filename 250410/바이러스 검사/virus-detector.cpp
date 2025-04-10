#include <iostream>
#include <cmath>

typedef long long ll;

using namespace std;

// 팀장이 a, 팀원이 b, 고객 수가 c -> a + k * b > c -> k > (c - a) / b
// k = ceil (c-a)/b
// 각 식당에 대한 정답 = k + 1
// sum(k+1)

//최대 범위 : 1000000 x 1000000 -> long long 필요

int n, a, b;
int customePerStore[1000000];
int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    //input
    cin >> n;
    for(int i =0; i < n; i++) {
        cin >> customePerStore[i];
    }
    cin >> a >> b;

    //solve
    ll sm = 0;
    for(int i = 0; i < n; i++) {
        ll k = ceil(((float)customePerStore[i] - a) / b);
        sm += (k + 1);
    }
    cout << sm;
    return 0;
}