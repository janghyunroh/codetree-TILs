/*

열/행 우선순위 조심!!!
열이 행보다 우선순위가 높은 경우 다중 반복에서 인덱스 순서 바뀜!!!!

"벽면의 숫자는 충분히 많이 적혀 있어 생겨날 조각 수가 부족한 겨우는 없다"
--> 벽면 큐가 빌 걱정 X!
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int K, M;

class Board {

public:

    int grid[5][5];

    // 생성자
    Board() {
        for(int i = 0; i < 5; i++) {
            for(int j = 0; j < 5; j++) {
                grid[i][j] = 0;
            }
        }
    }

    // 회전한 보드 반환 함수
    Board* rotate(int sx, int sy, int angle) {
        Board * newBoard = new Board();

        //우선 복사
        for(int i = 0; i < 5; i++) {
            for(int j = 0; j < 5; j++) {
                newBoard->grid[i][j] = this->grid[i][j];
            }
        }

        //돌리기
        for(int i = 0; i < angle; i++) {
            
            int partGrid[3][3];
            // 임시 배열에 3×3 부분 보드 복사
            for (int j = 0; j < 3; j++)
                for (int k = 0; k < 3; k++)
                    partGrid[j][k] = newBoard->grid[sx + j][sy + k];

            // 
            for(int j = 0; j < 3; j++) {
                for(int k = 0 ; k < 3; k++) {
                    newBoard->grid[sx + k][sy + 2 - j] = partGrid[j][k];
                }
            }
        }
        return newBoard;
    }

    //유물 점수 계산 및 획득한 유물 제거
    int calScore() {

        int score = 0; 
        bool visited[5][5];

        int dx[4] = {0, 0, 1, -1};
        int dy[4] = {1, -1, 0, 0};

        for(int i = 0; i < 5; i++) {
            for(int j = 0; j < 5; j++) {
                visited[i][j] = false;
            }
        }

        for(int i = 0; i < 5; i++) {
            for(int j = 0; j < 5; j++) {
                
                //각 요소 별 BFS 시작
                queue<pair<int, int>> q;
                queue<pair<int, int>> trace; // 사라진 유물 좌표 기록용

                //첫 시작 칸 큐에 넣고 시작
                q.push(make_pair(i, j));
                trace.push(make_pair(i, j));
                visited[i][j] = true;

                while(q.size()) {
                    pair<int, int> cur_node = q.front();
                    q.pop();

                    for(int k = 0; k < 4; k++) {
                        int nx = cur_node.first + dx[k];
                        int ny = cur_node.second + dy[k];

                        if(inRange(nx, ny) && !visited[nx][ny] && grid[nx][ny] == grid[cur_node.first][cur_node.second]) {
                            q.push(make_pair(nx, ny));
                            trace.push(make_pair(nx, ny));
                            visited[nx][ny] = true;
                        }
                    }
                }

                //BFS를 마친 뒤
                if(trace.size() >= 3) {
                    score += trace.size();
                    while(trace.size()) {
                        pair<int, int> tmp = trace.front(); trace.pop();
                        this->grid[tmp.first][tmp.second] = 0;
                    }
                }
            }
        }
        return score;
    }

    //빈 공간 있는 보드에 유물 조각 삽입
    void Fill(queue<int>*q) {
        for(int j = 0; j < 5; j++) {    //1. 열 번호가 작은 순서
           for(int i = 4; i >= 0; i--) { // 2. 행 번호가 큰 순서
                if(grid[i][j] == 0) {
                    grid[i][j] = q->front();
                    q->pop();
                }
            }
        }
    }

private:

    bool inRange(int x, int y) {
        return (0 <= x && x < 5 && 0 <= y && y < 5);
    }

};



int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    Board *board = new Board();
    queue<int> pieces;

    //input
    cin >> K >> M;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            cin >> board->grid[i][j];
        }   
    }
    for(int i = 0; i < M; i++) {
        int tmp; cin >> tmp; pieces.push(tmp); 
    }


    while(K--) {

        // 1. 회전으로 최대 점수 얻을 수 있는 경우 찾기
        int maxScore = 0;
        Board* maxBoard = NULL;
        for(int angle = 0; angle < 3; angle++) {     // 각도 -> 열 -> 행 순서!!!!
            for(int sy = 0; sy < 3; sy++) {
                for(int sx = 0; sx < 3; sx++) {
                    Board *rotated = board->rotate(sx, sy, angle);
                    int score = rotated->calScore();

                    if(maxScore < score) {
                        maxScore = score;
                        maxBoard = rotated;
                    }
                }
            }
        }


        if(!maxBoard) break;

        // 보드 갱신
        board = maxBoard;

        //유물 연쇄 획득 - 채우고 획득하기 반복
        while(true) {
            board->Fill(&pieces);
            int newScore = board->calScore(); 
            if(newScore == 0) break;
            maxScore += newScore;
        }
        cout << maxScore << ' ';
    }

    return 0;
}