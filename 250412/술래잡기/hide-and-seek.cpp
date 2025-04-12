/*
정중앙 시작(N x N, N은 항상 홀수)
도망자 M명. 좌우(오른쪽) or 상하(아래)
나무 h개

도망자 이동 -> 술래 이동 

1. 도망자 이동
 - 거리가 3 이하인 애들만 이동
 - 맨해튼 거리로 판별 후 이동

  - 나가는 경우
    일단 먼저 돌림
    술래 없으면 ㄱ
  - 안 나가는 경우
    술래 없으면 ㄱ

2. 술래 이동
 - 달팽이 이동
    꺾는 곳이면 이동 후 꺾기까지 끝냄. 
 - 도망자 잡기(시야 이용)
    -> 여기서 나무가 있는 경우 가려짐!!!!!
 - 잡은만큼 점수 갱신 (턴 수 x 명 수)
*/

#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <tuple>

#define MAX_N 100
#define DIR_NUM 4

using namespace std;

int N, M, h, k;

vector<int> hiders[MAX_N][MAX_N];
vector<int> next_hiders[MAX_N][MAX_N];
bool tree[MAX_N][MAX_N];

int seeker_next_dir[MAX_N][MAX_N];
int seeker_rev_dir[MAX_N][MAX_N];
pair<int, int> seeker_pos;
bool forward_facing = true;
int ans;

void initializeSeekerPath() {

    //상 - 우 - 좌 - 하(시계방향)
    int dx[DIR_NUM] = {-1, 0, 1, 0};
    int dy[DIR_NUM] = {0, 1, 0, -1};

    int cx = N / 2; int cy = N / 2;
    int move_dir = 0; 
    int move_num = 1;

    // cx, cy가 N/2, N/2 -> 0, 0으로 이동할 때까지 경로 기록
    while(cx || cy) {

        for(int i = 0; i < move_num; i++) {
            seeker_next_dir[cx][cy] = move_dir;
            cx += dx[move_dir];
            cy += dy[move_dir];

            // 반대 방향 행렬은 반대방향으로 기록
            seeker_rev_dir[cx][cy] = (move_dir < 2);

            if(!cx && !cy) break;
        }

        move_dir = (move_dir + 1) % 4;
        if(move_dir == 0 || move_dir == 2) move_num++;
    }
}

bool inRange(int x, int y) {
    return 0 <= x && x < N && 0 <= y && y < N;
}

// 
void hiderMove(int x, int y, int move_dir) {

    int dx[DIR_NUM] = {0, 0, 1, -1};
    int dy[DIR_NUM] = {-1, 1, 0, 0};

    int nx = x + dx[move_dir];
    int ny = y + dy[move_dir];

    if(!inRange(nx, ny)) {
        move_dir = (move_dir < 2) ? (1 - move_dir) : (5 -  move_dir);
        nx = x + dx[move_dir];
        ny = y + dy[move_dir];
    }

    if(make_pair(nx, ny) != seeker_pos) {
        next_hiders[nx][ny].push_back(move_dir);
    }

    else {
        next_hiders[x][y].push_back(move_dir);
    }
}

int distFromSeeker(int x, int y) {
    int seeker_x = seeker_pos.first;
    int seeker_y = seeker_pos.second;

    return abs(x - seeker_x) + abs(y - seeker_y);
}

void hiderMoveAll() {

    //초기화
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            next_hiders[i][j].clear();
        }
    }

    // hider 이동
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {

            if(distFromSeeker(i, j) <= 3) {
                for(int k = 0; k < hiders[i][j].size(); k++) {
                    hiderMove(i, j, hiders[i][j][k]);
                }
            }
            else {
                for(int k = 0; k < hiders[i][j].size(); k++) {
                    next_hiders[i][j].push_back(hiders[i][j][k]);
                }
            }
        }
    }

    // 값 옮겨주기
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            hiders[i][j] = next_hiders[i][j];
        }
    }
}

int getSeekerDir() {
    int x = seeker_pos.first;
    int y = seeker_pos.second;

    int move_dir;
    if(forward_facing) move_dir = seeker_next_dir[x][y];
    else move_dir = seeker_rev_dir[x][y];

    return move_dir;
}

void checkerFacing() {
    if(seeker_pos == make_pair(0, 0) && forward_facing) forward_facing = false;
    if(seeker_pos == make_pair(N/2, N/2) && !forward_facing) forward_facing = true;
}
void seekerMove() {
    int x = seeker_pos.first;
    int y = seeker_pos.second;

    int dx[DIR_NUM] = {-1, 0, 1, 0};
    int dy[DIR_NUM] = {0, 1, 0, -1};

    int move_dir = getSeekerDir();

    seeker_pos = make_pair(x + dx[move_dir], y + dy[move_dir]);
    checkerFacing();
}

void getScore(int t) {

    int dx[DIR_NUM] = {-1, 0, 1, 0};
    int dy[DIR_NUM] = {0, 1, 0, -1};

    int x = seeker_pos.first;
    int y = seeker_pos.second;

    int move_dir = getSeekerDir();

    for(int dist = 0; dist < 3; dist++) {
        
        int nx = x + dist * dx[move_dir];
        int ny = y + dist * dy[move_dir];

        if(inRange(nx, ny) && !tree[nx][ny]) {
            ans += t * hiders[nx][ny].size();
            hiders[nx][ny].clear();
        }
    }
}

void simulate(int t) {
    hiderMoveAll();
    seekerMove();
    getScore(t);
}

int main() {
    cin >> N >> M >> h >> k;

    while(M--) {
        int x, y, d; cin >> x >> y >> d;
        hiders[x-1][y-1].push_back(d);
    }

    while(h--) {
        int x, y; cin >> x >> y;
        tree[x - 1][y - 1] = true;
    }

    seeker_pos = make_pair(N/2, N/2);

    initializeSeekerPath();

    for(int i = 1; i <= k; i++) simulate(i);

    cout << ans;
    return 0;
}
