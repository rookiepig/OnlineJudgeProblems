// 694 - The Collatz Sequence
// A =  A / 2 or 3 * A + 1
#include<iostream>
using namespace std;

int main(void) {
	unsigned long long init = 0, limit = 0, backup = 0;
	const unsigned long long odd_mask = 1;
	unsigned int test_case = 1;
	while (true) {
		long long signed_init = 0, signed_limit = 0;
		cin >> signed_init >> signed_limit;
		if (signed_init < 0 || signed_limit < 0) {
			break;
		}
		init = signed_init;
		limit = signed_limit;
		unsigned long long term = 1;
		while (init <= limit) {
			if (init == 1) {
				break;
			}
			if (init & odd_mask) {
				// odd number
				init = 3 * init + 1;
			} else {
				init >>= 1;
			}
			term++;
		}
		if (init > limit) {
			term--;
		}
		cout << "Case " << test_case ++
			<< ": A = " << signed_init << ", limit = " << limit
			 << ", number of terms = " << term << endl;

	}
	return 0;
}