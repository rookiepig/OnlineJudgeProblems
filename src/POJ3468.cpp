///////////////////////////////////////////////////////
// File: main.cpp
// Desc: POJ 3468 A Simple Problem with Integers
//       Segment tree + lazy update
// Author: rookiepig
// Date: 2015/01/18
//
///////////////////////////////////////////////////////


#include<cstdio>
#include<algorithm>
using namespace std;

typedef long long lint;

#define MAX_N 100005
lint sum[MAX_N << 2];
lint lazy[MAX_N << 2];    // record the added value
void PushUp(lint rt) {
  sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}
void PushDown(lint rt, lint len) {
  //  lazy[rt] must not equal to 0
  if (lazy[rt]) {
    lazy[rt << 1] += lazy[rt];
    lazy[rt << 1 | 1] += lazy[rt];
    sum[rt << 1] += lazy[rt] * (len - (len >> 1));
    sum[rt << 1 | 1] += lazy[rt] * (len >> 1);
    lazy[rt] = 0;
  }

}
void Build(lint rt, lint rt_st, lint rt_ed) {
  if (rt_st == rt_ed) {
    // input node data
    scanf("%lld", &sum[rt]);
    // sum[rt] = 1;
    lazy[rt] = 0;
    return;
  }
  lint mid = (rt_st + rt_ed) >> 1;
  Build(rt << 1, rt_st, mid);
  Build(rt << 1 | 1, mid + 1, rt_ed);
  lazy[rt] = 0;
  PushUp(rt);
}
void Update(lint rt, lint rt_st, lint rt_ed, lint up_st, lint up_ed, lint add_val) {
  int len = rt_ed - rt_st + 1;
  if (up_st <= rt_st && up_ed >= rt_ed) {
    sum[rt] += add_val * len;
    lazy[rt] += add_val;
    return;
  }
  PushDown(rt, len);
  int mid = (rt_st + rt_ed) >> 1;
  if (up_st <= mid) {
    Update(rt << 1, rt_st, mid, up_st, up_ed, add_val);
  }
  if (up_ed > mid) {
    Update(rt << 1 | 1, mid + 1, rt_ed, up_st, up_ed, add_val);
  }
  PushUp(rt);
}

lint Query(lint rt, lint rt_st, lint rt_ed, lint q_st, lint q_ed) {
  if (q_st <= rt_st && q_ed >= rt_ed) {
    return sum[rt];
  }
  PushDown(rt, rt_ed - rt_st + 1);
  lint mid = (rt_st + rt_ed) >> 1;
  lint tmp_sum = 0;
  if (q_st <= mid) {
    tmp_sum += Query(rt << 1, rt_st, mid, q_st, q_ed);
  }
  if (q_ed > mid) {
    tmp_sum += Query(rt << 1 | 1, mid + 1, rt_ed, q_st, q_ed);
  }
  return tmp_sum;
}

int main(void) {
  lint n = 0;
  lint q_num = 0;
  scanf("%lld%lld", &n, &q_num);
  Build(1, 1, n);
  for (lint q = 0; q < q_num; ++q) {
    lint up_st = 0;
    lint up_ed = 0;
    char op[3] = "";
    scanf("%s%lld%lld", op, &up_st, &up_ed);
    if (op[0] == 'Q') {
      // query
      printf("%lld\n", Query(1, 1, n, up_st, up_ed));
    }
    else {
      // add
      lint add_val = 0;
      scanf("%lld", &add_val);
      Update(1, 1, n, up_st, up_ed, add_val);
    } 
  }
  return 0;
}