#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define f first
#define s second
using namespace std;
using namespace __gnu_pbds;
using ii = pair<int, int>;
template<typename T> using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
constexpr int MAXN = 100001;

vector<int> T[MAXN + 1];
ordered_set<int> S[4 * MAXN + 4];

void build(int l = 0, int r = MAXN, int n = 1) {
	if (l == r) {
		for (auto& y : T[l]) S[n].insert(y);
	}
	else {
		int m = (l + r) >> 1;
		build(l, m, n << 1), build(m + 1, r, n << 1 | 1);
		for (auto& y : S[n << 1]) S[n].insert(y);
		for (auto& y : S[n << 1 | 1]) S[n].insert(y);
	}
}

int query(int xl, int xr, int yl, int yr, int l = 0, int r = MAXN, int n = 1) {
	if (l > r || l > xr || r < xl) return 0;
	if (l >= xl && r <= xr) return S[n].order_of_key(yr + 1) - S[n].order_of_key(yl);
	else {
		int m = (l + r) >> 1;
		return query(xl, xr, yl, yr, l, m, n << 1) + query(xl, xr, yl, yr, m + 1, r, n << 1 | 1);
	}
}
 
ii P[100001];
 
int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	int N; cin >> N;
	for (int i = 0; i < N; ++i) cin >> P[i].f >> P[i].s;
 
	vector<ii> tmp;
	for (int i = 0; i < N; ++i) tmp.emplace_back(P[i].f, i);
	sort(begin(tmp), end(tmp));
	for (int i = 0; i < N; ++i) {
		if (i && tmp[i].f == tmp[i - 1].f) P[tmp[i].s].f = P[tmp[i - 1].s].f;
		else P[tmp[i].s].f = i;
	}
	tmp.clear();
	for (int i = 0; i < N; ++i) tmp.emplace_back(P[i].s, i);
	sort(begin(tmp), end(tmp));
	for (int i = 0; i < N; ++i) {
		if (i && tmp[i].f == tmp[i - 1].f) P[tmp[i].s].s = P[tmp[i - 1].s].s;
		else P[tmp[i].s].s = i;
	}
	
	for (int i = 0; i < N; ++i) T[P[i].f].push_back(P[i].s);
	build();
	
	vector<ii> X, Y;
	for (int i = 0; i < N; ++i) X.push_back(P[i]), Y.push_back(P[i]);
 
	auto cmpy = [](const ii & a, const ii & b) { return a.s < b.s || (a.s == b.s && a.f < b.f); };
	sort(begin(X), end(X));
	sort(begin(Y), end(Y), cmpy);
	unique(begin(X), end(X));
	unique(begin(Y), end(Y), cmpy);
 
	int ans = 0;
	for (int i = 0; i < N; ++i) {
		auto it = lower_bound(begin(X), end(X), ii(P[i].f, P[i].s));
		int yh = (next(it) != end(X) && next(it)->f == P[i].f ? next(it)->s : MAXN + 1);
		int yl = (it != begin(X) && prev(it)->f == P[i].f ? prev(it)->s : -2);
 
		it = lower_bound(begin(Y), end(Y), ii(P[i].f, P[i].s), cmpy);
		int xh = (next(it) != end(Y) && next(it)->s == P[i].s ? next(it)->f : MAXN + 1);
		int xl = (it != begin(Y) && prev(it)->s == P[i].s ? prev(it)->f : -2);
 
		int q = query(xl + 1, xh - 1, yl + 1, yh - 1);
		if (q > 1) ++ans;
	}
	cout << ans << '\n';
}
