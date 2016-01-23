///////////////////////////////////////////////////////
// File: main.c
// Desc: POJ 3264 Segment Tree (no lazy update)
// 
// Author: rookiepig
// Date: 2015/01/16
//
///////////////////////////////////////////////////////

#include<cstdio>
#include<algorithm>
using namespace std;

#define MAX_N 50005
#define MAX_V 1000005
#define MAX_NODE 4*MAX_N

typedef long long lint;
lint min_node[MAX_NODE];    // segment tree node
lint max_node[MAX_NODE];    // segment tree node
lint a[MAX_N];    // array info

void BuildSegTree(lint root, lint start, lint end) {
  if (start == end) {
    min_node[root] = a[start];
    max_node[root] = a[start];
  }
  else {
    lint mid = start + (end - start) / 2;
    BuildSegTree(root << 1, start, mid);
    BuildSegTree(root << 1 | 1, mid + 1, end);
    // push up sum info to root
    max_node[root] = max(max_node[root << 1], max_node[root << 1 | 1]);
    min_node[root] = min(min_node[root << 1], min_node[root << 1 | 1]);
  }
}

// update one item of a
//void UpdateSegTree(lint root, lint start, lint end, lint index, lint delta) {
//  if (start == end) {
//    node[root] += delta;
//    a[index] += delta;
//  }
//  else {
//    lint mid = start + (end - start) / 2;
//    if (index <= mid) {
//      UpdateSegTree(root << 1, start, mid, index, delta);
//    }
//    else {
//      UpdateSegTree(root << 1 | 1, mid + 1, end, index, delta);
//    }
//    // update root
//    node[root] += delta;
//  }
//}

void QuerySegTree(lint root, lint start, lint end, lint left, lint right,
  lint& max_v, lint& min_v) {
  if (left <= start && right >= end) {
    max_v = max_node[root];
    min_v = min_node[root];
  } else {
    lint mid = start + (end - start) / 2;
    lint tmp_max = - 1;
    lint tmp_min = MAX_V;
    if (left <= mid) {
      QuerySegTree(root << 1, start, mid, left, right, tmp_max, tmp_min);
      max_v = max(max_v, tmp_max);
      min_v = min(min_v, tmp_min);
    }
    if (right > mid) {
      QuerySegTree(root << 1 | 1, mid + 1, end, left, right, tmp_max, tmp_min);
      max_v = max(max_v, tmp_max);
      min_v = min(min_v, tmp_min);
    }
  }
}

int main(void) {

  lint n = 0;
  lint q = 0;
  scanf("%lld%lld", &n, &q);
  for (lint i = 1; i <= n; ++i) {
    scanf("%lld", a + i);
  }
  // build segment tree
  BuildSegTree(1, 1, n);
  for (int i = 0; i < q; ++i) {
    lint left = 0;
    lint right = 0;
    scanf("%ld%ld", &left, &right);
    lint max_v = - 1;
    lint min_v = MAX_V;
    QuerySegTree(1, 1, n, left, right, max_v, min_v);
    printf("%lld\n", max_v - min_v);
  }
  return 0;
}