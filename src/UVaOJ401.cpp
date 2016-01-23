// Palindromes
#include<iostream>
#include<string>
#include<map>
using namespace std;

bool IsPal(const string str) {
  for (int i = str.size() - 1, j = 0; i >= 0 && i >= j; --i, ++j) {
    if (str[i] != str[j]) {
      return false;
    }
  }
  return true;
}

bool IsMirr(const string str, const map<char, char>& tab) {
  for (int i = str.size() - 1, j = 0; i >= 0 && i >= j; --i, ++j) {
    if (tab.find(str[j]) == tab.end()) {
      return false;
    } else {
      if (str[i] != tab.find(str[j])->second) {
        return false;
      }
    }
  }
  return true;
}
int main(void) {
  string input = "";
  map<char, char> reverse_tab;
  // 1st col
  reverse_tab['A'] = 'A'; reverse_tab['E'] = '3'; reverse_tab['H'] = 'H';
  reverse_tab['I'] = 'I'; reverse_tab['J'] = 'L'; reverse_tab['L'] = 'J';
  // 2nd col
  reverse_tab['M'] = 'M'; reverse_tab['O'] = 'O'; reverse_tab['S'] = '2';
  reverse_tab['T'] = 'T'; reverse_tab['U'] = 'U'; reverse_tab['V'] = 'V';
  reverse_tab['W'] = 'W'; reverse_tab['X'] = 'X';
  // 3rd col
  reverse_tab['Y'] = 'Y'; reverse_tab['Z'] = '5'; reverse_tab['1'] = '1';
  reverse_tab['2'] = 'S'; reverse_tab['3'] = 'E'; reverse_tab['5'] = 'Z'; reverse_tab['8'] = '8';
  while (cin >> input) {
    bool is_pal = false;
    bool is_mirr = false;
    is_pal = IsPal(input);
    is_mirr = IsMirr(input, reverse_tab);
    if (!is_pal && !is_mirr) {
      cout << input << " -- is not a palindrome." << endl;
    }
    else if (is_pal && !is_mirr) {
      cout << input << " -- is a regular palindrome." << endl;
    }
    else if (!is_pal && is_mirr) {
      cout << input << " -- is a mirrored string." << endl;
    }
    else  {
      cout << input << " -- is a mirrored palindrome." << endl;
    }
    cout << endl;
  }
}