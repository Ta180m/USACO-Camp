#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int M1 = 8191, M2 = 1e9+7;

string s[10001];
vector<int> h[10001];
int r[10001], hs[2][10001];

inline void print(int x, int d) {
	cout << "MOO ";
	for (int i = 0; i < d; ++i) cout << (1 & (x >> i));
	cout << endl;
}

inline int read(int d) {
	int x = 0;
	for (int i = 0; i < 16; ++i) {
		char c;
		cin >> c;
		if (c == '1') x |= (1 << i);
	}
	return x;
}

inline int hsh(string& s, int m) {
	ll x = 0;
	for (auto& c : s) x *= 31, x += c - 'a', x %= m;
	return x;
}

int main() {
	ofstream debug("debug");

	int c, n[2];
	cin >> c >> n[0];
	for (int i = 0; i < n[0]; ++i) {
		cin >> s[i];
		hs[0][i] = hsh(s[i], M1);
		hs[1][i] = hsh(s[i], M2);
	}
	if (c) {
		print(n[0], 16);
		debug << 1 << ' ' << n[1];
		n[1] = read(16);

		for (int i = 0; i < n[0]; ++i) {
			print(hs[0][i], 13);
			bool b;
			cin >> b;
			if (b == 1) {
				print(hs[1][i], 30);
				cin >> b;
				if (b == 1) {
					cout << "RETURN " << s[i] << endl;
					return 0;
				}
			}
		}
	}
	else {
		n[1] = read(16);
		debug << 0 << ' ' << n[1];
		print(n[0], 16);
		
		for (int i = 0; i < n[0]; ++i) {
			h[hs[0][i]].push_back(i);
		}
		for (int i = 0; i < n[1]; ++i) {
			r[i] = read(13);
			if (h[r[i]].empty()) {
				print(0, 1);
			}
			else {
				print(1, 1);
				int x;
				x = read(30);
				bool ans = 0;
				for (auto& y : h[r[i]]) {
					if (hs[1][y] == x) {
						ans = 1;
						cout << "RETURN " << s[y] << endl;
						print(1, 1);
						return 0;
					}
				}
				if (!ans) {
					print(0, 1);
				}
			}
		}
	}
}