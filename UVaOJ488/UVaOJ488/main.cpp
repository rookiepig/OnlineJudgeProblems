// 488 - Triangle Wave
// simple printing program

#include<iostream>

using namespace std;

int main(void) {
	//freopen("out.txt", "w", stdout);
	int test_case;
	cin >> test_case;
	while (test_case--) {
		int amp = 0, frq = 0;
		cin >> amp >> frq;
		for (int f = 0; f < frq; ++f) {
			if (f != 0) {
				cout << '\n';
			}
			for (int a = 1; a <= amp; ++a) {
				for (int t = 0; t < a; ++t) {
					cout << a;
				}
				cout << '\n';
			}
			for (int a = amp - 1; a >= 1; --a) {
				for (int t = 0; t < a; ++t) {
					cout << a;
				}
				cout << '\n';
			}
			//if (f != frq - 1) {
			//	cout << '\n';
			//}
		}
		if (test_case) {
			cout << '\n';
		}
	}
	return 0;
}