// (Works? HUH?)
#include <bits/stdc++.h>

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC optimize("avx2")
#pragma GCC optimize("Ofast")

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int m;
    cin >> m;
    int n, num;
    int sum = 0;
    double total = 0.0;
    int min1, min2;
    while(m){
        set <int> nums;
        cin >> n;
        
        for(int i = 0; i < n; ++i) {
            cin >> num;
            nums.insert(num);
        }
        
        for(int i = 0; i < n - 1; ++i) {
            sum += *nums.begin();
            nums.erase(*nums.begin());
            sum += *nums.begin();
            nums.erase(*nums.begin());
            nums.insert(sum);
            total += (sum * 5.0) / 100.0;
            sum = 0;
        }
        cout << total;
        total = 0;
        --m;
    }
    return 0;
}