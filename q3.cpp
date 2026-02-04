#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ll n;
    
    cin >> n;

    ll i = 60; 

    while (true) { 
        ll mid = 1LL << (i - 1);

        if (n == mid) {
            char result = 'A' + ((i - 1) % 26);
            cout << result << endl;
            break;
        } else if (n > mid) {
            n -= mid;
        }
        i--;
    }
    //Time Complexity: O(log n) 
    //เพราะloopแต่ละรอบ n ลดลงทีละครึ่ง(ในกรณีที่ n อยู่ขวาสุด)
}