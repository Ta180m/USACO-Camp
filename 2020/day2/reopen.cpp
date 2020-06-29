#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n, a, b;
	string r;
	cin >> n >> a >> b >> r;
	
	if (r == "1/2") {
		for (int i = 0; i < n / 2; ++i) cout << b * i << ' ' << 0 << '\n';
		for (int i = n / 2; i < n; ++i) cout << b * i + a << ' ' << 0 << '\n';
	}
	else {
		int d = a * (b + 1) / 2 % b;
		for (int i = 0; i < n; ++i) {
			int x = d + (i / 4) * b, y = 0;
			if (i % 2 == 1) swap(x, y);
			if (i % 4 == 2) x = -x;
			if (i % 4 == 3) y = -y;
			cout << x + 500000000 << ' ' << y + 500000000 << '\n';
		}
	}
}