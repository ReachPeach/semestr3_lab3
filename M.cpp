#include <iostream>
#include <vector>

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

int main() {
    freopen("common.in", "r", stdin);
    freopen("common.out", "w", stdout);
    ios::sync_with_stdio(NULL);
    cout.tie(NULL);
    cin.tie(NULL);
    string s, t;
    cin >> s >> t;
    string s_t = s + st + t + st + star;

    auto sufArr = sufArray(s_t);
    auto lcps = lcp(sufArr, s_t);

    int T = s.size();
    pair<int, int> res = {-1, 0};


    for (int i = 3; i < sufArr.size(); i++) {
        if (((sufArr[i - 1] - T) * (sufArr[i] - T)) < 0) {
            if (lcps[i] > res.first) {
                res = {lcps[i], min(sufArr[i - 1], sufArr[i])};
            }
            if (lcps[i] == res.first) {
                res.second = min(sufArr[i], min(res.second, sufArr[i - 1]));
            }
        }
    }

    for (int i = res.second; i < res.second + res.first; i++) {
        if (s_t[i] == st || s_t[i] == star) continue;
        cout << s_t[i];
    }
    return 0;
}