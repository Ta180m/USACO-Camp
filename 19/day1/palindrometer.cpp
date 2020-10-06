#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int P[2][100001];

int main() {
	string S; cin >> S;
	int N = S.size();
	for (int i = 0; i < 2; ++i) {
		for (int j = 0, l = 0, r = 0; j < N; ++j) {
			int k = (j > r ? !i : min(P[i][l + r - j + i], r - j + 1));
			while (j - k - i >= 0 && j + k < N && S[j - k - i] == S[j + k]) ++k;
			P[i][j] = k--;
			if (j + k > r) l = j - k - i, r = j + k;
		}
	}

	ll ans = 0;
	for (int i = 0; i < N; ++i) ans += P[0][i] + P[1][i];
	cout << ans << '\n';
}