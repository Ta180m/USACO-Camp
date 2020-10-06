#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	int N, L;
	cin >> N >> L;

	multiset<ll> S;
	ll ans = 0;
	for (int i = 0, b, s; i < N; ++i) {
		cin >> b >> s;
		ans = max(ans - (i >= L ? *begin(S) : 0) + s, ans);
		S.insert({ b, s });
		if (i >= L) S.erase(begin(S)), S.erase(prev(end(S)));
	}
	for (auto it = S.begin(); L; ++it, --L) ans -= *it;
	cout << ans << endl;
}