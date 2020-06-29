#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
using ii = pair<int, int>;
template<typename T> class fenwick_tree {
private: vector<T> FT;
public:
	fenwick_tree(int N) { FT.assign(N + 1, 0); }
	void update(int x, T val) { if (x > 0) for (; x < FT.size(); x += x & -x) FT[x] += val; }
	T query(int x) { T ret = 0; if (x > 0) for (; x > 0; x -= x & -x) ret += FT[x]; return ret; }
	T query(int x, int y) { return query(y) - query(x - 1); }
};

int N, Q, ans[200002];
ii E[200002];
pair<ii, int> q[200002];

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	cin >> N >> Q;
	fenwick_tree<int> FT(N);
	for (int i = 0; i < N - 1; ++i) {
		cin >> E[i].f >> E[i].s;
		if (E[i].f > E[i].s) swap(E[i].f, E[i].s);
		FT.update(E[i].s, 1);
	}
	for (int i = 0; i < Q; ++i) {
		cin >> q[i].f.f >> q[i].f.s; q[i].s = i;
	}
	sort(E, E + N - 1), sort(q, q + Q);
	for (int i = 0, j = 0; i < Q; ++i) {
		while (j < N - 1 && E[j].f < q[i].f.f) FT.update(E[j++].s, -1);
		ans[q[i].s] = q[i].f.s - q[i].f.f + 1 - FT.query(q[i].f.s);
	}
	for (int i = 0; i < Q; ++i) cout << ans[i] << '\n';
}