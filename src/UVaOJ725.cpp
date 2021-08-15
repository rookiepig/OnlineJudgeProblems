/**
*  @author  Zhang Kang (zhangkang.blizzard@bytedance.com)
*  @date    2021/08/15 16:32
*  @version 1.0
*
*  @brief   uva 725 division
*           url:
*           https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=666
*/

#include<iostream>
#include<cstdlib>
using namespace std;

#define MAX 10


// cand[0:4] is used for fghij
// cand[5:9] is used for abcde
int cand[MAX];
bool is_used[MAX];
int N;
bool has_ans = false;

bool is_valid(void) {
  bool check_valid[MAX];
  for (int i = 0; i < MAX; ++i) {
    check_valid[i] = false;
  }
  int first_sum = 0;
  int mul = 1;
  for (int i = 4; i >= 0; --i) {
    check_valid[cand[i]] = true;
    first_sum += mul * cand[i];
    mul *= 10;
  }
  int sec_sum = first_sum * N;
  if (sec_sum > 98765) {
    return false;
  }
  if (sec_sum <= 9876 && is_used[0]) {
    return false;
  }
  while (sec_sum) {
    if (check_valid[sec_sum % 10]) {
      return false;
    }
    check_valid[sec_sum % 10] = true;
    sec_sum /= 10;
  }
  return true;
}

void print_ans(void) {
  int first_sum = 0;
  int mul = 1;
  for (int i = 4; i >= 0; --i) {
    first_sum += mul * cand[i];
    mul *= 10;
  }
  int sec_sum = first_sum * N;
  for (int i = 9; i >= 5; --i) {
    cand[i] = sec_sum % 10;
    sec_sum /= 10;
  }
  for (int i = 5; i < 10; ++i) {
    printf("%d", cand[i]);
  }
  printf(" / ");
  for (int i = 0; i < 5; ++i) {
    printf("%d", cand[i]);
  }
  printf(" = %d\n", N);
}

void search(int cur) {
  if (cur == MAX / 2) {
    if (is_valid()) {
      has_ans = true;
      print_ans();
    }
  } else {
    for (int i = 0; i < MAX; ++i) {
      if (!is_used[i]) {
        cand[cur] = i;
        is_used[i] = true;
        search(cur + 1);
        is_used[i] = false;
      }
    }
  }
}

int main(void) {
  bool is_first = true;
  while (cin >> N) {
    if (N == 0) {
      break;
    }
    // init data
    has_ans = false;
    for (int i = 0; i < MAX; ++i) {
      cand[i] = 0;
      is_used[i] = false;
    }
    if (is_first) {
      is_first = false;
    } else {
      printf("\n");
    }
    search(0);
    if (!has_ans) {
      printf("There are no solutions for %d.\n", N);
    }
  }
  return 0;
}
