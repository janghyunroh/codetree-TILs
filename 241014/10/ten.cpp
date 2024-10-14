/*
완탐: 한 좌표O(NM)를 왼쪽 구석으로 하는 모든 직사각형O(NM)의 넓이(O(NM)) 평가 -> O(N^3 x M^3)

prefix sum : 누적합 배열
배열의 일부 시퀀스(a ~ b)의 합을 구하기 -> S[b] - S[a - 1]

2차원 배열에는 어떻게 적용해야 할까?


S[i][j] = a[1][1] ~ a[i][j] 까지의 합

****
*###
*###
*###

왼쪽 위 좌표: (i, j), 오른쪽 아래 좌표: (x, y)
넓이  = S[x][y] - S[x][j-1] - S[i - 1][j] + S[i-1][j-1]
--> 정해진 사각형의 넓이 계산: O(1)
-> O(N^2 x M^2)

넓이가 10을 넘어가는 경우 그 부분을 포함된 부분은 계산해볼 필요가 없음!
즉, 한 원소값이 최소 1이므로 최대 10칸까지만 보면 됨!
-> O(N^2 x M^2) -> O(NM x 10 x 10)
*/


#include <iostream>
using namespace std;

int m, n;
int a[301][301];
int s[301][301];

int main() {

    // 
    cin >> m >> n;
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> a[i][j]; 
        }
    }

    // prefix sum 구하기
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1] + a[i][j];
        }
    }

    int ans = 0;
    for(int sy = 1; sy <= m; sy++) { //O(M)
        for(int sx = 1; sx <= n; sx++) { //O(N)
            for(int ey = sy; ey <= min(m, sy + 10); ey++) { // O(10)
                for(int ex = sx; ex <= min(n, sx + 10); ex++) { // O(10)
                    int area = s[ey][ex] - s[sy - 1][ex] - s[ey][sx - 1] + s[sy - 1][sx - 1];
                    if(area == 10) ans += 1;
                }
            }
        }
    }

    cout << ans;
    return 0;
}