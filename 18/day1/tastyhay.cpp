#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
using ll = long long;
using ii = pair<int, int>;

int t[100001];
map<int, ll> cnt, pre;

int main() {
    int N, Q;
	cin >> N >> Q;
	for (int i = 0; i < N; ++i) cin >> t[i];

	unordered_map<int, int> m;
	for (int i = N - 1; i >= 0; --i) {
		unordered_map<int, int> tmp;
		for (auto x : m) tmp[__gcd(t[i], x.f)] += x.s;
		++tmp[t[i]];
		swap(tmp, m);
		for (auto& x : m) cnt[x.f] += x.s;
	}
	for (auto& x : cnt) pre[x.f] = x.s + (pre.size() ? pre.rbegin()->s : 0);
	
	while (Q--) {
		int a, b;
		cin >> a >> b;
		auto ia = pre.upper_bound(a - 1), ib = pre.upper_bound(b);
		cout << (ib != pre.begin() ? prev(ib)->s : 0) - (ia != pre.begin() ? prev(ia)->s : 0) << '\n';
	}
}