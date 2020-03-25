#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    string s;
    cin >> s;
    int N = s.size();
    vector<int> z(N, 0);
    z[0] = 0;
    for (int i = 1, l = 0, r = 0; i < N; i++) {
        if (i <= r)
            z[i] = min(z[i - l], r - i + 1);
        while ((i + z[i] < N) && (s[i + z[i]] == s[z[i]])) z[i]++;
        if (i + z[i] > r + 1) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    for (int i = 0; i< N; i++) {
        if ( i + z[i] == N && N%i == 0) {
            cout<<i;
            return 0;
        }
    }
    cout<<N;
    return 0;
}