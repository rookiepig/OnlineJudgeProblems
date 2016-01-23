// 445 - Marvelous Mazes

#include<iostream>
using namespace std;

enum State {NEW_LINE, PRINT};

int main(void) {
	// freopen("in.txt", "r", stdin);
	// freopen("out.txt", "w", stdout);
	State state = NEW_LINE;
	int count = 0;
	char ch = 0;
	while (cin.get(ch)) {
		switch (state)
		{
		case NEW_LINE:
			if (isdigit(ch)) {
				count += (ch - '0');
				state = PRINT;
			} else if (ch == '\n') {
				// a new maze
				cout << ch;
				count = 0;
			}
			break;
		case PRINT:
			if (isdigit(ch)) {
				count += (ch - '0');
			} else if (ch == '\n') {
				cout << ch;
				count = 0;
				state = NEW_LINE;
			} else if (ch == '!') {
				cout << '\n';
				count = 0;
			} else {
				if (ch == 'b') {
					ch = ' ';
				}
				while (count-- > 0) {
					cout << ch;
				}
				count = 0;
			}
			break;
		default:
			break;
		}
	}
	return 0;
}