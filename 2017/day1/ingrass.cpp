#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
using ll = long long;
using ii = pair<int, int>;

ii P[50005];

bool ccw(ii a, ii b, ii c) { return (ll)(b.f - a.f) * (c.s - a.s) - (ll)(c.f - a.f) * (b.s - a.s) > 0; }

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	int N; cin >> N;
	for (int i = 0; i < N; ++i) cin >> P[i].f >> P[i].s;
	int m = min_element(P, P + N) - P;
	vector<pair<double, int>> A;
	for (int i = 0; i < N; ++i) {
		if (i != m) A.emplace_back(atan2(P[i].s - P[m].s, P[i].f - P[m].f), i);
	}
	sort(begin(A), end(A));
	vector<int> S;
	vector<ii> ans;
	for (int i = 0; i < A.size(); ++i) {
		ans.emplace_back(m, A[i].s);
		while (i) {
			ans.emplace_back(A[i].s, S.back());
			if (S.size() <= 1 || ccw(P[A[i].s], P[S[S.size() - 2]], P[S.back()])) break;
			else S.pop_back();
		}
		S.push_back(A[i].s);
	}
	cout << 3 * N - 2 * S.size() - 4 << ' ' << ans.size() << '\n';
	for (auto& p : ans) cout << p.f + 1 << ' ' << p.s + 1 << '\n';
}