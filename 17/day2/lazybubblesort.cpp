#include <bits/stdc++.h>
using namespace std;

int A[100001];

int main() {
	int N, K; cin >> N >> K;
	for (int i = 0; i < N; ++i) cin >> A[i];
	multiset<int> S;
	vector<int> ans;
	for (int i = 0; i < N; ++i) {
		if (S.size() < K || A[i] > *begin(S)) {
			if (S.size() == K) ans.push_back(*begin(S)), S.erase(begin(S));
			S.insert(A[i]);
		}
		else ans.push_back(A[i]);
	}
	while (S.size()) ans.push_back(*begin(S)), S.erase(begin(S));
	for (auto& x : ans) cout << x << '\n';
}