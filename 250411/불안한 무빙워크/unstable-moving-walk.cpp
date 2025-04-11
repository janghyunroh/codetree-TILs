#include <iostream>
#include <deque>

using namespace std;

int N, K;
deque<int> dq1; // 위 내구도
deque<int> dq2; // 아래 내구도
deque<bool> robots; // 로봇 존재 여부

int main() {
    
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    //input
    cin >> N >> K;
    for(int i = 0; i < N; i++) {
        int tmp; cin >> tmp;
        dq1.push_back(tmp);
    }
    for(int i = 0; i < N; i++) {
        int tmp; cin >> tmp;
        dq2.push_back(tmp);
    }
    for(int i = 0; i < N; i++) {
        robots.push_back(false);
    }
    
    //simulate
    int cnt = 0;
    //cout << "start" << '\n';
    while(K > 0) {
        
        //1. 벨트 및 로봇 회전
        
        //1-1 벨트 덱 회전
        int tmp = dq1.back(); dq1.pop_back();
        dq2.push_front(tmp); tmp = dq2.back(); dq2.pop_back();
        dq1.push_front(tmp);
        //cout << cnt << " belt rotated\n";
        
        //1-2 로봇 덱 회전
        robots.pop_back(); 
        if(robots.back()==true) robots.back() = false; // 내리기
        robots.push_front(false);
        //cout << cnt << " robots rotated\n";
        
        //2. 이동 가능 시 이동(뒤부터 순서대로) & 내구도 갱신
        for(int i = N - 2; i >= 0; i--) { //맨 끝은 항상 없으므로
            if(robots[i] && !robots[i+1] && dq1[i+1] > 0) {
                robots[i] = false; robots[i+1] = true;
                dq1[i+1]--;
                if(dq1[i+1] == 0) K--;
                if(i+1 == N-1) robots[i+1] = false;
            }
        }
        
        //4. 로봇 올림
        if(!robots[0] && dq1[0] > 0) {
            robots[0] = true; 
            dq1[0]--;
            if(dq1[0] == 0) K--;
        }
        
        cnt++;
    }
    
    cout << cnt;
    return 0;
}
