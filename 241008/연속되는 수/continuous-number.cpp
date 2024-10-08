#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*

실제 삭제 연산을 벡터나 배열에 쓰면 시간 복잡도 개판

그렇다고 LinkedList 쓸 수도 없고...

K와 같은 원소를 제외하고 새로운 벡터에 추가하여 선형 탐색하여 횟수 세기!


*/

int N;
vector<int> arr;
int ans = 0;
int main() {

    //입력 
    cin >> N;
    for(int i = 0; i < N; i++) {
        int n; cin >> n;
        arr.push_back(n);
    }    

    for(int i = 0; i < N; i++) {

        //제거
        vector<int> exc;
        for(auto item : arr) {
            if(item != arr[i]) exc.push_back(item);
        }

        int last = -1;
        
        int cnt = 0;
        for(auto item : exc) {
            if(item == last) {
                cnt++;
            }
            else {
                last = item;
                cnt = 1;
            }
            ans = max(cnt, ans);
        }
    }

    cout << ans;

    return 0;
}