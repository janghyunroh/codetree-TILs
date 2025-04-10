#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int N, M, K;
int turn;

// 레이저 공격용 - 우, 하, 좌, 상 순서
int dx1[4] = {0, 1, 0, -1};
int dy1[4] = {1, 0, -1, 0};
bool visited[10][10];
pair<int, int> path[10][10];

//포탄 공격용 - 주위 9칸 
int dx2[9] = {0, 0, 0, -1, -1, -1, 1, 1, 1};
int dy2[9] = {0, -1, 1, 0, -1, 1, 0, -1, 1};

int powers[10][10];
int attackTime[10][10];
bool isInvolved[10][10];

struct Turret {
    int x;
    int y;
    int power;
    int recentAttackTime;
};

vector<Turret> liveTurrets;

// 턴 시작마다 수행하는 초기화 함수
void init() {

    //턴 증가
    turn++;

    //공격 포함 여부 초기화
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            isInvolved[i][j] = false;
            visited[i][j] = false;
        }
    }

    //살아있는 터렛 다시 세기
    liveTurrets.clear();
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if(powers[i][j]) {
                Turret new_turret;
                new_turret.x = i; 
                new_turret.y = j;
                new_turret.recentAttackTime = attackTime[i][j];
                new_turret.power = powers[i][j];

                liveTurrets.push_back(new_turret);
            }
        }
    }
}

bool cmp(Turret a, Turret b) {
    if(a.power != b.power) return a.power < b.power;
    if(a.recentAttackTime != b.recentAttackTime) return a.recentAttackTime > b.recentAttackTime;
    if(a.x + a.y != b.x + b.y) return a.x + a.y > b.x + b.y;
    return a.y > b.y; 
}

bool laserAttack(Turret attacker, Turret defender) {
    int att_x = attacker.x;
    int att_y = attacker.y;

    int def_x = defender.x;
    int def_y = defender.y;

    int p = attacker.power;
    
    //레이저 공격 경로 탐색을 위한 BFS
    bool reachable = false;
    queue<pair<int, int>> q;
    visited[att_x][att_y] = true;
    q.push(make_pair(att_x, att_y));
    while(q.size()) {
        pair<int, int> cur_node = q.front();
        int x = cur_node.first;
        int y = cur_node.second;
        q.pop();

        if(x == def_x && y == def_y) {
            reachable = true;
            break;
        }

        for(int i = 0; i < 4; i++) {
            int nx = (x + dx1[i] + N) % N;
            int ny = (y + dy1[i] + M) % M;

            if(!visited[nx][ny] && powers[nx][ny] != 0) {
                visited[nx][ny] = true;
                path[nx][ny] = make_pair(x, y);
                q.push(make_pair(nx, ny));

            }
        }
    }

    // 도달 가능한 경우 공격 적용
    if(reachable) {

        powers[def_x][def_y] -= p;
        if(powers[def_x][def_y] < 0) powers[def_x][def_y] = 0;
        isInvolved[def_x][def_y] = true;

        int cx = path[def_x][def_y].first;
        int cy = path[def_x][def_y].second;

        while(!(cx == att_x && cy == att_y)) {
            powers[cx][cy] -= (p / 2);
            if(powers[cx][cy] < 0) powers[cx][cy] = 0;
            isInvolved[cx][cy] = true;

            int next_cx = path[cx][cy].first;
            int next_cy = path[cx][cy].second;

            cx = next_cx;
            cy = next_cy;
        }
    }

    //레이저 공격 성공 여부 반환
    return reachable;

}

void cannonAttack(Turret attacker, Turret defender) {

    int att_x = attacker.x;
    int att_y = attacker.y;

    int def_x = defender.x;
    int def_y = defender.y;

    int p = attacker.power;

    //
    for(int i = 0; i < 9; i++) {
        int nx = (def_x + dx2[i] + N) % N;
        int ny = (def_y + dy2[i] + M) % M;

        if(nx == att_x && ny == att_y) continue;
        if(nx == def_x && ny == def_y) {
            powers[nx][ny] -= p;
            if(powers[nx][ny] < 0) powers[nx][ny] = 0;
            isInvolved[nx][ny] = true;
        }
        else {
            powers[nx][ny] -= p/2;
            if(powers[nx][ny] < 0) powers[nx][ny] = 0;
            isInvolved[nx][ny] = true;
        }

    }
}

// 포탑 정비
void healthGain() {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if(!isInvolved[i][j] && powers[i][j] !=  0) powers[i][j]++;
        }
    }
}

int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> M >> K;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            cin >> powers[i][j];
        }
    }

    while(K--) {
        
        //0. 필수 초기화
        init();

        //
        if(liveTurrets.size() <= 1) break;

        //1. 공격자 선정 및 강화
        sort(liveTurrets.begin(), liveTurrets.end(), cmp);

        Turret attacker = liveTurrets[0];
        int x = attacker.x;
        int y = attacker.y;

        //공격 강화
        powers[x][y] += (N + M);
        attackTime[x][y] = turn;
        attacker.power = powers[x][y];
        attacker.recentAttackTime = attackTime[x][y];
        isInvolved[x][y] = true;
        liveTurrets[0] = attacker;

        //2. 공격 대상 선정 - 
        Turret defender = liveTurrets[liveTurrets.size() - 1];

        //3. 레이저 공격 or 포탄 공격 
        if(!laserAttack(attacker, defender)) cannonAttack(attacker, defender);

        //4. 포탑 정비
        healthGain();
    }

    // 모든 턴이 종료된 경우
    int ans = 0;
    for(int i =0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            ans = max(ans, powers[i][j]);
        }
    }
    cout << ans;
    return 0;
}