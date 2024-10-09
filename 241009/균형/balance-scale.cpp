#include <iostream>
#include <vector>
using namespace std;

//
int count_additional_weights(int n) {
    //greedy
    int cnt = 0;
    while(n > 0) {
        if(n >= 100) {
            n -= 100;
            cnt += 1;
        }
        else if(n >= 50) {
            n -= 50;
            cnt += 1;
        }
        else if(n >= 20) {
            n -= 20;
            cnt += 1;
        }
        else if(n >= 10) {
            n -= 10;
            cnt += 1;
        }
        else if(n >= 5) {
            n -= 5;
            cnt += 1;
        }
        else if(n >= 2) {
            n -= 2;
            cnt += 1;
        }
        else {
            n -= 1;
            cnt += 1;
        }
    }
    return cnt;
}

int n;
vector<int> arr;
int main() {
    cin >> n;
    for(int i =0; i < n; i++) {
        int x; cin >> x; 
        arr.push_back(x);
    }

    // 있는 무게추 올리기
    int left = arr[0];
    int right = arr[1];
    for(int i = 2; i < n; i++) {
        if(left == right) left += arr[i];
        else if(left < right) left += arr[i];
        else right += arr[i];
    }

    //양쪽 차이 구하기
    int sub = (left > right ? left - right : right - left);
    cout << count_additional_weights(sub);


    return 0;
}