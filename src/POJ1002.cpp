#include<vector>
#include<iostream>
#include<algorithm>
#include<string>
#include<map>
using namespace std;
typedef unsigned int uint;

const int CUT_OFF = 10;
template<class T>
void Swap(T& a, T&b) {
  T tmp = a;
  a = b;
  b = tmp;
}
template<class T>
void InsertSort(vector<T>& A, const int start, const int end) {
  for (int i = start + 1; i <= end; ++i) {
    T tmp = A[i];
    int j = i;
    for (; j > 0 && A[j - 1] > tmp; --j) {
      A[j] = A[j - 1];
    }
    A[j] = tmp;
  }
}
template<class T>
T Median3(vector<T>& A, const int start, const int end) {
  int mid = start + (end - start) / 2;
  if (A[start] > A[end]) {
    Swap(A[start], A[end]);
  }
  if (A[start] > A[mid]) {
    Swap(A[start], A[mid]);
  }
  if (A[mid] > A[end]) {
    Swap(A[mid], A[end]);
  }
  Swap(A[mid], A[end - 1]);
  return A[end - 1];
}
template<class T>
void QuickSort(vector<T>& A, const int start, const int end) {
  if (end - start >= CUT_OFF) {
    T pivot = Median3(A, start, end);
    int i = start;
    int j = end - 1;
    while (true) {
      while (A[++i] < pivot);
      while (A[--j] > pivot);
      if (i > j) {
        break;
      } else {
        Swap(A[i], A[j]);
      }
    }
    Swap(A[i], A[end - 1]);
    QuickSort(A, start, i - 1);
    QuickSort(A, i + 1, end);
  } else {
    InsertSort(A, start, end);
  }
}
map<char, uint> ch_to_int;
void GenerateMap(void) {
  for (char ch = 'A'; ch <= 'Z'; ++ch) {
    if (ch <= 'O') {
      ch_to_int[ch] = (uint)(2 + (ch - 'A') / 3);
    } else {
      switch (ch) {
      case 'P':
      case 'R':
      case 'S':
        ch_to_int[ch] = 7;
        break;
      case 'T' :
      case 'U' :
      case 'V' :
        ch_to_int[ch] = 8;
        break;
      case 'W' :
      case 'X' :
      case 'Y' :
        ch_to_int[ch] = 9;
        break;
      default:
        ch_to_int[ch] = 0;
        break;
      }
    }
  }
}
uint StrToUINT(const string& str) {
  uint val = 0;
  uint base = 1;
  for (int i = str.size() - 1; i >= 0; --i) {
    if (str[i] >= '0' && str[i] <= '9') {
      val += base * (str[i] - '0');
      base *= 10;
    } else if (str[i] != '-' && str[i] != 'Q' && str[i] != 'Z') {
      val += base * ch_to_int[str[i]];
      base *= 10;
    }
  }
  return val;
}
string UINTToStr(uint val) {
  string str(8, '-');
  for (int i = 7; i >= 0; --i) {
    if (i == 3) {
      continue;
    } else {
      str[i] = '0' + val % 10;
      val /= 10;
    }
  }
  return str;
}
int main(void) {
  vector<uint> A;
  GenerateMap();
  int len = 0;
  cin >> len;
  string tmp = "";
  for (int i = 0; i < len; ++i) {
    cin >> tmp;
    A.push_back(StrToUINT(tmp));
  }
  QuickSort<uint>(A, 0, A.size() - 1);
  int has_dup = false;
  for (int i = 0, cnt = 0; i < A.size();) {
    cnt = 0;
    for (int j = i; j < A.size(); ++j) {
      if (A[j] != A[i]) {
        break;
      }
      else {
        ++cnt;
      }
    }
    if (cnt > 1) {
      has_dup = true;
      cout << UINTToStr(A[i]) << " " << cnt << endl;
    }
    i += cnt;
  }
  if (!has_dup) {
    cout << "No duplicates." << endl;
  }
  return 0;
}