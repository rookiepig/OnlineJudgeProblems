///////////////////////////////////////////////////////
// File: main.cpp
// Desc: POJ 2479 Maximum Sum
//       find maximum two long subsequence sum
//       DP !!!! longest subsequence sum
// Author: rookiepig
// Date: 2014/04/12
//
///////////////////////////////////////////////////////

#include<iostream>
#include<fstream>
#include<streambuf>
//#include<cstdint>
#define USE_SCANF
typedef long long int64_t;

using namespace std;
const int64_t kMaxLen = 50001;
const int64_t kMinInt = -60000001000;
const int64_t kMaxInt = 60000901000;
int64_t lower_max[kMaxLen] = { 0 };
int64_t cum_sum[kMaxLen] = { 0 };
int64_t upper_max[kMaxLen] = { 0 };
int64_t val[kMaxLen] = { 0 };

void LowerMax(const int64_t len) {
  int64_t max_sub = 0;
  max_sub = lower_max[0] = cum_sum[0] = val[0];
  for (int64_t i = 1; i < len; ++i) {
    if (cum_sum[i - 1] > 0) {
      cum_sum[i] = cum_sum[i - 1] + val[i];
    }
    else {
      cum_sum[i] = val[i];
    }
    if (cum_sum[i] > max_sub) {
      max_sub = cum_sum[i];
    }
    lower_max[i] = max_sub;
  }
}
void UpperMax(const int64_t len) {
  int64_t max_sub = 0;
  max_sub = upper_max[len - 1] = cum_sum[len - 1] = val[len - 1];
  for (int64_t i = len - 2; i >= 0; --i) {
    if (cum_sum[i + 1] > 0) {
      cum_sum[i] = cum_sum[i + 1] + val[i];
    }
    else {
      cum_sum[i] = val[i];
    }
    if (cum_sum[i] > max_sub) {
      max_sub = cum_sum[i];
    }
    upper_max[i] = max_sub;
  }
}

int64_t FindMaxSum(const int64_t len) {
  int64_t all_max = kMinInt;
  // find lower and upper max subsequence sum 
  LowerMax(len);
  UpperMax(len);
  for (int64_t j = 0; j < len - 1; ++j) {
    int64_t lu_sum = lower_max[j] + upper_max[j + 1];
    if (lu_sum > all_max) {
      all_max = lu_sum;
    }
  }
  return all_max;
}

int main(void)
{
#ifdef _DEBUG
  // redirect file stream to cin
  fstream file_in("in.txt");
  streambuf* cinBuf = cin.rdbuf();
  cin.rdbuf(file_in.rdbuf());
#endif
  int64_t test_num = 0;
#ifdef USE_SCANF
  scanf("%d", &test_num);
#else
  cin >> test_num;
#endif
  while (test_num > 0) {
    int64_t input_len = 0;
    // input data sequence
#ifdef USE_SCANF
    scanf("%lld", &input_len);
    for (int64_t i = 0; i < input_len; ++i) {
      scanf("%lld", &val[i]);
    }
#else
    cin >> input_len;
    for (int64_t i = 0; i < input_len; ++i) {
      cin >> val[i];
    }
#endif
    cout << FindMaxSum(input_len) << endl;
    --test_num;
  }
  
#ifdef _DEBUG
  // restore cin buf
  cin.rdbuf(cinBuf);
#endif
  return 0;
}