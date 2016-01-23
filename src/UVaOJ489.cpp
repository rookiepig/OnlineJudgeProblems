// 489 - Hangman Judge
// simple simulation problem

#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

int main(void) {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	const int MAX_LETTER = 256;
	const int MAX_WRONG_NUM = 7;
	while (true) {
		int round = -1;
		cin >> round;
		if (round == -1) {
			break;
		}
		string sol = "", guess = "";
		cin >> sol >> guess;
		int count[MAX_LETTER];
		fill(count, count + MAX_LETTER, 0);
		int sol_len = sol.size();
		for (int i = 0; i < sol_len; ++i) {
			count[sol[i]] ++;
		}
		cout << "Round " << round << '\n';
		int wrong_num = 0;
		int cur_count[MAX_LETTER];
		int has_used[MAX_LETTER];
		fill(has_used, has_used + MAX_LETTER, 0);
		copy(count, count + MAX_LETTER, cur_count);
		for (int i = 0; i < guess.size(); ++i) {
			int cur_guess = guess[i];
			if (cur_count[cur_guess]) {
				sol_len -= cur_count[cur_guess];
				cur_count[cur_guess] = 0;
				if (sol_len <= 0) {
					cout << "You win.\n";
					break;
				}
			} else {
				if (!cur_count[cur_guess] && !has_used[cur_guess]) {
					// guess letter not exist
					wrong_num++;
					has_used[cur_guess] = 1;
					if (wrong_num >= MAX_WRONG_NUM) {
						cout << "You lose.\n";
						break;
					}
				}
			}
		}
		if (wrong_num < MAX_WRONG_NUM && sol_len > 0) {
			cout << "You chickened out.\n";
		}
	}
	

}