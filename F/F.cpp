#include <bits/stdc++.h>
using namespace std;
#define endl "\n"

int n, m;

array<int, 2> convert(int i, int j) {
    if (i < n && j < m) {
        return {i - j, j};
    }
    if (i >= n) {
        return {n - 1 - j, j + i - n + 1};
    }
}

void solve() {
    cin >> n >> m;
    vector<vector<int>> matrix(n, vector<int>(m));
    vector<vector<vector<int>>> dp(n + m - 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> matrix[i][j];
            if (matrix[i][j] == -1)
                matrix[i][j] = -1e9;
        }
    }
    int size = 1;
    for (int i = 0; i < n + m - 1; i++) {
        dp[i] = vector<vector<int>>(size, vector<int>(size, -1e9));
        if (i < n - 1 && i < m - 1) {
            size++;
        }
        else if (i >= n - 1 && i >= m - 1) {
            size--;
        }
    }
    dp[0][0][0] = matrix[0][0];
    for (int i = 1; i < n + m - 1; i++) {
        for (int j = 0; j < dp[i].size(); j++) {
            array<int, 2> coord1 = convert(i, j);
            for (int k = 0; k < dp[i].size(); k++) {
                array<int, 2> coord2 = convert(i, k);
                int sum = 0;
                if (j == k)
                    sum = matrix[coord1[0]][coord1[1]];
                else
                    sum = matrix[coord1[0]][coord1[1]] + matrix[coord2[0]][coord2[1]];
                int diff = i >= n ? 1 : -1;
                if (j < dp[i - 1].size() && k < dp[i - 1].size()) {
                    dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j][k] + sum);
                }
                if (j + diff >= 0 && k + diff >= 0 && j + diff < dp[i - 1].size() && k + diff < dp[i - 1].size()) {
                    dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j + diff][k + diff] + sum);
                }
                if (j + diff >= 0 && k < dp[i - 1].size() && j + diff < dp[i - 1].size()) {
                    dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j + diff][k] + sum);
                }
                if (j < dp[i - 1].size() && k + diff >= 0 && k + diff < dp[i - 1].size()) {
                    dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j][k + diff] + sum);
                }
            }
        }
    }
    if (dp[n + m - 2][0][0] < 0) {
        cout << "-1" << endl;
    }
    else {
        cout << dp[n + m - 2][0][0] << endl;
    }
    return;
}

int main() {
    cin.tie(NULL), ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    cout.flush();
    return 0;
}