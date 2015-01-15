// 458 - The Decoder
// out = in - 7
#include<iostream>

using namespace std;
int main(void) {
	char in = 0;
	while (cin.get(in)) {
		if (in == '\n') {
			cout << in;
		} else {
			cout << (char)(in - 7);
		}
	}
	return 0;
}