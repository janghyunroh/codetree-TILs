#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

int n;
int cur_pos; 
tuple<char, int> arr[2000001];
int main() {

    //input
    cin >> n;
    for(int i = 0; i < n; i++) {
        int x; char c; int dist; 
        cin >> x >> c >> dist;
        arr[x + 1000000] = make_pair(c, dist);
    }
    cin >> cur_pos;

    //simulate
    for(int i = 0; i < n; i++) {
        if(get<0>(arr[cur_pos + 1000000]) == 'R')
            cur_pos += get<1>(arr[cur_pos + 1000000]);
        else {
            cur_pos -= get<1>(arr[cur_pos + 1000000]);
        }
    }
    cout << cur_pos;
    return 0;
}