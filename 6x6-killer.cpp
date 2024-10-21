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

int main() {
	int N = 6;
	// generate all horizontal and vertical domino's
	vii dominos;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N-1; c++) {
			dominos.push_back({6*r+c,6*r+(c+1)});
		}
	}
	for (int r = 0; r < N-1; r++) {
		for (int c = 0; c < N; c++) {
			dominos.push_back({6*r+c,6*(r+1)+c});
		}
	}

	// set up 60 choose 4 combinations of choosing domino's
	vi pairs(dominos.size());
	for (int i = 0; i < 4; i++) pairs[i] = true;
	r::reverse(pairs);
	

	int count = 0;
	// loop through combinations of 4 domino's
	do {
		vii used_domino;
		for (int i = 0; i < dominos.size(); i++) if (pairs[i]) {
			used_domino.push_back(dominos[i]);
		}

		vi row_used(N);
		vi col_used(N);
		vi used(N*N);

		bool valid = true;
		// loop through domino's and set which rows, columns and cells are used
		for (auto domino : used_domino) {
			if (used[domino.first] or used[domino.second]) {
				// cell used twice
				valid = false;
				break;
			}
			used[domino.first] = true;
			row_used[domino.first / N] = true;
			col_used[domino.first % N] = true;
			used[domino.second] = true;
			row_used[domino.second / N] = true;
			col_used[domino.second % N] = true;
		}
		if (!valid) continue;
		// more solutions because rows can be swapped
		if (!row_used[0] and !row_used[1]) continue;
		if (!row_used[2] and !row_used[3]) continue;
		if (!row_used[4] and !row_used[5]) continue;
		// more solutions because columns can be swapped
		if (!col_used[0] and !col_used[1]) continue;
		if (!col_used[0] and !col_used[2]) continue;
		if (!col_used[1] and !col_used[2]) continue;
		if (!col_used[3] and !col_used[4]) continue;
		if (!col_used[3] and !col_used[5]) continue;
		if (!col_used[4] and !col_used[5]) continue;

		vi row_perm(N);
		iota(row_perm.begin(),row_perm.end(),0);
		vvi row_perms;
		do {
			if (row_perm[0] / 2 != row_perm[1] / 2) continue;
			if (row_perm[2] / 2 != row_perm[3] / 2) continue;
			if (row_perm[4] / 2 != row_perm[5] / 2) continue;
			bool row_perm_valid = true;
			for (auto domino : used_domino) {
				if (abs(row_perm[domino.first / 6] - row_perm[domino.second / 6]) > 1) {
					row_perm_valid = false;
				}
			}
			if (!row_perm_valid) continue;
			row_perms.push_back(row_perm);
		} while (r::next_permutation(row_perm).found);

		vi col_perm(N);
		iota(col_perm.begin(),col_perm.end(),0);
		vvi col_perms;
		do {
			if (col_perm[0] / 3 != col_perm[1] / 3) continue;
			if (col_perm[0] / 3 != col_perm[2] / 3) continue;
			if (col_perm[3] / 3 != col_perm[4] / 3) continue;
			if (col_perm[3] / 3 != col_perm[5] / 3) continue;
			bool col_perm_valid = true;
			for (auto domino : used_domino) {
				if (abs(col_perm[domino.first % 6] - col_perm[domino.second % 6]) > 1) {
					col_perm_valid = false;
				}
			}
			if (!col_perm_valid) continue;
			col_perms.push_back(col_perm);
		} while (r::next_permutation(col_perm).found);

		for (auto row_perm : row_perms) {
			for (auto col_perm : col_perms) {
				vi used2(N*N);
				for (int r = 0; r < N; r++) {
					for (int c = 0; c < N; c++) {
						used2[6*r+c] = used[6*row_perm[r]+col_perm[c]];
					}
				}
				if (used2 < used) {
					valid = false;
					break;
				}
			}
			if (!valid) break;
		}
		if (!valid) continue;

		for (auto domino : used_domino) {
			cout << domino.first << " " << domino.second << " ";
		} cout << endl;
		count++;
	} while (r::next_permutation(pairs).found);

	cerr << count << endl;
	return 0;
}
