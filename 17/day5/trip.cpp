#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
using ll = long long;
using ii = pair<int, int>;

vector<ii> G[100001];
unordered_map<int, ll> A[100001], B[100001];
 
ll dfs(int u, int p) {
	sort(begin(G[u]), end(G[u]));
	ll ret = 0, sa = 1, tmp = 0, l = -1;
	++A[u][0], ++B[u][1e9+7];
	for (auto& v : G[u]) {
		if (v.s != p) {
			ret += dfs(v.s, u);
			ll ca = 0, cb = 0;
			for (auto& x : A[v.s]) {
				if (x.f < v.f) ca += x.s, A[u][v.f] += x.s;
			}
			for (auto& x : B[v.s]) {
				if (x.f > v.f) cb += x.s, B[u][v.f] += x.s;
			}
			ret += cb * sa, sa += ca;
			if (v.f != l) l = v.f, tmp = ca;
			else ret -= cb * tmp, tmp += ca;
		}
	}
	return ret + sa - 1;
}
 
int main() {
	int N;
	cin >> N;
	for (int i = 1, a, b, e; i < N; ++i) {
		cin >> a >> b >> e;
		G[a].emplace_back(e, b), G[b].emplace_back(e, a);
	}
	cout << dfs(1, 0) << '\n';
}