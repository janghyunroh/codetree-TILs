/*
각 단계 별로, 
1. 각 몬스터까지 최단 거리 계산(BFS)
2. 레벨 -> 거리 -> 우선순위를 순서대로 고려하여 타겟 좌표 선출
3. 1) 해당 좌표로 로봇을 옮기기, 2) 거리만큼 시간 늘리기, 3) 로봇 레벨 늘리기 

주의사항)

1. 몬스터 별 차이
로봇보다 레벨이 낮은 경우 - 처치 가능
로봇보다 레벨이 같은 경우 - 처치 불가능, 지나갈 순 있음
로봇보다 레벨이 높은 경우 - 지나갈 수도 없음

2. 레벨 업 조건
레벨은 현재 레벨과 같은 수의 로봇을 잡아야 오름!!
-> 경험치 통 변수 필요!
*/
#include <iostream>
#include <queue>

# define INF (~0U>>2)
# define NO_PAIR make_pair(-1, -1)

using namespace std;

//입력되는 변수
int N;
int board[20][20];

//로봇에 대한 변수
int lv = 2;
int experience = 0; // 잡은 몬스터 수(레벨과 같아지는 경우 0이 되고 레벨 1 오름)
pair<int, int> robot_pos;
int t = 0;

//기타 계산용 변수
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
bool visited[20][20];
int dist[20][20];       // BFS 수행하고 나면 업데이트되는 거리 행렬. 이 행렬을 스캔하여 도달 가능 여부 판별. 

//debugging
void displayBoard() {
    cout << "===보드===" << '\n';
    for(int i =0; i < N; i++) {
        for(int j =0; j < N; j++) {
            cout << board[i][j] << ' ';
        }   
        cout << '\n';
    }
}

void displayDist() {
    cout << "===거리===" << '\n';
    for(int i =0; i < N; i++) {
        for(int j =0; j < N; j++) {
            cout << dist[i][j] << ' ';
        }   
        cout << '\n';
    }
}

void displayVisited() {
    cout << "===방문===" << '\n';
    for(int i =0; i < N; i++) {
        for(int j =0; j < N; j++) {
            cout << (int)visited[i][j] << ' ';
        }   
        cout << '\n';
    }
}


// 
void initVisited() {
    for(int i =0; i < N; i++) {
        for(int j =0; j < N; j++) {
            visited[i][j] = false;
        }   
    }
}

// -1로 초기화: unreachable
void initDist() {
    for(int i =0; i < N; i++) {
        for(int j =0; j < N; j++) {
            dist[i][j] = -1;
        }   
    }
}

// 
void BFS(int x, int y) {

    //시작 노드
    queue<pair<int, int>> q;
    q.push(make_pair(x, y));
    visited[x][y] = true;
    dist[x][y] = 0;

    //BFS 돌면서 dist 행렬 갱신
    while(q.size()) {
        pair<int, int> cur_node = q.front();
        int cx = cur_node.first;
        int cy = cur_node.second;
        q.pop();

        for(int i = 0; i < 4; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if(nx >= 0 && nx < N && ny >= 0 && ny < N && !visited[nx][ny] && board[nx][ny] <= lv) { // 레벨이 같아도 지나갈 수는 있음!

                q.push(make_pair(nx, ny));
                visited[nx][ny] = true;
                dist[nx][ny] =  dist[cx][cy] + 1;
            }
        }
    }
}

bool moveRobot() {

    // 초기화
    initVisited();
    initDist();

    int x = robot_pos.first;
    int y = robot_pos.second;
    dist[x][y] = 0;

    //
    BFS(x, y);

    //dist를 갱신했으니 전체를 훑으며 후보 탐색
    int min_dist = INF;
    pair<int, int> dest = NO_PAIR;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {

            //몬스터 중에 레벨이 낮은 것 중 거리가 최소이고 인덱스가 작은 것.
            // 1. 몬스터여야 함.
            // 2. 레벨이 나보다 낮아야 함

            // 걸러야 할 경우
            // 1. 도달 불가한 경우
            // 2. 로봇 자신인 경우
            // 3. 빈 칸인 경우
            // 4. 레벨이 낮지 않은 경우
            if(!visited[i][j] || board[i][j] == 9 || board[i][j] == 0 || board[i][j] >= lv || dist[i][j] == -1) {
                continue;
            }

            pair<int, int> new_pos = make_pair(i, j);
            if(dist[i][j] < min_dist) {
                dest = new_pos; // 어차피 i랑 j 다 0부터 시작하므로 인덱스 번호 조건은 자연스레 만족.
                min_dist = dist[i][j];
            }
        }
    }

    //위치를 찾은 경우
    if(dest != NO_PAIR) {

        //로봇 위치 갱신
        //원래 있던 곳 지우기
        board[x][y] = 0;


        robot_pos = dest;
        dist[robot_pos.first][robot_pos.second] = 0;
        board[robot_pos.first][robot_pos.second] = 9;

        //시간 갱신
        t += min_dist;

        //경험치 갱신
        experience++;
        if(experience == lv) {
            lv++;
            experience = 0;
        }

        // 턴 종료

        //debugging
        //displayBoard();
        //displayDist();
        //displayVisited();
        //cout << dest.first << ' ' << dest.second << '\n';
        return true;
    }
    //위치가 없는 경우
    else {
        return false;
    }
}


int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    //input
    cin >> N;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            int tmp; cin >> tmp; board[i][j] = tmp;
            if(tmp == 9) robot_pos = make_pair(i, j);
        }
    }

    //simulate
    while(moveRobot()) {
        ;;
    }

    //output
    cout << t << '\n';
    return 0;
}