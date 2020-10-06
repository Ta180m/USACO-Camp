#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	string S; cin >> S;
	int N = S.size(), cnt = 0;
	if (count(begin(S), end(S), 'G') << 1 != N) {
		cout << "NO\n";
		return 0;
	}
	unordered_set<int> M[2];
	for (int i = 0; i < N; ++i) {
		if (S[i] != S[(i-1+N)%N]) M[S[i] == 'G'].insert(cnt);
		cnt += (S[i] == 'G' ? 1 : -1);
		if (S[i] != S[(i+1)%N] && M[S[i] == 'G'].find(cnt - (S[i] == 'G' ? 1 : -1)) != end(M[S[i] == 'G'])) {
			cout << "YES\n";
			return 0;
		}
	}
	cout << "NO\n";
	return 0;
}