/**
*  @author  Zhang Kang (zk54188@gmail.com)
*  @date    2021/09/30 17:43
*  @version 1.0
*
*  @brief   142. 前缀统计
*/
#include<iostream>
#include<string>
using namespace std;
#define MAX_N 1000005
int sz = 1;
int tree[MAX_N][26];
int word_count[MAX_N];

void insert(const string& s) {
  int p = 1;
  for (int i = 0; i < s.size(); ++i) {
    int cur = s[i] - 'a';
    if (tree[p][cur] == 0) {
      tree[p][cur] = ++ sz;
    }
    p = tree[p][cur];
  }
  word_count[p] ++;
}

int search(const string& s) {
  int sum = 0;
  int p = 1;
  for (int i = 0; i < s.size(); ++i) {
    int cur = s[i] - 'a';
    p = tree[p][cur];
    if (p == 0) {
      break;
    }
    sum += word_count[p];
  }
  return sum;
}

int main() {
  int n = 0;
  int m = 0;
  cin >> n >> m;
  string s = " ";
  while (n -- > 0) {
    cin >> s;
    insert(s);
  }
  while (m -- > 0) {
    cin >> s;
    cout << search(s) << "\n";
  }
  return 0;
}
