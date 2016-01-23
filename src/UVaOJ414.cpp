// 414 - Machined Surfaces
// find the max number of X in each row
// remain space = \sum{max_x - x_i}
// where x_i isthe number of X in each row

#include<iostream>
#include<string>
using namespace std;

int main(void) {
	const int MAX_ROW = 14;
	const int MAX_COL = 25;
	int x_count[MAX_ROW];
	while (true) {
		int row_num = 0;
		cin >> row_num;
		if (row_num <= 0) {
			break;
		}
		char ch = 0;
		cin.get(ch); // remove line ending

		int max_x = 0;
		for (int i = 0; i < row_num; ++i) {
			char row[MAX_COL+1] = "";
			cin.getline(row, MAX_COL+1);
			x_count[i] = 0;
			// count x number
			for (int j = 0; j < MAX_COL; ++j) {
				if (row[j] == 'X') {
					++x_count[i];
				}
			}
			// record max x
			if (x_count[i] > max_x) {
				max_x = x_count[i];
			}
		}
		int space_num = 0;
		for (int i = 0; i < row_num; ++i) {
			space_num += (max_x - x_count[i]);
		}
		cout << space_num << '\n';
	}
	

	return 0;
}