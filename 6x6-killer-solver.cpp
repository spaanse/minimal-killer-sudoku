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
	ifstream config_file("6x6-26-10-11-configurations.txt");
	ifstream solution_file("6x6-solutions.txt");
	vvi solutions;
	string line;
	while (getline(solution_file, line)) {
		istringstream line_ss(line);
		vi solution(36);
		for (auto &cell : solution) line_ss >> cell;
		solutions.push_back(solution);
	}
	cerr << solutions.size() << endl;
	while (getline(config_file, line)) {
		vvi cages;
		for (auto cage : string_view(line) | v::split(" | "sv)) {
			vi cells;
			for (auto cell : string_view(cage) | v::split(" "sv)) {
				cells.push_back(stoi(string(string_view(cell))));
			}
			cages.push_back(cells);
		}

		map<vvi, int> templates;
		for (auto solution : solutions) {
			vvi cages_in_val(6);
			bool valid = true;
			for (int i = 0; i < cages.size(); i++) {
				vi& cage = cages[i];
				for (auto cell : cage) {
					if (cages_in_val[solution[cell]].size() and cages_in_val[solution[cell]].back() == i) valid = false;
					cages_in_val[solution[cell]].push_back(i);
				}
			}
			if (!valid) continue;
			r::sort(cages_in_val);
			auto [last, end] = r::unique(cages_in_val);
			if (last != end) continue;
			templates[cages_in_val]++;
		}

		for (auto solution : solutions) {
			vvi cages_in_val(6);
			bool valid = true;
			for (int i = 0; i < cages.size(); i++) {
				vi& cage = cages[i];
				for (auto cell : cage) {
					if (cages_in_val[solution[cell]].size() and cages_in_val[solution[cell]].back() == i) valid = false;
					cages_in_val[solution[cell]].push_back(i);
				}
			}
			if (!valid) continue;
			r::sort(cages_in_val);
			auto [last, end] = r::unique(cages_in_val);
			if (last != end) continue;
			if (templates[cages_in_val] != 1) continue;
			for (int r = 0; r < 6; r++) {
				for (int c = 0; c < 6; c++) {
					cerr << solution[6*r+c] << " ";
				} cerr << endl;
			} cerr << endl;
		}


		for (auto [temp, count] : templates) {
			if (count == 1) {
				cout << line << endl;
				break;
			}
		}
	}
	return 0;
}
