// 490 - Rotating Sentences
// 100 x 100 int matrix to store


// a good C++ example

//#include<iostream>
//#include<vector>
//#include<string>
//
//using namespace std;
//
//int main(){
//	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
//
//	string s;
//	vector<string> v;
//	int n = -1;
//
//	while (getline(cin, s)){
//		v.push_back(s);
//		n = max(n, (int)s.size());
//	}
//
//	vector<string> u(n, "");
//
//	for (int i = v.size() - 1; i >= 0; i--){
//		for (int j = 0; j<v[i].size(); j++) u[j] += v[i][j];
//		for (int j = v[i].size(); j<n; j++) u[j] += " ";
//	}
//
//	for (int i = 0; i<n; i++) cout << u[i] << endl;
//
//	return 0;
//}
#include<iostream>
#include<algorithm>
#include<cstring>

#include<vector>
using namespace std;

int main(void) {
	// freopen("in.txt", "r", stdin);
	const int MAX_LINE = 100 + 1;
	const int MAX_LEN = 100 + 1;
	char buff[MAX_LEN] = "";
	
	char in_mat[MAX_LINE][MAX_LEN];
	for (int i = 0; i < MAX_LINE; ++i) {
		for (int j = 0; j < MAX_LEN; ++j) {
			in_mat[i][j] = -1;
		}
	}
	int line_num = 0;
	int max_len = -1;
	while (cin.getline(in_mat[line_num], MAX_LEN)) {
		max_len = max(max_len, (int)strlen(in_mat[line_num]));
		++line_num;
	}
	//for (int i = 0; i < line_num; ++i) {
	//	for (int j = 0; j < max_len; ++j) {
	//		if (in_mat[i][j] == -1) {
	//			in_mat[i][j] = ' ';
	//		}
	//	}
	//}
	for (int j = 0; j < max_len; ++j) {
		//int last_ch_loc = -1;
		//for (int i = 0; i < line_num; ++i) {
		//	if (in_mat[i][j] != -1) {
		//		last_ch_loc = i;
		//		break;
		//	}
		//}
		for (int i = line_num - 1; i >= 0; --i) {
			if (in_mat[i][j] != -1 && in_mat[i][j] != '\0') {
				cout << in_mat[i][j];
			}
			else {
				cout << ' ';
			}
		}
		cout << '\n';
	}
	return 0;
}