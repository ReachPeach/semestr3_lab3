#include <utility>

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;
const char st = 'a' - 1;
const char star = st - 1;

vector<int> sufArray(const string &s) {
    auto n = s.size();
    vector<int> p(n), count(30, 0), c(n);
    for (int i = 0; i < n; i++) count[s[i] - star]++;
    for (int i = 1; i < 30; i++) count[i] += count[i - 1];
    for (int i = 0; i < n; i++) {
        p[count[s[i] - star] - 1] = i;
        count[s[i] - star]--;
    }

    c[p[0]] = 0;
    int cls = 0;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i - 1]]) cls++;
        c[p[i]] = cls;
    }

    vector<int> new_c(n), p_sec(n);
    for (int k = 0; (1 << k) < n; k++) {
        for (int i = 0; i < n; i++) {
            p_sec[i] = p[i] - (1 << k);
            if (p_sec[i] < 0) p_sec[i] += n;
        }
        count.assign(cls + 1, 0);
        for (int i = 0; i < n; i++) count[c[p_sec[i]]]++;
        for (int i = 1; i <= cls; i++) count[i] += count[i - 1];
        for (int i = n - 1; i >= 0; i--) {
            p[count[c[p_sec[i]]] - 1] = p_sec[i];
            count[c[p_sec[i]]]--;
        }
        new_c[p[0]] = 0;
        cls = 0;
        for (int i = 1; i < n; i++) {
            int mid1 = (p[i] + (1 << k)) % n;
            int mid2 = (p[i - 1] + (1 << k)) % n;
            if (c[p[i]] != c[p[i - 1]] || c[mid1] != c[mid2])
                ++cls;
            new_c[p[i]] = cls;
        }
        c.clear();
        c.assign(new_c.begin(), new_c.end());
    }
    return p;
}

int common_pref_length(const string &s, const int &n, int shift, int i, int j) {
    i = min(shift + i, n), j = min(shift + j, n);
    for (; i < n && j < n && s[i] == s[j]; i++, j++, shift++);
    return shift;
}

vector<int> lcp(const vector<int> &sufArray, const string &s) {
    int n = s.size();
    vector<int> pos(n);
    vector<int> lcps(n);
    for (int i = 0; i < n; i++) pos[sufArray[i]] = i;
    bool done = false;
    for (int i = 0; i < n; i++) {
        if (pos[i] == 0) continue;
        if (!done) {
            lcps[pos[i]] = common_pref_length(s, n, 0, sufArray[pos[i]], sufArray[pos[i] - 1]);
            done = true;
        } else {
            lcps[pos[i]] = common_pref_length(s, n, max(lcps[pos[i - 1]] - 1, 0), sufArray[pos[i]],
                                              sufArray[pos[i] - 1]);
        }
    }
    return lcps;
}

struct keys {
    vector<int> k;

    keys(vector<int> k) : k(std::move(k)) {}

    keys() = default;

    int from(int a) {
        for (int i = 0; i < k.size(); i++) {
            if (a < k[i]) return 1 << i;
        }
    }


};

int ok(const vector<int> &k, int a) {
    for (int i = 0; i < k.size(); i++) {
        if (a < k[i]) return 1 << i;
    }
}

int main() {
    ios::sync_with_stdio(NULL);
    cout.tie(NULL);
    cin.tie(NULL);
    int k;
    cin >> k;
    string s = "";
    vector<string> ss(k);
    for (int i = 0; i < k; i++) {
        cin >> ss[i];
    }
    sort(ss.begin(), ss.end());
    vector<int> Ts;
    for (const auto &sss : ss) {
        s += sss + st;
        Ts.push_back(s.size() - 1);
    }
    s += star;

    auto sufArr = sufArray(s);
    auto lcps = lcp(sufArr, s);

    pair<int, int> res = {-1, 0};
    auto help = keys(Ts);
    int N = s.size();

    vector<int> pos;
    sort(pos.begin(), pos.end());
    for (int i = k + 1; i < N; i++) {
        if (sufArr[i] < Ts[0]) pos.push_back(i);
    }
    lcps.push_back(-1);
    lcps[k] = -1;
    int ful = (1 << k) - 1;
    for (auto pos_s : pos) {
        int cur = 1;
        int l = pos_s - 1, r = pos_s + 1;
        int ans = INT32_MAX;
        while (cur != ful) {
            if (lcps[l + 1] > lcps[r]) {
                ans = min(lcps[l + 1], ans);
                cur = cur | ok(Ts, sufArr[l]);
                l--;
            } else {
                ans = min(ans, lcps[r]);
                cur = cur | ok(Ts, sufArr[r]);
                r++;
            }
        }
        if (res.first < ans) {
            res = {ans, pos_s};
        }
    }

    for (int i = sufArr[res.second]; i < sufArr[res.second] + res.first; i++) {
        if (s[i] == st || s[i] == star) continue;
        cout << s[i];
    }

    return 0;
}