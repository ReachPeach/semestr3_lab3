#include <iostream>
#include <vector>

const int M = 1e9 + 7;

using namespace std;
vector<long long> x, p;

int main() {
    int n;
    string s;
    cin >> s >> n;

    auto N = s.size();

    x.assign(N + 1, 0);
    p.assign(N + 1, 0);
    x[0] = 37;
    p[0] = 0;

    for (int i = 1; i <= N; i++) {
        x[i] = (x[0] * x[i - 1]) % M;
    }
    for (int i = 1; i <= N; i++) {
        p[i] = ((p[i - 1] * x[0]) % M + s[i - 1] - 'a' + 1) % M;
    }
    for (int i = 0; i < n; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        long long P1 = (p[b] - (p[a - 1] * x[b - a]) % M) % M;
        long long P2 = (p[d] - (p[c - 1] * x[d - c]) % M) % M;
        if (P1 < 0) P1 += M;
        if (P2 < 0) P2 += M;
        if (P1 == P2) {
            if (s.substr(a, b - a) == s.substr(c, d - c)) {
                cout << "Yes\n";
                continue;
            }
        }
        cout << "No\n";
    }
    return 0;
}