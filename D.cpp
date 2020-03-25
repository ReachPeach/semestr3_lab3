#include <iostream>
#include <vector>

using namespace std;

int main() {
    string s, t, p;
    cin >> t >> s;
    p = t + '#' + s;
    vector<int> ans(p.size() + 1, 0);
    ans[0] = -1;
    for (int i = 1; i <= p.size(); i++) {
        int k = ans[i - 1];
        while (k >= 0) {
            if (p[k] == p[i - 1]) {
                ans[i] = k + 1;
                break;
            }
            k = ans[k];
        }
    }
    int tc = 0;
    for (int i = t.size() + 1; i < ans.size(); i++) if (ans[i] == t.size()) tc++;
    cout << tc << endl;
    for (int i = 1; i < ans.size(); i++) {
        if (ans[i] == t.size())
            cout << i - 2 * t.size() << " ";
    }
    return 0;
}