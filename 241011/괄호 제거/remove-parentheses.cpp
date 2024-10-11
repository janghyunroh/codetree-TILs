/*

1. stack 이용해서 괄호 쌍 찾기


2. 완탐으로 모든 결과 제작
*/



#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

int check[201];

int main() {

    string formula;
    stack<int> st;
    vector<pair<int, int>> par_pairs;
    vector<string> ans;
    int cnt = 0;

    // 1. 괄호 쌍 정보 기록
    cin >> formula;
    for(int i = 0; i < formula.size(); i++) {
        if(formula[i] == '(') {
            st.push(i);
        }
        else if(formula[i] == ')') {
            int p = st.top();
            st.pop();

            // 현재 i값이 p와 짝꿍인덱스
            par_pairs.push_back({p, i});
            cnt++;
            check[p] = cnt;
            check[i] = cnt;
        }
    }

    // 2. 완탐으로 제작 가능한 문자열 생성
    for(int bit = 1; bit <= ( 1 << cnt ) - 1; bit++) {
        string tmp;

        for(int i = 0; i < formula.size(); i++) {
            if(formula[i] == '(' || formula[i] == ')') {

                if(1 << (check[i] - 1) & bit ) {
                    //exclude 
                    continue;
                }
                
            }
            tmp.push_back(formula[i]);
        }
        ans.push_back(tmp);
    }
    sort(ans.begin(), ans.end());
    for(auto str : ans) cout << str << '\n';
    return 0;
}