#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN = 100001;

int c[MAXN];
vector<int> G[MAXN];

int cnt, scc_num, scc[MAXN], in[MAXN], low[MAXN];
stack<int> s;
bitset<MAXN> ins;

void tarjan(int u) {
	low[u] = in[u] = cnt++;
	s.push(u);
	ins[u] = 1;
	for (int v : G[u]) {
		if (in[v] == -1) tarjan(v), low[u] = min(low[u], low[v]);
		else if (ins[v]) low[u] = min(low[u], in[v]);
	}
	if (low[u] == in[u]) {
		++scc_num;
		while (1) {
			int x = s.top(); s.pop();
			scc[x] = scc_num, ins[x] = 0;
			if (x == u) break;
		}
	}
}

int main() {
	int N, M, K; cin >> N >> M >> K;
	while (M--) {
		int a, b; cin >> a >> b;
		G[a].push_back(b);
	}

	memset(scc, -1, sizeof scc), memset(in, -1, sizeof in);
	for (int u = 1; u <= N; ++u) if (scc[u] == -1) tarjan(u);

	if (scc_num < K) cout << "impossible\n";
	else for (int u = 1; u <= N; ++u) cout << min(scc[u], K) << '\n';	
}