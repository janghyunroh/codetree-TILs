#include <iostream>

using namespace std;

int score;
int main() {
    cin >> score;
    if(score >= 80) cout << "pass";
    else cout << 80 - score << " more score";
    return 0; 
}