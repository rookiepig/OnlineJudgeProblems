///////////////////////////////////////////////////////
// File: main.cpp
// Desc: POJ 1065 Wooden Sticks
//       greedy --> simple sort
// 
// Author: rookiepig
// Date: 2014/04/16
//
///////////////////////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_STICK_NUM 5005
#define MAX_STICK_LEN 10005

typedef struct Stick {
  int len;
  int wgt;
  int max;
} Stick;

Stick stick[MAX_STICK_NUM];
int is_used[MAX_STICK_NUM];
int sort_idx[MAX_STICK_LEN];
int st_num;

int cmp(const void* a, const void* b) {
  Stick* st_a = (Stick*)a;
  Stick* st_b = (Stick*)b;
  if (st_a->len == st_b->len) {
    return  st_a->wgt - st_b->wgt;
  } else {
    return st_a->len - st_b->len;
  }
}
//int GetSetupTime(void) {
//  memset(is_used, 0, st_num * sizeof(is_used[0]));
//  int i = 0;
//  while (true) {
//    // find minimum length
//    int min_max = MAX_STICK_LEN;
//    int min_idx = -1;
//    for (int i = 0; i < st_num; ++i) {
//      if (is_used[i] == 0 && stick[i].max < min_max) {
//        min_max = stick[i].max;
//        min_idx = i;
//      }
//    }
//    if (min_idx == -1) {
//      // all used
//      break;
//    } else {
//      // sort (arrange all possible)
//      
//    }
//  }
//}
void Reorder(void) {
  for (int i = 0; i < st_num; ++i) {
    int cur_len = -1;
    int cur_wgt = -1;
    if (i >= 1) {
      cur_len = stick[i - 1].len;
      cur_wgt = stick[i - 1].wgt;
    }
    int min_max = MAX_STICK_LEN;
    int min_idx = -1;
    for (int j = i; j < st_num; ++j) {
      // find minimum comparable one
      if (stick[j].len >= cur_len && stick[j].wgt >= cur_wgt) {
        if (stick[j].len < min_max) {
          min_max = stick[j].len;
          min_idx = j;
        }
        if (stick[j].len == min_max) {
          if (stick[j].wgt < stick[min_idx].wgt) {
            min_idx = j;
          }
        }
      }
    }
    if (min_idx == -1) {
      min_max = MAX_STICK_LEN;
      for (int j = i; j < st_num; ++j) {
        // find minimum uncomparable one
        if (stick[j].len < min_max) {
          min_max = stick[j].len;
          min_idx = j;
        }
        if (stick[j].len == min_max) {
          if (stick[j].wgt < stick[min_idx].wgt) {
            min_idx = j;
          }
        }
      }
    }
    // swap
    if (min_idx > i) {
      Stick tmp = stick[i];
      stick[i] = stick[min_idx];
      stick[min_idx] = tmp;
    }
  }
}
//void BubbleSort(void) {
//  for (int i = st_num - 1; i >= 0; --i) {
//    for (int j = 0; j < i; ++j) {
//      if (stick[j].len >= stick[j + 1].len && stick[j].wgt >= stick[j + 1].wgt) {
//        // swap
//        Stick tmp = stick[j];
//        stick[j] = stick[j + 1];
//        stick[j + 1] = tmp;
//      }
//    }
//  }
//}
int main(void) {
  int test_case = 0;
  scanf("%d", &test_case);
  while (test_case-- > 0) {
    // input data
    scanf("%d", &st_num);
    for (int i = 0; i < st_num; ++i) {
      scanf("%d%d", &stick[i].len, &stick[i].wgt);
      if (stick[i].len > stick[i].wgt) {
        stick[i].max = stick[i].len;
      } else {
        stick[i].max = stick[i].wgt;
      }
    }
    // sort
    // qsort(stick, st_num, sizeof(stick[0]), cmp);
    Reorder();
    // output
    int setup_time = 1;
    for (int i = 1; i < st_num; ++i) {
      if (stick[i - 1].len > stick[i].len || stick[i - 1].wgt > stick[i].wgt) {
        ++setup_time;
      }
    }
    printf("%d\n", setup_time);
  }
  return 0;
}