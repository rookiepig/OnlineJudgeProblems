////////////////////////////////////////////////////////
// File: POJ2299 Ultra-QuickSort
// Desc: count the inverse number of an array
//       method 1: merge sort
//       method 2: binary indexed trees (not implemented)
// Author: rookiepig
// Date: Date
//
///////////////////////////////////////////////////////


//
// Merge Sort Implementation
// 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LEN 500005
typedef long long lint;
lint a[MAX_LEN];
lint b[MAX_LEN];

lint MergeInv(lint start, lint mid, lint end) {
  lint n = (end - start) + 1;
  lint l_idx = start;
  lint r_idx = mid + 1;
  lint inv_cnt = 0;
  for (lint i = 0; i < n; ++i) {
    if (l_idx > mid) {
      b[i] = a[r_idx++];
      continue;
    }
    if (r_idx > end) {
      b[i] = a[l_idx++];
      continue;
    }
    if (a[l_idx] < a[r_idx]) {
      b[i] = a[l_idx++];
    }
    else {
      b[i] = a[r_idx++];
      inv_cnt += (mid - l_idx) + 1;
    }
  }
  // copy b to a
  memcpy(a + start, b, n * sizeof(b[0]));
  return inv_cnt;
}
lint InvCount(lint start, lint end) {
  if (start >= end) {
    return 0;
  }
  lint mid = start + (end - start) / 2;
  lint l_cnt = InvCount(start, mid);
  lint r_cnt = InvCount(mid + 1, end);
  return l_cnt + r_cnt + MergeInv(start, mid, end);
}

int main(void) {
  lint n;
  while (scanf("%lld", &n) != EOF) {
    if (n == 0) {
      break;
    }
    for (lint i = 0; i < n; ++i) {
      scanf("%lld", a + i);
    }
    printf("%lld\n", InvCount(0, n - 1));
  }

  return 0;
}