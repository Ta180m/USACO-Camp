#include <bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define eb emplace_back
using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vii = vector<ii>;

vi G[100001];

bool test(int x, vector<int> & ch) {
	ll tmp = 1;
	for (auto& c : ch) {
		if (c > x || !tmp) return 0;
		tmp = min(tmp * (1 << min(x - c, 20)) - 1, 100001ll), x = c;	
	}
	return tmp;
}

int dfs(int u, int p) {
	vi ch;
	for (auto& v : G[u]) if (v != p) ch.push_back(dfs(v, u));
	if (ch.empty()) return 0;
	sort(begin(ch), end(ch), greater<int>());
	int l = ch[0] + 1, r = 100001;
	while (l < r) {
		int m = (l + r) / 2;
		test(m, ch) ? r = m : l = m + 1;
	}
	return l;
}

int main() {
	int N; cin >> N;
	for (int i = 1; i < N; ++i) {
		int a, b; cin >> a >> b;
		G[a].push_back(b), G[b].push_back(a);
	}
	cout << dfs(1, 0) + N - 1 << '\n';	
}