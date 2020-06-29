#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr ll INF = 1e12;
 
int dx[] = { 2, 1, -1, -2, -2, -1, 1, 2 };
int dy[] = { 1, 2, 2, 1, -1, -2, -2, -1 };
char A[101][101];
 
template<int V, class T = ll> class max_flow {
	struct edge {
		int t, rev;
		T cap, f;
	};
	vector<edge> adj[V];
	int dist[V];
	int ptr[V];
	bool bfs(int s, int t) {
		memset(dist, -1, sizeof dist);
		dist[s] = 0;
		queue<int> q({ s });
		while (!q.empty() && dist[t] == -1) {
			int n = q.front();
			q.pop();
			for (auto& e : adj[n]) {
				if (dist[e.t] == -1 && e.cap != e.f) {
					dist[e.t] = dist[n] + 1;
					q.push(e.t);
				}
			}
		}
		return dist[t] != -1;
	}
	T augment(int n, T amt, int t) {
		if (n == t) return amt;
		for (; ptr[n] < adj[n].size(); ptr[n]++) {
			edge& e = adj[n][ptr[n]];
			if (dist[e.t] == dist[n] + 1 && e.cap != e.f) {
				T flow = augment(e.t, min(amt, e.cap - e.f), t);
				if (flow != 0) {
					e.f += flow;
					adj[e.t][e.rev].f -= flow;
					return flow;
				}
			}
		}
		return 0;
	}
public:
	void add(int u, int v, T cap = 1, T rcap=0) {
		adj[u].push_back({ v, (int) adj[v].size(), cap, 0 });
		adj[v].push_back({ u, (int) adj[u].size() - 1, rcap, 0 });
	}
	T calc(int s, int t) {
		T flow = 0;
		while (bfs(s, t)) {
			memset(ptr, 0, sizeof ptr);
			while (T df = augment(s, INF, t)) flow += df;
		}
		return flow;
	}
	void clear() {
		for (int n = 0; n < V; n++) adj[n].clear();
	}
};
 
int main() {
	int R, C; 
	cin >> R >> C;
	int ans = R * C;
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) cin >> A[i][j];
	}
 
	max_flow<101*101> MF;
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			if (A[i][j] == '#') { --ans; continue; }
			if (i + j & 1) {
				MF.add(10000, i * C + j, (A[i][j] == 'C' ? INF : 1));
				for (int d = 0; d < 8; ++d) {
					int x = i + dx[d], y = j + dy[d];
					if (x < 0 || x >= R || y < 0 || y >= C || A[x][y] == '#') continue;
					MF.add(i * C + j, x * C + y, INF);
				}
			}
			else MF.add(i * C + j, 10001, (A[i][j] == 'C' ? INF : 1));
		}
	}
	cout << ans - MF.calc(10000, 10001) << '\n';
}