///////////////////////////////////////////////////////
// File: main.cpp
// Desc: POJ 2528 Mayor's posters
//       segment tree + descritization + lazy update
//       many good implementation skills
// Author: rookiepig
// Date: 2015/01/18
//
///////////////////////////////////////////////////////

#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int MAX_N = 100005;
const int NO_VAL = -1;

int st[MAX_N];
int ed[MAX_N];
int ext_loc[MAX_N << 2];
int node[MAX_N << 4];    // order of the segment
bool is_used[MAX_N];     // whether ith order can be seen
int order_cnt = 0;

void PushDown(int rt) {
  if (node[rt] != NO_VAL) {
    node[rt << 1] = node[rt << 1 | 1] = node[rt];
    node[rt] = NO_VAL;
  }
}
void Update(int rt, int rt_st, int rt_ed, int up_st, int up_ed, int order) {
  if (up_st <= rt_st && up_ed >= rt_ed) {
    node[rt] = order;
    return;
  }
  PushDown(rt);
  int mid = (rt_st + rt_ed) >> 1;
  if (up_st <= mid) {
    Update(rt << 1, rt_st, mid, up_st, up_ed, order);
  }
  if (up_ed > mid) {
    Update(rt << 1 | 1, mid + 1, rt_ed, up_st, up_ed, order);
  }
}
void Query(int rt, int rt_st, int rt_ed) {
  if (node[rt] != NO_VAL) {
    if (!is_used[node[rt]]) {
      ++order_cnt;
      is_used[node[rt]] = true;
    }
    return;
  }
  if (rt_st == rt_ed) {
    return;
  }
  int mid = (rt_st + rt_ed) >> 1;
  Query(rt << 1, rt_st, mid);
  Query(rt << 1 | 1, mid + 1, rt_ed);
}
int BinarySearch(int target, int size) {
  int left = 0;
  int right = size - 1;
  while (left <= right) {
    int mid = (left + right) >> 1;
    if (ext_loc[mid] == target) {
      return mid;
    }
    if (ext_loc[mid] < target) {
      left = mid + 1;
    }
    else {
      right = mid - 1;
    }
  }
  return NO_VAL;
}

int main(void) {
  int test_case = 0;
  scanf("%d", &test_case);
  while (test_case--) {
    // initial segment tree node
    memset(node, NO_VAL, sizeof(node));
    int n = 0;
    scanf("%d", &n);
    int ext_size = 0;
    for (int i = 0; i < n; ++i) {
      scanf("%d%d", st + i, ed + i);
      ext_loc[ext_size++] = st[i];
      ext_loc[ext_size++] = ed[i];
    }
    // remove duplicate
    // good implementations
    sort(ext_loc, ext_loc + ext_size);
    int new_size = 1;
    for (int i = 1; i < ext_size; ++i) {
      if (ext_loc[i] != ext_loc[i - 1]) {
        ext_loc[new_size++] = ext_loc[i];
      }
    }
    // add split value
    // good implementations
    for (int i = new_size - 1; i > 0; --i) {
      if (ext_loc[i] != ext_loc[i - 1] + 1) {
        ext_loc[new_size++] = ext_loc[i - 1] + 1;
      }
    }
    sort(ext_loc, ext_loc + new_size);
    // update segment tree
    for (int i = 0; i < n; ++i) {
      int st_loc = BinarySearch(st[i], new_size);
      int ed_loc = BinarySearch(ed[i], new_size);
      Update(1, 0, new_size - 1, st_loc, ed_loc, i);
    }
    // query and add order count
    memset(is_used, false, sizeof(is_used));
    order_cnt = 0;
    Query(1, 0, new_size - 1);
    printf("%d\n", order_cnt);
  }
  return 0;
}