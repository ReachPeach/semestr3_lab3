#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <algorithm>

using namespace std;
const int N = 1000 * 1000 + 10;
int trie[N][27];
int m = 1;
vector<int> rev[N];
int root = 0;
unordered_set<int> T;
pair<int, int> p[N];
int suf_link[N];
map<int, string> term;
pair<int, int> Time[N];
int num[N];
int used[N];

void insert(string &s, int n) {
    auto v = root;
    for (auto c : s) {
        if (trie[v][c - 'a'] == -1) {
            trie[v][c - 'a'] = m++;
            p[m - 1] = {v, c};
        }
        v = trie[v][c - 'a'];
    }
    num[n] = v;
    term[v] = s;
    T.insert(v);
}

void make_suffix_links() {
    suf_link[root] = root;
    queue<int> q;
    for (int i = 0; i < 27; i++) {
        if (trie[root][i] != -1) {
            for (int j = 0; j < 27; j++) if (trie[trie[root][i]][j] != -1) q.push(trie[trie[root][i]][j]);
            suf_link[trie[root][i]] = root;
            rev[root].push_back(trie[root][i]);
        }
    }

    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        auto pp = p[t];
        auto next = suf_link[pp.first];
        while (next != root && trie[next][pp.second - 'a'] == -1) {
            next = suf_link[next];
        }
        if (trie[next][pp.second - 'a'] == -1) {
            suf_link[t] = root;
            rev[root].push_back(t);
        } else {
            suf_link[t] = trie[next][pp.second - 'a'];
            rev[trie[next][pp.second - 'a']].push_back(t);
        }
        for (int i = 0; i < 27; i++) {
            if (trie[t][i] != -1)
                q.push(trie[t][i]);
        }
    }
}

void dfs(int v) {
    for (auto u : rev[v]) {
        dfs(u);
    }

    for (auto u : rev[v]) {
        used[v] += used[u];
        if (used[u] > 0) {
            Time[v].first = min(Time[v].first, Time[u].first);
            Time[v].second = max(Time[v].second, Time[u].second);
        }
    }
}

int main() {
    freopen("search6.in", "r", stdin);
    freopen("search6.out", "w", stdout);
    ios::sync_with_stdio(NULL);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    vector<string> strings;
    cin >> n;
    for (int i = 0; i < N; i++) {
        used[i] = 0;
        Time[i] = {INT32_MAX, INT32_MIN};
        for (int j = 0; j < 27; j++) trie[i][j] = -1;
    }
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        strings.emplace_back(s);
        insert(s, i);
    }
    make_suffix_links();

    string t;
    cin >> t;
    int cur = root;
    used[root] = 0;
    set<string> ans;
    int A = 0;
    for (auto &ch : t) {
        while (trie[cur][ch - 'a'] == -1 && cur != root) {
            cur = suf_link[cur];
        }
        if (trie[cur][ch - 'a'] != -1)
            cur = trie[cur][ch - 'a'];
        used[cur]++;
        if (used[cur] == 1) {
            Time[cur] = {A, A};
        } else if (used[cur] > 1) {
            Time[cur].second = A;
        }
        A++;
    }
    dfs(root);
    for (int i = 0; i < n; i++) {
        if (used[num[i]]) {
            cout << Time[num[i]].first - strings[i].length() + 1 << " " << Time[num[i]].second - strings[i].length() + 1
                 << "\n";
        } else {
            cout << "-1 -1\n";
        }
    }
    return 0;
}