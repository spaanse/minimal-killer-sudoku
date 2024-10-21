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

const int p = 2; // height of boxes
const int q = 3; // width of boxes
const int N = p*q;
const int min_cell = 10;
const int max_cell = 11;
const int min_cage_size = 2;
const int max_cage_size = 6;

vvi cages;
vvi row_perms;
vvi col_perms;
int total = 0;


void build_cages(vi& cage) {
	if (cage.size() >= min_cage_size) {
		vi sorted = cage;
		r::sort(sorted);
		cages.push_back(sorted);
	}
	if (cage.size() >= max_cage_size) return;
	
	set<int> new_options;
	for (auto cell : cage) {
		int r = cell / N;
		int c = cell % N;
		if (0 <= r-1) new_options.insert(N*(r-1)+c);
		if (r+1 < N) new_options.insert(N*(r+1)+c);
		if (0 <= c-1) new_options.insert(N*r+(c-1));
		if (c+1 < N) new_options.insert(N*r+(c+1));
	}
	for (auto cell : cage) {
		new_options.erase(cell);
	}

	for (auto new_cell : new_options) {
		cage.push_back(new_cell);
		build_cages(cage);
		cage.pop_back();
	}
}

bool possibly_unique(vvi& config) {
	vvi cages_in_row(N, vi(N, -1));
	vvi cages_in_col(N, vi(N, -1));
	for (int i = 0; i < config.size(); i++) {
		vi& cage = config[i];
		for (auto cell : cage) {
			cages_in_row[cell/N][cell%N]=i;
			cages_in_col[cell%N][cell/N]=i;
		}
	}

	for (int r = 0; r < N; r += p) {
		for (int i = 0; i < p; i++) {
			for (int j = i+1; j < p; j++) {
				if (cages_in_row[r+i] == cages_in_row[r+j]) return false;
			}
		}
	}

	for (int c = 0; c < N; c += q) {
		for (int i = 0; i < q; i++) {
			for (int j = i+1; j < q; j++) {
				if (cages_in_col[c+i] == cages_in_col[c+j]) return false;
			}
		}
	}
	return true;
}

bool transform(vvi& config, vi& row_perm, vi& col_perm, vvi& new_config) {
	for (auto cage : config) {
		vi new_cage;
		for (auto cell : cage) {
			new_cage.push_back(N*row_perm[cell/N]+col_perm[cell%N]);
		}
		r::sort(new_cage);
		if (!r::binary_search(cages, new_cage)) return false;
		new_config.push_back(new_cage);
	}
	r::sort(new_config);
	return true;
}

bool essentially_unique(vvi& config) {
	for (auto row_perm : row_perms) {
		for (auto col_perm : col_perms) {
			vvi new_config;
			if (!transform(config, row_perm, col_perm, new_config)) continue;
			if (new_config < config) return false;
		}
	}
	return true;
}

bool valid_new_cage(vi& used, vi& new_cage) {
	for (auto cell : new_cage) {
		if (used[cell]) return false;
	}
	return true;
}

void build_configs(int cur, int count, vi& used, vvi& config) {
	if (count > max_cell) return;

	for (int i = cur; i < cages.size(); i++) {
		vi cage = cages[i];
		if (!valid_new_cage(used, cage)) continue;

		config.push_back(cage);
		for (auto cell : cage) used[cell] = true;
		build_configs(i+1, count+cage.size(), used, config);
		for (auto cell : cage) used[cell] = false;
		config.pop_back();
	}

	if (count < min_cell) return;
	if (count > max_cell) return;
	if (!possibly_unique(config)) return;
	if (!essentially_unique(config)) return;
	
	total++;
	bool first_cage = true;
	for (auto cage : config) {
		if (!first_cage) cout << " | ";
		first_cage = false;
		bool first_cell = true;
		for (auto cell : cage) {
			if (!first_cell) cout << " ";
			first_cell = false;
			cout << cell;
		};
	} cout << endl;
}

bool valid_perm_blocks(vi& perm, int block_size) {
	for (int r = 0; r < N; r+= block_size) {
		for (int i = 1; i < block_size; i++) {
			if (perm[r] / block_size != perm[r+i] / block_size) return false;
		}
	}
	return true;
}

int main() {
	vi cage;
	for (int i = 0; i < N*N; i++) {
		cage.push_back(i);
		build_cages(cage);
		cage.pop_back();
	}
	r::sort(cages);
	auto [first, last] = r::unique(cages);
	cages.erase(first, last);
	cerr << cages.size() << endl;

	vi row_perm(N);
	iota(row_perm.begin(),row_perm.end(),0);
	do {
		if (valid_perm_blocks(row_perm, p)) {
			row_perms.push_back(row_perm);
		}
	} while (r::next_permutation(row_perm).found);

	vi col_perm(N);
	iota(col_perm.begin(),col_perm.end(),0);
	do {
		if (valid_perm_blocks(col_perm, q)) {
			col_perms.push_back(col_perm);
		}
	} while (r::next_permutation(col_perm).found);

	vvi config;
	vi used(N*N, false);
	build_configs(0, 0, used, config);

	cerr << total << endl;
	return 0;
}
