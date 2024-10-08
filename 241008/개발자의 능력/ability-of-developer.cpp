#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

int ability[12];
int where[12] = {0,0,0,1,1,1,2,2,2,3,3,3};
int ans = INT_MAX;
int main() {
    
    for(int i = 0; i < 12; i++) {
        cin >> ability[i];
    }

    do {
        int team[4] = {0, 0, 0, 0};
        //team[i]: i번 팀의 점수 합산

        for(int i = 0; i < 12; i++) {
            team[where[i]] += ability[i];
        }

        sort(team, team + 4);
        ans = min(team[3] - team[0], ans);
    } while(next_permutation(where, where+12));

    cout << ans;
    return 0;
}