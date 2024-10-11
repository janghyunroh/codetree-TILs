#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

priority_queue<pair<int, pair<int, int>>> pq;
int main() {
    
    int n;
    cin >> n;

    int x;
    for(int i = 0; i < n; i++) {
        cin >> x;
        pq.push({x, {x, 1}});
    }

    for(int i = 0; i < n; i++) {
        auto t = pq.top();
        pq.pop();
        int origin = t.second.first;
        int idx = t.second.second;
        pq.push({origin / (idx + 1), {origin, idx + 1}});

        if(i==n-1) cout << t.first;
    }
    return 0;
}