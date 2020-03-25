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
    }
}


int main() {
    ios::sync_with_stdio(NULL);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("search5.in", "r", stdin);
    freopen("search5.out", "w", stdout);
    int n;
    vector<string> strings;
    cin >> n;
    for (int i = 0; i < N; i++) {
        used[i] = 0;
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
    for (auto &ch : t) {
        while (trie[cur][ch - 'a'] == -1 && cur != root) {
            cur = suf_link[cur];
        }
        if (trie[cur][ch - 'a'] != -1)
            cur = trie[cur][ch - 'a'];
        used[cur]++;
    }
    dfs(root);
    for (int i = 0; i < n; i++) {
        printf("%d\n", used[num[i]]);
    }
    return 0;
}