#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr ll p1 = 19, p2 = 29, p3 = 53;
constexpr ll MOD = 1e9+7;

template<int D, typename T> struct vec_nd : public vector<vec_nd<D - 1, T>> {
  static_assert(D >= 1, "Vector dimension must be greater than zero!");
  template<typename... Args> vec_nd(int n = 0, Args... args) : vector<vec_nd<D - 1, T>>(n, vec_nd<D - 1, T>(args...)) { }
};
template<typename T> struct vec_nd<1, T> : public vector<T> { vec_nd(int n = 0, const T& val = T()) : vector<T>(n, val) { } };

int pw(int base, int exp) {
	int res = 1;
	while (exp) {
		if (exp & 1) res = (ll)base * res % MOD;
		exp >>= 1, base = (ll)base * base % MOD;
	}
	return res;
}

int inv(int x) { return pw(x, MOD - 2); }

int main() {
	int T1, R1, C1; cin >> T1 >> R1 >> C1;
	vec_nd<3, ll> A(T1, R1, C1);
	for (int i = 0; i < T1; ++i) for (int j = 0; j < R1; ++j) for (int k = 0; k < C1; ++k) cin >> A[i][j][k];
	
	int T2, R2, C2; cin >> T2 >> R2 >> C2;
	vec_nd<3, ll> B(T2, R2, C2);
	for (int i = 0; i < T2; ++i) for (int j = 0; j < R2; ++j) for (int k = 0; k < C2; ++k) cin >> B[i][j][k];
	
	ll h = 0;
	ll pw1 = 1; for (int i = 0; i < T1; ++i) {
		ll pw2 = 1; for (int j = 0; j < R1; ++j) {
			ll pw3 = 1; for (int k = 0; k < C1; ++k) {
				h = (A[i][j][k] * pw1 % MOD * pw2 % MOD * pw3 + h) % MOD;
			pw3 = p3 * pw3 % MOD; }
		pw2 = p2 * pw2 % MOD; }
	pw1 = p1 * pw1 % MOD; }

	vec_nd<3, ll> S(T2, R2, C2);
	pw1 = 1; for (int i = 0; i < T2; ++i) {
		ll pw2 = 1; for (int j = 0; j < R2; ++j) {
			ll pw3 = 1; for (int k = 0; k < C2; ++k) {
				S[i][j][k] = B[i][j][k] * pw1 % MOD * pw2 % MOD * pw3 % MOD;
				if (i) S[i][j][k] += S[i - 1][j][k];
				if (j) S[i][j][k] += S[i][j - 1][k];
				if (k) S[i][j][k] += S[i][j][k - 1];
				if (i && j) S[i][j][k] -= S[i - 1][j - 1][k];
				if (i && k) S[i][j][k] -= S[i - 1][j][k - 1];
				if (j && k) S[i][j][k] -= S[i][j - 1][k - 1];				
				if (i && j && k) S[i][j][k] += S[i - 1][j - 1][k - 1];
				S[i][j][k] = (S[i][j][k] + MOD * MOD) % MOD;
			pw3 = p3 * pw3 % MOD; }
		pw2 = p2 * pw2 % MOD; }
	pw1 = p1 * pw1 % MOD; }

	ll ans = 0;
	pw1 = 1; for (int i = 0; i <= T2 - T1; ++i) {
		ll pw2 = 1; for (int j = 0; j <= R2 - R1; ++j) {
			ll pw3 = 1;	for (int k = 0; k <= C2 - C1; ++k) {
				ll h2 = S[i + T1 - 1][j + R1 - 1][k + C1 - 1];
				if (i) h2 -= S[i - 1][j + R1 - 1][k + C1 - 1];
				if (j) h2 -= S[i + T1 - 1][j - 1][k + C1 - 1];
				if (k) h2 -= S[i + T1 - 1][j + R1 - 1][k - 1];
				if (i && j) h2 += S[i - 1][j - 1][k + C1 - 1];
				if (i && k) h2 += S[i - 1][j + R1 - 1][k - 1];
				if (j && k) h2 += S[i + T1 - 1][j - 1][k - 1];				
				if (i && j && k) h2 -= S[i - 1][j - 1][k - 1];
				h2 = (h2 + MOD * MOD) % MOD;
				h2 = h2 * inv(pw3) % MOD * inv(pw2) % MOD * inv(pw1) % MOD;
				if (h2 == h) ++ans;
			pw3 = p3 * pw3 % MOD; }
		pw2 = p2 * pw2 % MOD; }
	pw1 = p1 * pw1 % MOD; }
	cout << ans << '\n';
}