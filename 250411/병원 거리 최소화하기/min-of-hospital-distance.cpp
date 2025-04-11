#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
int map[50][50];
vector<pair<int, int>> houses; 
vector<pair<int, int>> chickenStores; 
vector<int> ans_stores; // 후보 치킨집들의 chickenStores 상 인덱스
bool visited[13] = {false, };
int mn = 987654321;

// O(M) 
int chickenDistForSingleHouse(int x, int y) {
    int dist = 1000;
    for(auto it : ans_stores) {
        
        int r = chickenStores[it].first;
        int c = chickenStores[it].second;
        dist = min(dist, abs(r - x) + abs(c - y));
    }
    return dist;
}

//O(N x M)
int chickenDistForCity() {
    int dist = 0;
    for(auto it : houses) {
        dist += chickenDistForSingleHouse(it.first, it.second);
    }
    return dist;
}

void solve(int store_num, int last) {
    // end case
    if(store_num == M) {
        mn = min(mn, chickenDistForCity());
        return ;
    }
    
    //avg case
    for(int i = last; i < chickenStores.size(); i++) {
        if(!visited[i]) {
            visited[i] = true;
            ans_stores.push_back(i);
            solve(store_num + 1, i + 1);
            visited[i] = false;
            ans_stores.pop_back();
        }
    }
}

int main() {
    cin >> N >> M;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            int tmp; cin >> tmp;
            if(tmp == 1) {
                houses.emplace_back(i, j);
            }
            else if(tmp == 2) {
                chickenStores.emplace_back(i, j);
            }
        }
    }
    solve(0, 0);
    cout << mn << '\n';
    return 0;
}