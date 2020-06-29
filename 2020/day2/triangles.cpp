#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
constexpr ll MOD = 1e9+7;

ii P[2002];

int main() {
	ifstream cin("triangles.in");
	ofstream cout("triangles.out");

	int N;
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> P[i].f >> P[i].s;
	sort(P, P + N);

	ll ans = 0;
	for (int i = 0; i < N; ++i) {
		ii p = P[i];
		vector<ii> l, r;
		for (int j = 0; j < i; ++j) l.push_back(P[j]);
		for (int j = i + 1; j < N; ++j) r.push_back(P[j]);
		sort(l.begin(), l.end(), [&p](const ii& a, const ii& b) {
			int x = (a.f - p.f) * (b.s - p.s) - (a.s - p.s) * (b.f - p.f);
			if (x == 0) return (a.f - p.f) * (a.f - p.f) + (a.s - p.s) * (a.s - p.s) < (b.f - p.f) * (b.f - p.f) + (b.s - p.s) * (b.s - p.s);
			return x < 0;
		});
		sort(r.begin(), r.end(), [&p](const ii& a, const ii& b) {
			int x = (a.f - p.f) * (b.s - p.s) - (a.s - p.s) * (b.f - p.f);
			if (x == 0) return (a.f - p.f) * (a.f - p.f) + (a.s - p.s) * (a.s - p.s) < (b.f - p.f) * (b.f - p.f) + (b.s - p.s) * (b.s - p.s);
			return x < 0;
		});

		for (int j = 0, k = 0; j < i; ++j) {
			while (k < N - i - 1 && (l[j].f - p.f) * (r[k].s - p.s) - (l[j].s - p.s) * (r[k].f - p.f) <= 0) ++k;
			ans += (ll)(2 * j + N - 2 * i - 2 * k) * (p.s + l[j].s) * (p.f - l[j].f) + MOD * MOD;
			ans %= MOD;
		}
	}

	cout << ans << '\n';
}