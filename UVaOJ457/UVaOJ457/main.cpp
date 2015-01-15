// 457 - Linear Cellular Automata
// simple simulation problem
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

int main(void) {
	const int DNA_LEN = 10;
	const int DISH_NUM = 40 + 2; // 1 - 40 are actual dishes
	                             // 0, 41 dummy dishes;
	const string output_fmt = " .xW";
	int dna[DNA_LEN];
	int dish[DISH_NUM];
	int new_dish[DISH_NUM];
	int test_case = 0;
	cin >> test_case;
	while (test_case--) {
		for (int i = 0; i < DNA_LEN; ++i) {
			cin >> dna[i];
		}
		fill(dish, dish + DISH_NUM, 0);
		fill(new_dish, new_dish + DISH_NUM, 0);
		dish[20] = 1;    // init dish[20] to 1
		for (int day = 0; day < 50; ++day) {
			// print dish
			for (int i = 1; i <= DISH_NUM - 2; ++i) {
				cout << output_fmt[dish[i]];
			}
			cout << '\n';
			// evolve
			for (int i = 1; i <= DISH_NUM - 2; ++i) {
				new_dish[i] = dna[dish[i] + dish[i - 1] + dish[i + 1]];
			}
			copy(new_dish, new_dish + DISH_NUM, dish);
		}
		if (test_case) {
			cout << '\n';
		}
	}
	return 0;
}