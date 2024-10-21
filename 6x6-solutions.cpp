#include <bits/stdc++.h>
using namespace std;
namespace v = views;
namespace r = ranges;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef int64_t ll;
typedef vector<ll> vl;
typedef vector<vl> vvl;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef queue<int> qi;

void solve(int cur, vi& solution, vvi& row_used, vvi& col_used, vvi& box_used, int& count) {
	if (cur == 36) {
		count++;
		for (int i = 0; i < 36; i++) {
			if (i) cout << " ";
			cout << solution[i];
		} cout << endl;
		return;
	}

	int r = cur / 6;
	int c = cur % 6;
	int b = 2*(r/2) + (c/3);
	for (int v = 0; v < 6; v++) {
		if (row_used[r][v]) continue;
		if (col_used[c][v]) continue;
		if (box_used[b][v]) continue;
		if (r == 0 and c != v) continue;
		row_used[r][v] = true;
		col_used[c][v] = true;
		box_used[b][v] = true;
		solution[cur] = v;
		solve(cur+1, solution, row_used, col_used, box_used, count);
		solution[cur] = -1;
		row_used[r][v] = false;
		col_used[c][v] = false;
		box_used[b][v] = false;
	}
}

int main() {
	vvi row_used(6, vi(6, false));
	vvi col_used(6, vi(6, false));
	vvi box_used(6, vi(6, false));
	vi solution(36, -1);
	int count = 0;
	solve(0, solution, row_used, col_used, box_used, count);
	cerr << count << endl;
	return 0;
}
