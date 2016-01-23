// 494 - Kindergarten Counting Game
// word count in each line
// use state transistion

#include<iostream>
#include<cctype>
using namespace std;

enum State {NO_WORD, WORD};
int main(void) {
	State state = NO_WORD;
	char ch = 0;
	int word_count = 0;
	while (cin.get(ch)) {
		switch (state) {
		case NO_WORD :
			if (isalpha(ch)) {
				word_count++;
				state = WORD;
			} else if (ch == '\n') {
				cout << word_count << '\n';
				word_count = 0;
				state = NO_WORD;
			} else {
				// do nothing
			}
			break;
		case WORD :
			if (isalpha(ch)) {
				// do nothing
			} else if (ch == '\n') {
				cout << word_count << '\n';
				word_count = 0;
				state = NO_WORD;
			} else {
				state = NO_WORD;
			}
			break;
		}
	}
	return 0;
}