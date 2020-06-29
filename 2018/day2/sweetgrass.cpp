#include <bits/stdc++.h>
using namespace std;

int N, idx[100001];
bitset<100001> vis, ans;
vector<int> path;
unordered_set<int> G[100001];

void solve() {
	vis.reset();
	for (int i = 0; i < path.size() - 1; ++i) {
		G[path[i]].erase(path[i + 1]);
	}
	memset(idx, -1, sizeof idx);
	for (int i = 0; i < path.size(); ++i) idx[path[i]] = i;
	int m = 0;
	ans.set();
	for (int i = 0; i < path.size() - 1; ++i) {
		m = max(i + 1, m);
		queue<int> q;
		q.push(path[i]);
		while (q.size()) {
			int u = q.front();
			q.pop();
			if (vis[u]) continue;
			vis[u] = 1;
			if (u != path[i] && idx[u] != -1) {
				for (int j = m; j < idx[u]; ++j)
					ans[j] = 0;
				m = max(idx[u], m);
				continue;
			}			
			for (auto& v : G[u]) {
				if (!vis[v]) q.push(v);
			}
		}
	}
	vector<int> out;
	for (int i = 1; i < path.size() - 1; ++i)
		if (ans[i]) out.push_back(path[i]);
	sort(begin(out), end(out));
	cout << out.size() << '\n';
	for (auto& x : out) cout << x << '\n';
}

void dfs(int u) {
	vis[u] = 1;
	path.push_back(u);
	if (u == N) {
		solve();
		exit(0);
	}	
	for (auto& v : G[u]) {
		if (!vis[v]) dfs(v);
	}
	path.pop_back();
}

int main() {
	int M; cin >> N >> M;
	while (M--) {
		int a, b; cin >> a >> b;
		G[a].insert(b);
	}
	dfs(1);
}