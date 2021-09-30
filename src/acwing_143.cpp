/**
*  @author  Zhang Kang (zk54188@gmail.com)
*  @date    2021/09/30 17:43
*  @version 1.0
*
*  @brief   143. 最大异或对
*/
#include<iostream>
#include<string>
using namespace std;
int sz = 1;
int tree[32 * 100005][2];
int a[1000005][32];

void insert(int c[]) {
  int p = 1;
  for (int i = 0; i < 32; ++i) {
    int cur = c[i];
    if (tree[p][cur] == 0) {
      tree[p][cur] = ++ sz;
    }
    p = tree[p][cur];
  }
}

unsigned int search(int c[]) {
  int p = 1;
  unsigned int sum = 0;
  for (int i = 0; i < 32; ++i) {
    int cur = c[i];
    int v = 0;
    if (tree[p][1 - cur]) {
      p = tree[p][1 - cur];
      v = 1;
    } else {
      p = tree[p][cur];
    }
    sum = sum * 2 +  v;
  }
  return sum;
}

int main() {
  int n = 0;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    unsigned int v = 0;
    cin >> v;
    int idx = 31;
    while (v) {
      a[i][idx --] = v & 1;
      v >>= 1;
    }
    insert(a[i]);
  }
  int max_sum = 0;
  for (int i = 0; i < n; ++i) {
    int sum = search(a[i]);
    if (sum > max_sum) {
      max_sum = sum;
    }
  }
  cout << max_sum << "\n";
  return 0;
}
