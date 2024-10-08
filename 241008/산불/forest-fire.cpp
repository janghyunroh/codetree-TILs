#include <iostream>
using namespace std;


//1. O(n^3)의 풀이
/*
A[i]의 후보 0 ~ n에 대해 
0~i/2인 모든 k에 대해 
A[i] - A[i-k] != A[i-k] - A[i-2k]인지 확인
을 n번하여 A[n] 계산
n^3이지만 조기 탈출을 최대한 이용해서 아슬아슬하게 커팅
*/

/*
int main() {
    int n;
    int A[1000];

    cin >> n;
    A[0] = A[1] = 1;

    for(int i = 2; i <= n; i++) {
        for(int j = 1; j <= n; j++) {   // A[i]의 후보

            A[i] = j;
            
            //조건 확인
            bool flag = true;
            for(int k = 1; k <= (i/2); k++) {
                if(A[i] - A[i-k] == A[i - k] - A[i-2*k]) {
                    flag = false;
                    break;
                }
            }

            //조건이 만족하는 경우 -> 최소 만족값이라는 뜻이므로 반복문 탈출
            if(flag) {
                break;
            }
        }
    }

    cout << A[n];
    return 0;
}
*/

//2. O(n^2) 풀이
/*
A[i] - A[i-k] != A[i-k] - A[i-2k]를 만족하는 A[i]값에 대해 체크 배열 두기
*/
int main() {
    int n;
    int A[1000];

    cin >> n;
    A[0] = A[1] = 1;

    for(int i = 2; i <=n; i++) {

        //조건에 위배되는 숫자들 목록 배열
        bool impossible[1000] = {false}; // 인덱스 = 후보값. 모든 후보값을 돌며 조건 확인 해서 bool 배열 채우기
        for(int k = 1; k <= i / 2; k++) {
            // A[i] - A[i - k] == A[i - k] - A[i - 2 * k] 인 A[i]값을 인덱스로 가지는 check 배열 원소는 
            // 정답일 수 없으므로 true로!

            // -> A[i] = 2 * A[i - k] - A[i - 2 * k]
            impossible[2*A[i-k]-A[i-2*k]] = true;
        }

        // 배열을 채웠으니 다시 처음부터 linear search로 최소 후보(정답) 찾기
        for(int j = 1; j <= n; j++) {
            if(!impossible[j]) {
                A[i] = j;
                break;
            }
        }
    }

    cout << A[n];
    return 0;
}