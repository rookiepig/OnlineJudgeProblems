///////////////////////////////////////////////////////
// File: main.cpp
// Desc: POJ 2374 Fence Obstacle Course
//       DP + max segment tree
// Author: rookiepig
// Date: 2014/01/23
//
///////////////////////////////////////////////////////


#include<cstdio>
#include<algorithm>
using namespace std;

struct Fence {
  int L;    // left and right end of fence
  int R;
};

#define MAX_FENCE 50005
#define MAX_DIS 100005
Fence fence[MAX_FENCE];
Fence dp[MAX_FENCE];
int sg_tree[MAX_DIS << 3];    // default init to zero
int lazy[MAX_DIS << 3];       // lazy update

void PushUp(int rt) {
  sg_tree[rt] = max(sg_tree[rt << 1], sg_tree[rt << 1 | 1]);
}
void PushDown(int rt) {
  sg_tree[rt << 1] = sg_tree[rt << 1 | 1] = lazy[rt];
  lazy[rt << 1] = lazy[rt << 1 | 1] = lazy[rt];
  lazy[rt] = 0;
}
int Query(int rt, int st, int ed, int pos) {
  if (st == ed) {
    return sg_tree[rt];
  }
  if (lazy[rt]) {
    PushDown(rt);
  }
  int mid = (st + ed) >> 1;
  if (pos <= mid) {
    return Query(rt << 1, st, mid, pos);
  }
  else {
    return Query(rt << 1 | 1, mid + 1, ed, pos);
  }
}
void Update(int rt, int st, int ed, int up_st, int up_ed, int val) {
  if (up_st <= st && up_ed >= ed) {
    sg_tree[rt] = val;
    lazy[rt] = val;
    return;
  }
  if (lazy[rt]) {
    PushDown(rt);
  }
  int mid = (st + ed) >> 1;
  if (up_st <= mid) {
    Update(rt << 1, st, mid, up_st, up_ed, val);
  }
  if (up_ed > mid) {
    Update(rt << 1 | 1, mid + 1, ed, up_st, up_ed, val);
  }
  PushUp(rt);
}
int DPMin(int i, int pos) {
  if (i) {
    return min(dp[i].L + pos - fence[i].L, dp[i].R + fence[i].R - pos);
  }
  else {
    // 0 level can go direct to original point
    return abs(pos - MAX_DIS);
  }
}
int main(void) {
  int N = 0;
  int S = 0;
  scanf("%d%d", &N, &S);
  S += MAX_DIS;
  for (int i = 1; i <= N; ++i) {
    scanf("%d%d", &fence[i].L, &fence[i].R);
    fence[i].L += MAX_DIS;
    fence[i].R += MAX_DIS;
    dp[i].L = DPMin(Query(1, 0, 2 * MAX_DIS, fence[i].L), fence[i].L);
    dp[i].R = DPMin(Query(1, 0, 2 * MAX_DIS, fence[i].R), fence[i].R);
    Update(1, 0, 2 * MAX_DIS, fence[i].L, fence[i].R, i);
  }
  printf("%d\n", min(S - fence[N].L + dp[N].L, fence[N].R - S + dp[N].R));
  return 0;
}