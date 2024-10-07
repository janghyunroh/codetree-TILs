#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;
/*

1. 리드 클라이밍
2. 스피드 클라이밍
3. 볼더링

1) 곱
2) 합
3) 등번호

*/

//정렬용 함수
bool comp(tuple<int, int, int> &a, tuple<int, int, int> &b) {
    if(get<0>(a) == get<0>(b)) {
        if(get<1>(a) == get<1>(b)) {
            return get<2>(a) < get<2>(b);
        }
        else return get<1>(a) < get<1>(b);
    }
    else return get<0>(a) < get<0>(b);
}

vector<tuple<int, int, int>> players;
int n;
int main() {
    cin >> n;
    int b, p, q, r;
    for(int i = 0; i < n; i++) {
        cin >> b >> p >> q >> r; 
        int mul = p * q * r;
        int sum = p + q + r;
        
        players.emplace_back(mul, sum, b);
    }

    sort(players.begin(), players.end(), comp);
    cout << get<2>(players[0]) << ' ' << get<2>(players[1]) << ' ' << get<2>(players[2]);
    return 0;
}