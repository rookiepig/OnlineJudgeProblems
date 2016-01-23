///////////////////////////////////////////////////////
// File: main.c
// Desc: HDU 1166 Segment Tree (no lazy update)
// 
// Author: rookiepig
// Date: 2015/01/15
//
///////////////////////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_N 50005
#define MAX_NODE 4*MAX_N

typedef long long lint;
lint node[MAX_NODE];    // segment tree node
lint a[MAX_N];    // array info

void BuildSegTree(lint root, lint start, lint end) {
  if (start == end) {
    node[root] = a[start];
  }
  else {
    lint mid = start + (end - start) / 2;
    BuildSegTree(root << 1, start, mid);
    BuildSegTree(root << 1 | 1, mid + 1, end);
    // push up sum info to root
    node[root] = node[root << 1] + node[root << 1 | 1];
  }
}

// update one item of a
void UpdateSegTree(lint root, lint start, lint end, lint index, lint delta) {
  if (start == end) {
    node[root] += delta;
    a[index] += delta;
  }
  else {
    lint mid = start + (end - start) / 2;
    if (index <= mid) {
      UpdateSegTree(root << 1, start, mid, index, delta);
    }
    else {
      UpdateSegTree(root << 1 | 1, mid + 1, end, index, delta);
    }
    // update root
    node[root] += delta;
  }
}

lint QuerySegTree(lint root, lint start, lint end, lint left, lint right) {
  if (left <= start && right >= end) {
    return node[root];
  }
  else if (left > end || right < start) {
    return 0;
  }
  else {
    lint mid = start + (end - start) / 2;
    return QuerySegTree(root << 1, start, mid, left, right) +
      QuerySegTree(root << 1 | 1, mid + 1, end, left, right);
  }
}

int main(void) {
  lint test_case = 0;
  scanf("%lld", &test_case);
  for (lint t = 1; t <= test_case; ++t) {
    printf("Case %lld:\n", t);
    lint n = 0;
    scanf("%lld", &n);
    for (lint i = 1; i <= n; ++i) {
      scanf("%lld", a + i);
    }
    // build segment tree
    BuildSegTree(1, 1, n);
    // process command
    char cmd[256] = "";
    while (scanf("%s", cmd) != EOF) {
      lint param1 = 0;
      lint param2 = 0;
      if (strcmp(cmd, "Query") == 0) {
        scanf("%lld%lld", &param1, &param2);
        printf("%lld\n", QuerySegTree(1, 1, n, param1, param2));
      }
      else if (strcmp(cmd, "Add") == 0) {
        scanf("%lld%lld", &param1, &param2);
        UpdateSegTree(1, 1, n, param1, param2);
      }
      else if (strcmp(cmd, "Sub") == 0) {
        scanf("%lld%lld", &param1, &param2);
        UpdateSegTree(1, 1, n, param1, -param2);
      }
      else {
        // end
        break;
      }
    }
  }
  return 0;
}