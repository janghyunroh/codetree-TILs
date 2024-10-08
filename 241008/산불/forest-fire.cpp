#include <iostream>
using namespace std;


//1. O(n^3)의 풀이
/*
A[i]의 후보 0 ~ n에 대해 
0~i/2인 모든 k에 대해 
A[i] - A[i-k] != A[i-k] - A[i-2k]인지 확인
을 n번하여 A[n] 계산
*/

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