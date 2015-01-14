#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<cmath>
using namespace std;
int main(void) {
  vector<string> norm_dict;
  vector<string> sort_dict;
  // input
  while (true) {
    string tmp;
    cin >> tmp;
    if (tmp == "XXXXXX") {
      break;
    } else {
      norm_dict.push_back(tmp);
      sort(tmp.begin(), tmp.end());
      sort_dict.push_back(tmp);
    }
  }
  // output
  while (true) {
    string tmp;
    cin >> tmp;
    if (tmp == "XXXXXX") {
      break;
    } else {
      sort(tmp.begin(), tmp.end());
      vector<string> output;
      for (int i = 0; i < norm_dict.size(); ++i) {
        if (sort_dict[i] == tmp) {
          output.push_back(norm_dict[i]);
        }
      }
      if (output.size() > 0) {
        sort(output.begin(), output.end());
        for (int i = 0; i < output.size(); ++i) {
          cout << output[i] << endl;
        }
      } else {
        cout << "NOT A VALID WORD" << endl;
      }
    }
    cout << "******" << endl;
  }
}