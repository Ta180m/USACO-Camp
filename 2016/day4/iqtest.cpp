#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N, K, A[400004];

inline ll pw(ll base, ll exp) {
	ll res = 1;
	while (exp) {
		if (exp & 1) res = base * res % K;
		exp >>= 1, base = base * base % K;
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	
	cin >> N >> K;
	for (int i = 0; i < N; ++i) cin >> A[i];

	ll phi = K, tmp = K;
	vector<int> factors, exp;
	for (int i = 2; i * i <= K; ++i) {
		if (tmp % i == 0) {
			while (tmp % i == 0) tmp /= i;
			factors.push_back(i), exp.push_back(0);
			phi = phi * (i - 1) / i;
		}
	}
	if (tmp > 1) {
		factors.push_back(tmp), exp.push_back(0);
		phi = phi * (tmp - 1) / tmp;
	}

	ll cur = 1, ans = A[0];
	for (int i = 1; i < N; ++i) {
		ll x = N - i, y = i;
		for (int j = 0; j < factors.size(); ++j) {
			while (x % factors[j] == 0) ++exp[j], x /= factors[j];
			while (y % factors[j] == 0) --exp[j], y /= factors[j];
		}
		ll tmp = cur = x * pw(y, phi - 1) % K * cur % K;
		for (int j = 0; j < factors.size(); ++j) tmp = pw(factors[j], exp[j]) * tmp % K;
		ans = (tmp * A[i] + ans) % K;
	}
	cout << ans;
}