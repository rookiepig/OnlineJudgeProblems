// 10300 - Ecological Premium
// money = size * friendness

#include<iostream>

using namespace std;

int main(void) {
	int test_case;
	cin >> test_case;
	while (test_case-- > 0) {
		long long money = 0;
		int num_farm;
		cin >> num_farm;
		while (num_farm-- > 0) {
			long long size = 0, animal = 0, friendness = 0;
			cin >> size >> animal >> friendness;
			money += size * friendness;
		}
		cout << money << endl;
	}
	return 0;
}