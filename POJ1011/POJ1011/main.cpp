////////////////////////////////////////////////////////
// File: POJ1011 Sticks
// Desc: exautive search + pruning
//       two key points:
//       1) do not search same length
//       2) if first unused stick can not form one, then
//          no need to search others, since this stick 
//          must be used once
// 
// Author: rookiepig
// Date: Date
//
///////////////////////////////////////////////////////


#include<iostream>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<fstream>
#include<streambuf>
#include<algorithm>
#include<functional>
#include<cmath>
#ifdef _DEBUG
#include<Windows.h>
#endif
using namespace std;

const int kMaxStickNum = 65;
const int kMaxStickLen = 51;
int g_stick[kMaxStickNum];                    // global stick len
int g_st_used[kMaxStickNum];                  // global stick used flag
                                              // 0 -> unused, 1 -> used
int g_st_num = 0;                             // global stick number
int g_st_sum = 0;                             // global stick len sum
int g_st_max = 0;                             // global maximum stick length


bool DFSSearch(int remain_merge_num, const int& cur_st, const int& merge_len, const int& find_len) {
  if (remain_merge_num == 0) {
    return true;
  } else {
    for (int s = cur_st; s < g_st_num; ++s) {
      if (g_st_used[s] || g_stick[s] > find_len) {
        continue;
      }
      // find unused stick
      g_st_used[s] = 1;
      bool is_success = false;
      if (g_stick[s] < find_len) {
        // current merge
        is_success = DFSSearch(remain_merge_num, s + 1, merge_len, find_len - g_stick[s]);
      } else {
        // new merge
        is_success = DFSSearch(remain_merge_num - 1, 0, merge_len, merge_len);
      }
      if (is_success) {
        return true;
      } else {
        // backtrack
        g_st_used[s] = 0;
        if (find_len == merge_len) {
          // first stick of new merge
          return false;
        }
        // jump to different length
        for (++s; s < g_st_num; ++s) {
          if (g_stick[s] != g_stick[s - 1]) {
            --s;
            break;
          }
        }
      } 
    } // end for each unused stick

    return false;
  } // end if-else
}
int main(void)
{
#ifdef _DEBUG
  // redirect file stream to cin
  fstream fIn("in.txt");
  streambuf* cinBuf = cin.rdbuf();
  cin.rdbuf(fIn.rdbuf());
#endif
  while (true) {
    //
    // input data
    //
    cin >> g_st_num;
    if (g_st_num == 0) {
      break;
    }
    // re-init global variables
    g_st_max = -1;
    g_st_sum = 0;
    for (int i = 0; i < g_st_num; ++i) {
      cin >> g_stick[i];
      g_st_sum += g_stick[i];
      if (g_stick[i] > g_st_max) {
        g_st_max = g_stick[i];
      }
    }
#ifdef _DEBUG
    // record time
    double duration = static_cast<double>(GetTickCount());
#endif
    // sort g_st_len
    sort(g_stick, g_stick + g_st_num, greater<int>());
    // enumerate all possible merge length
    for (int merge_len = 1; merge_len <= g_st_sum; ++merge_len) {
      if (merge_len >= g_st_max && (g_st_sum % merge_len == 0)) {
        int merge_num = g_st_sum / merge_len;
        // re-init used flag
        fill(g_st_used, g_st_used + g_st_num, 0);
        // DFS search
        if (DFSSearch(merge_num, 0, merge_len, merge_len)) {
          cout << merge_len << endl;
          break;
        }
      }
    } // end for merege_len
#ifdef _DEBUG
    // record time
    cout  << "run time: " << (static_cast<double>(GetTickCount()) - duration)
      << " (ms)\n";
#endif
  }
#ifdef _DEBUG
  // restore cin buf
  cin.rdbuf(cinBuf);
#endif
  return 0;
}