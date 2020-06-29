#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
using ll = long long;
using pl = pair<ll, ll>;

ll C[5005], D[5005];
pl DP[5005][5005];

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	ll N, T, RA, RB;
	cin >> N >> T >> RA >> RB;
	for (int i = 0; i < N; ++i) cin >> C[i];
	for (int i = 0; i < N; ++i) cin >> D[i];
	
	memset(DP, 63, sizeof(DP));
	DP[0][0] = pl(0, 0);
	ll ans = T;
	for (int i = 0; i <= N; ++i) {
		for (int j = 0; j <= N; ++j) {
			ll r = 1 + i * RA + j * RB;
			if (i < N) {
				ll t = max((C[i] + DP[i][j].s + r - 1) / r, 0ll);
				DP[i + 1][j] = min(pl(DP[i][j].f + t, -t * r + C[i] + DP[i][j].s), DP[i + 1][j]);
			}
			if (j < N) {
				ll t = max((D[j] + DP[i][j].s + r - 1) / r, 0ll);
				DP[i][j + 1] = min(pl(DP[i][j].f + t, -t * r + D[j] + DP[i][j].s), DP[i][j + 1]);
			}
			ans = min(DP[i][j].f + max((T + DP[i][j].s + r - 1) / r, 0ll), ans);
		}
	}
	cout << ans << '\n';
}