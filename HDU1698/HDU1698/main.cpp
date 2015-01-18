///////////////////////////////////////////////////////
// File: main.cpp
// Desc: HDU 1698 segment tree lazy update 
//  
// Author: rookiepig
// Date: 2015/01/17
//
///////////////////////////////////////////////////////

#include<cstdio>
#include<algorithm>
using namespace std;

#define MAX_N 111111
int sum[MAX_N << 2];
int lazy[MAX_N << 2];    // record the new value
void PushUp(int rt) {
  sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}
void PushDown(int rt, int len) {
  //  lazy[rt] must not equal to 0
  if (lazy[rt]) {
    lazy[rt << 1] = lazy[rt << 1 | 1] = lazy[rt];
    sum[rt << 1] = lazy[rt] * (len - (len >> 1));
    sum[rt << 1 | 1] = lazy[rt] * (len >> 1);
    lazy[rt] = 0;
  }

}
void Build(int rt, int rt_st, int rt_ed) {
  if (rt_st == rt_ed) {
    // input node data
    // scanf("%d", &sum[rt]);
    sum[rt] = 1;
    lazy[rt] = 0;
    return;
  }
  int mid = (rt_st + rt_ed) >> 1;
  Build(rt << 1, rt_st, mid);
  Build(rt << 1 | 1, mid + 1, rt_ed);
  lazy[rt] = 0;
  PushUp(rt);
}
void Update(int rt, int rt_st, int rt_ed, int up_st, int up_ed, int new_val) {
  int len = rt_ed - rt_st + 1;
  if (up_st <= rt_st && up_ed >= rt_ed) {
    sum[rt] = new_val * len;
    lazy[rt] = new_val;
    return;
  }
  PushDown(rt, len);
  int mid = (rt_st + rt_ed) >> 1;
  if (up_st <= mid) {
    Update(rt << 1, rt_st, mid, up_st, up_ed, new_val);
  }
  if (up_ed > mid) {
    Update(rt << 1 | 1, mid + 1, rt_ed, up_st, up_ed, new_val);
  }
  PushUp(rt);
}
//int Query(int rt, int rt_st, int rt_ed, int q_st, int q_ed) {
//  if (q_st <= rt_st && q_ed >= rt_ed) {
//    return sum[rt];
//  }
//  if (lazy[rt]) {
//    PushDown(rt, rt_ed - rt_st + 1);
//  }
//  int mid = (rt_st + rt_ed) >> 1;
//  int tmp_sum = 0;
//  if (q_st <= mid) {
//    tmp_sum += Query(rt << 1, rt_st, mid, q_st, q_ed);
//  }
//  if (q_ed > mid) {
//    tmp_sum += Query(rt << 1 | 1, mid + 1, rt_ed, q_st, q_ed);
//  }
//  return tmp_sum;
//}

int main(void) {
  int test_case;
  scanf("%d", &test_case);
  for (int t = 0; t < test_case; ++t) {
    int n = 0;
    int q_num = 0;
    scanf("%d%d", &n, &q_num);
    Build(1, 1, n);
    for (int q = 0; q < q_num; ++q) {
      int up_st = 0;
      int up_ed = 0;
      int new_val = 0;
      scanf("%d%d%d", &up_st, &up_ed, &new_val);
      Update(1, 1, n, up_st, up_ed, new_val);
    }
    printf("Case %d: The total value of the hook is %d.\n", t + 1, sum[1]);
  }
  return 0;
}