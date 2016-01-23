#include<iostream>
#include<map>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

char easytolower(char in){
  if (in <= 'Z' && in >= 'A')
    return in - ('Z' - 'z');
  return in;
}

typedef struct Loc {
  int row;
  int col;
} Loc;

void BuildMap(const vector<string>& input, map<string, Loc>& tab) {
  int row_num = input.size();
  int col_num = input[0].size();
  string tmp = "";
  for (int r = row_num - 1; r >= 0; --r) {
    for (int c = col_num - 1; c >= 0; --c) {
      Loc cur_loc; cur_loc.row = r + 1; cur_loc.col = c + 1;
      // eight direction
      // up
      tmp = "";
      for (int cur_r = r, cur_c = c; cur_r >= 0; --cur_r) {
        tmp += input[cur_r][cur_c];
        tab[tmp] = cur_loc;
      }
      // right-up
      tmp = "";
      for (int cur_r = r, cur_c = c; cur_r >= 0 && cur_c < col_num; --cur_r, ++cur_c) {
        tmp += input[cur_r][cur_c];
        tab[tmp] = cur_loc;
      }
      // right
      tmp = "";
      for (int cur_r = r, cur_c = c; cur_c < col_num;  ++cur_c) {
        tmp += input[cur_r][cur_c];
        tab[tmp] = cur_loc;
      }
      // right-down
      tmp = "";
      for (int cur_r = r, cur_c = c; cur_r < row_num && cur_c < col_num; ++cur_r, ++cur_c) {
        tmp += input[cur_r][cur_c];
        tab[tmp] = cur_loc;
      }
      // down
      tmp = "";
      for (int cur_r = r, cur_c = c; cur_r < row_num; ++cur_r) {
        tmp += input[cur_r][cur_c];
        tab[tmp] = cur_loc;
      }
      // left-down
      tmp = "";
      for (int cur_r = r, cur_c = c; cur_r < row_num && cur_c >= 0; ++cur_r, --cur_c) {
        tmp += input[cur_r][cur_c];
        tab[tmp] = cur_loc;
      }
      // left
      tmp = "";
      for (int cur_r = r, cur_c = c; cur_c >= 0; --cur_c) {
        tmp += input[cur_r][cur_c];
        tab[tmp] = cur_loc;
      }
      // left-up
      tmp = "";
      for (int cur_r = r, cur_c = c; cur_r >= 0 && cur_c >= 0; --cur_r, --cur_c) {
        tmp += input[cur_r][cur_c];
        tab[tmp] = cur_loc;
      }
    }
  }
}
int main(void) {
  int test_case = 0;
  cin >> test_case;
  while (test_case--) {
    int row_num = 0, col_num = 0;
    cin >> row_num >> col_num;
    vector<string> input(row_num, "");
    for (int i = 0; i < row_num; ++i) {
      cin >> input[i];
      transform(input[i].begin(), input[i].end(), input[i].begin(), ::tolower);
    }
    map<string, Loc> tab;
    BuildMap(input, tab);
    int search_num = 0;
    cin >> search_num;
    while (search_num--) {
      string search;
      cin >> search;
      transform(search.begin(), search.end(), search.begin(), ::tolower);
      Loc tmp = tab.find(search)->second;
      cout << tmp.row << " " << tmp.col << endl;
    }
    if (test_case) {
      cout << endl;
    }
  }
}