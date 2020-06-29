#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	char s[10] = "MMOOMO";
	int K;
	cin >> K;
	if (K == 5) {
		cout << "impossible";
		return 0;
	}
	if (K == 1) { cout << "O"; return 0; }
	if (K == 2) { cout << "MO"; return 0; }
	if (K == 3) { cout << "MM";	return 0; }
	if (K == 7) { cout << "MMMO"; return 0; }
	if (K == 9) { cout << "MOMOM"; return 0; }
	if (K % 2 == 0 && K / 2 <= 1e5) {
		for (int i = 0; i <= K / 2; ++i) cout << s[i % 6];
		return 0;
	}
	ll sq = sqrt(8ll * K + 1) + 0.5;
	if (sq * sq == 8ll * K + 1) {
		int t = (sq - 1) / 2;
		for (int i = 0; i < t; ++i) cout << "O";
		return 0;
	}
	/*if (K > 1e8 && K % 2 == 1) {
		cout << "M";
		--K;
	}*/
	int t = sqrt(2 * K);
	while ((((K - t * (t + 1) / 2) - 2) % 2) || K - t * (t + 1) / 2 - 2 < 6) --t;
	for (int i = 0; i < t; ++i) cout << "O";
	int ans = t;
	//cout << t << '\n';
	K += - t * (t + 1) / 2 - 2;
	for (int i = 0; i <= K / 2; ++i) cout << s[i % 6];
	ans += K / 2;
	assert(ans <= 1e5);
	//cout << ans << '\n';
}