/*
합이 21이기만 하면 되는 주사위

주사위마다 이길 확률이 다름

두 주사위가 주어졌을 때 1이 2를 이길 확률

36가지 경우 중 1 > 2 인 경우 계산(완전탐색)

확률은 기약분수로

*/




#include <iostream>
using namespace std;

// 최대공약수(GCD) 구하는 함수
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int arr1[6], arr2[6];

int main() {
    for(int i = 0; i < 6; i++) cin >> arr1[i];
    for(int i = 0; i < 6; i++) cin >> arr2[i];
    int cnt = 0;
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 6; j++) {
            if(arr1[i] > arr2[j]) cnt++;
        }
    }

    //cnt / 36 약분해서 기약분수 구하기
    int GCD = gcd(cnt, 36);
    cout << (cnt/GCD) << '/' << (36/GCD);
    return 0;
}