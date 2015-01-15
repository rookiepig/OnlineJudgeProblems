///////////////////////////////////////////////////////
// File: main.c
// Desc: HDU 1754 Segment Tree (no lazy update)
// 
// Author: rookiepig
// Date: 2015/01/15
//
///////////////////////////////////////////////////////

#include <cstdio>  
#include <algorithm>  
using namespace std;

#define MAX_N 222222
#define max(a,b)    (((a) > (b)) ? (a) : (b))

typedef int lint;
lint node[MAX_N << 2];    // segment tree node
//lint a[MAX_N];    // array info

void PushUp(lint root) {
  node[root] = max(node[root << 1], node[root << 1 | 1]);
  /*if (node[root << 1] > node[root << 1 | 1]) {
    node[root] = node[root << 1];
  }
  else {
    node[root] = node[root << 1 | 1];
  }*/
}

void BuildSegTree(lint root, lint start, lint end) {
  if (start == end) {
    scanf("%d", node + root);
    return;
  }

  lint mid = (start + end) >> 1;
  BuildSegTree(root << 1, start, mid);
  BuildSegTree(root << 1 | 1, mid + 1, end);
  // push up sum info to root
  PushUp(root);
}

// update one item of a
void UpdateSegTree(lint root, lint start, lint end, lint index, lint new_val) {
  if (start == end) {
    node[root] = new_val;
    return;
  }

  lint mid = (start + end) >> 1;
  if (index <= mid) {
    UpdateSegTree(root << 1, start, mid, index, new_val);
  }
  else {
    UpdateSegTree(root << 1 | 1, mid + 1, end, index, new_val);
  }
  // update root
  PushUp(root);
}

lint QuerySegTree(lint root, lint start, lint end, lint left, lint right) {
  if (left <= start && right >= end) {
    return node[root];
  } else {
    lint mid = (start + end) >> 1;
    lint max_v = -1;
    if (left <= mid) {
      int tmp = QuerySegTree(root << 1, start, mid, left, right);
      if (tmp > max_v) {
        max_v = tmp;
      }
    }
    if (right > mid) {
      int tmp = QuerySegTree(root << 1 | 1, mid + 1, end, left, right);
      if (tmp > max_v) {
        max_v = tmp;
      }
    }
    return max_v;
  }
}

int main(void) {
  lint n = 0;
  lint m = 0;
  while (~scanf("%d%d", &n, &m)) {
    //for (lint i = 1; i <= n; ++i) {
    //  scanf("%d", a + i);
    //}
    // build segment tree
    BuildSegTree(1, 1, n);
    // process command
    while (m--) {
      char cmd[2] = "";
      lint param1 = 0;
      lint param2 = 0;
      scanf("%s%d%d", cmd, &param1, &param2);
      if (cmd[0] == 'Q') {
        printf("%d\n", QuerySegTree(1, 1, n, param1, param2));
      } else {
        // param2 -= a[param1];
        UpdateSegTree(1, 1, n, param1, param2);
      }
    }
  }
  return 0;
}



//
// 非常诡异，你的code TLE， 博客里的code就可以过
//
//#include <cstdio>  
//#include <algorithm>  
//using namespace std;
//
//#define lson l , m , rt << 1  
//#define rson m + 1 , r , rt << 1 | 1  
//const int maxn = 222222;
//int MAX[maxn << 2];
//void PushUP(int rt) {
//  MAX[rt] = max(MAX[rt << 1], MAX[rt << 1 | 1]);
//}
//void build(int l, int r, int rt) {
//  if (l == r) {
//    scanf("%d", &MAX[rt]);
//    return;
//  }
//  int m = (l + r) >> 1;
//  build(lson);
//  build(rson);
//  PushUP(rt);
//}
//void update(int p, int sc, int l, int r, int rt) {
//  if (l == r) {
//    MAX[rt] = sc;
//    return;
//  }
//  int m = (l + r) >> 1;
//  if (p <= m) update(p, sc, lson);
//  else update(p, sc, rson);
//  PushUP(rt);
//}
//int query(int L, int R, int l, int r, int rt) {
//  if (L <= l && r <= R) {
//    return MAX[rt];
//  }
//  int m = (l + r) >> 1;
//  int ret = 0;
//  if (L <= m) ret = max(ret, query(L, R, lson));
//  if (R > m) ret = max(ret, query(L, R, rson));
//  return ret;
//}
//int main() {
//  int n, m;
//  while (~scanf("%d%d", &n, &m)) {
//    build(1, n, 1);
//    while (m--) {
//      char op[2];
//      int a, b;
//      scanf("%s%d%d", op, &a, &b);
//      if (op[0] == 'Q') printf("%d\n", query(a, b, 1, n, 1));
//      else update(a, b, 1, n, 1);
//    }
//  }
//  return 0;
//}