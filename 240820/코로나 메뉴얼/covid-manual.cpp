#include <iostream>
using namespace std;

int main() {
    char sym[3];
    int tmp[3];
    int Acnt = 0;
    for(int i = 0; i < 3; i++) {
        cin >> sym[i] >> tmp[i];
        if(sym[i] == 'Y' && tmp[i] >= 37) Acnt++;
    }
    if(Acnt >= 2) cout << 'E';
    else cout << 'N';
    return 0;
}