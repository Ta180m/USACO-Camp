#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
typedef pair<int, int> ii;

int M = 10000;

int main() {
	ofstream cout("triangles.in");

	int N = 100;
	cout << N << '\n';
	srand(time(0));
	vector<ii> v;
	for (int i = 0; i < N; ++i) {
		ii x;
		do {
			x.f = (rand() % (2 * M)) - M, x.s = (rand() % (2 * M)) - M;
		} while (find(v.begin(), v.end(), x) != v.end());
		v.push_back(x);
		cout << x.f << ' ' << x.s << '\n';
	}
}