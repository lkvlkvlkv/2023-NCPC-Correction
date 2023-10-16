#include <bits/stdc++.h>
using namespace std;
#define endl "\n"

vector<int> now;
vector<vector<int>> dp[13];

void walk(int target, int i, vector<int> &permutation) {
    if (i == permutation.size()) {
        dp[target].push_back(now);
        return;
    }
    now.push_back(i + 1);
    for (auto &x : dp[permutation[i]]) {
        for (auto &y : x) {
            now.push_back(y);
        }
        now.push_back(0);
        walk(target, i + 1, permutation);
        for (auto &y : x) {
            now.pop_back();
        }
        now.pop_back();
    }
    now.pop_back();
}

void backtracking(int target, int n, vector<int> &permutation) {
    if (n == 0) {
        walk(target, 0, permutation);
        return;
    }
    for (int i = 1; i <= n; i++) {
        permutation.push_back(i);
        backtracking(target, n - i, permutation);
        permutation.pop_back();
    }
}

void dfs(int n) {
    vector<int> permutation;
    if (dp[n].size()) return;
    backtracking(n, n - 1, permutation);
    sort(dp[n].begin(), dp[n].end());
}

void solve() {
    int n;
    cin >> n;
    for (int i = 2; i <= n; i++) {
        dfs(i);
    }
    for (auto &x : dp[n]) {
        for (auto &y : x) {
            cout << y << " ";
        }
        cout << endl;
    }
}

int main() {
    cin.tie(NULL), ios::sync_with_stdio(false);
    int t;
    cin >> t;
    dp[0] = dp[1] = {{}};
    while (t--) {
        solve();
    }
    cout.flush();
    return 0;
}