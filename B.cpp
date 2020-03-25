#include <iostream>
#include <vector>

using namespace std;

int main() {
    string s;
    cin >> s;
    vector<int> ans(s.size() + 1, 0);
    ans[0] = -1;
    for (int i = 1; i <= s.size(); i++) {
        int k = ans[i - 1];
        while (k >= 0) {
            if (s[k] == s[i - 1]) {
                ans[i] = k + 1;
                break;
            }
            k = ans[k];
        }
    }
    for (int i = 1; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }
    return 0;
}