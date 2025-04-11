#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

int N;
int table[400][5];  // 각 행: {학생번호, 선호하는 학생 4명}
int seats[20][20];  // 실제 N x N의 자리 행렬. 0이면 빈 자리
int studentIndex[401]; // 학생 번호 -> table에서의 인덱스

// (x, y) 자리의 인접 칸 중, table[idx]에 기록된 선호 학생이 몇 명 있는지 계산
int calculate_favs_by_index(int idx, int x, int y) {
    int cnt = 0;
    for (int d = 0; d < 4; d++) {
        int nx = x + dx[d], ny = y + dy[d];
        if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
            // table[idx][1~4]에 기록된 학생 번호와 좌석의 학생 번호 비교
            for (int l = 1; l <= 4; l++) {
                if (table[idx][l] == seats[nx][ny]) {
                    cnt++;
                    break;
                }
            }
        }
    }
    return cnt;
}

// (x, y) 자리 주변에 빈 자리의 수 계산
int calculateEmpties(int x, int y) {
    int cnt = 0;
    for (int d = 0; d < 4; d++) {
        int nx = x + dx[d], ny = y + dy[d];
        if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
            if (seats[nx][ny] == 0)
                cnt++;
        }
    }
    return cnt;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    //input
    
    cin >> N;
    // 학생 수는 N*N이고, 각 학생마다 "학생번호 선호학생1 선호학생2 선호학생3 선호학생4" 형식으로 입력
    for (int i = 0; i < N * N; i++){
        for(int j = 0; j < 5; j++) cin >> table[i][j];
        int stu = table[i][0];
        studentIndex[stu] = i; // 학생 번호로 table에서의 인덱스 기록
    }
    
    // 좌석 배열 초기화 (0이면 빈 자리)
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            seats[i][j] = 0;
        }
    }
    
    // solve
    // 각 학생을 순서대로 배치
    for (int i = 0; i < N * N; i++){
        int stu = table[i][0];
        vector<pair<int,int>> candidates; // 후보 좌석 (행, 열)
        int max_favs = -1;
        
        // 1. 빈 자리 중, 인접한 칸에 선호하는 학생이 가장 많은 자리 찾기
        for (int r = 0; r < N; r++){
            for (int c = 0; c < N; c++){
                if(seats[r][c] != 0) continue; // 이미 배정된 자리 건너뛰기
                int favs = calculate_favs_by_index(i, r, c);
                if(favs > max_favs){
                    max_favs = favs;
                    candidates.clear();
                    candidates.push_back({r, c});
                } else if(favs == max_favs){
                    candidates.push_back({r, c});
                }
            }
        }
        
        // 2. 후보 좌석 중, 인접한 빈 자리 수가 가장 많은 자리 선택
        vector<pair<int,int>> candidates2;
        int max_empties = -1;
        for(auto pos : candidates){
            int r = pos.first, c = pos.second;
            int empties = calculateEmpties(r, c);
            if(empties > max_empties){
                max_empties = empties;
                candidates2.clear();
                candidates2.push_back({r, c});
            } else if(empties == max_empties){
                candidates2.push_back({r, c});
            }
        }
        // 3. 행 번호, 열 번호 순으로 tie-break하여 최종 선택 (가장 앞선 자리)
        sort(candidates2.begin(), candidates2.end());
        int x = candidates2[0].first;
        int y = candidates2[0].second;
        seats[x][y] = stu; // 해당 자리에 학생 번호 배정
    }
    
    // 만족도 계산
    int totalSatisfaction = 0;
    for (int r = 0; r < N; r++){
        for (int c = 0; c < N; c++){
            int stu = seats[r][c];
            int idx = studentIndex[stu];  // table에서의 인덱스
            int favs = calculate_favs_by_index(idx, r, c);
            if (favs > 0) totalSatisfaction += (int)pow(10, favs - 1);
        }
    }
    cout << totalSatisfaction << "\n";
    
    return 0;
}
