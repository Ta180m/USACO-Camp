#include <bits/stdc++.h>
using namespace std;
 
int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
 
	int N;
	cin >> N;
	int ans = 1, cnt = 1;
	for (int i = 2; i < N; ++i) {
		if (cnt) {
			cout << ans << ' ' << i << endl;
			string s; cin >> s;
			s[0] == 'S' ? ++cnt : --cnt;
		}
		else {
			ans = i;
			++cnt;
		}
	}
	cout << (cnt ? ans : N) << endl;
}