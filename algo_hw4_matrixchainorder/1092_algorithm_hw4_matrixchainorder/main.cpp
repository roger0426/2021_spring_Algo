//
//  main.cpp
//  1092_algorithm_hw4_matrixchainorder
//
//  Created by Chang Chung Che on 2021/4/22.
//

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int length;
vector<int> data;
vector<vector<int>> m, s;
string parens;

void printvecvec() {
  
  for (int i = 0; i < length; i++) {
    for (int j = 0; j < length; j++) {
      cout << m[i][j] << "\t\t";
    }
    cout << endl;
  }
  cout << "--------------------------------------\n";
  
  for (int i = 0; i < length; i++) {
    for (int j = 0; j < length; j++) {
      cout << s[i][j] << "\t\t";
    }
    cout << endl;
  }
  cout << "--------------------------------------\n";
}

void inimatrix() {
  for (int i = 0; i <= length; i++) {
    vector<int> in;
    for (int j = 0; j <= length; j++) {
      in.push_back(0);
    }
    m.push_back(in);
    s.push_back(in);
  }
  printvecvec();
}

void readfile() {
  string str;
  str = "input.txt";
  
  ifstream file((string(str)));
  
  if(!file) {
    cout << "fail\n";
  }
  
  int insert = 0, i = 0;
  file >> insert;
  while(insert){
    //cout << insert << endl;
    data.push_back(insert);
    insert = 0;
    file >> insert;
    i++;
  }
  length = i;
  
  file.close();
}

void matrixchainorder() {
  int n = length;
  for (int i = 0; i < n; i++) {
    m[i][i] = 0;
  }
  printvecvec();
  
  for (int l = 1; l < n; l++) {
    for (int i = 1; i < n-l+1; i++) {
      int j = i+l;
      m[i][j] = 10000000;
      cout << "m " << i << ", " << j << endl;
      for (int k = i; k < j; k++) {
        int tmp = m[i][k] + m[k+1][j] + data[i-1]*data[k]*data[j];
        cout << "m" << i << "," << k;
        cout << "\tm" << i << "," << k << endl;
        cout << i-1 << "," << k-1 << "," << j-1 << endl;
        cout << tmp << endl;
        if (tmp < m[i][j]) {
          m[i][j] = tmp;
          s[i][j] = k;
        }
      }
    }
  }
}

void printoptimalparens(int i, int j) {
  if (i == j) {
    cout << " " << "A" << i;
    parens += " A";
    parens += char(i+48);
  }
  else {
    cout << "(";
    parens += "(";
    printoptimalparens(i, s[i][j]);
    printoptimalparens(s[i][j]+1, j);
    cout << ")";
    parens += ")";
  }
}

void writefile() {
  
  fstream file;
  file.open("output.txt", ios::trunc | ios::out);
  
  if(!file) {
    cout << "fail\n";
  }
  
  file << m[1][length-1] << endl;
  file << parens;
  
  file.close();
}


int main(int argc, const char * argv[]) {
  
  readfile();
  
  for (vector<int>::iterator data_i = data.begin(); data_i != data.end(); data_i++) {
    cout << *data_i << endl;
  }
  
  inimatrix();
  printvecvec();
  
  matrixchainorder();
  printvecvec();
  
  printoptimalparens(1, length-1);
  cout << endl << parens;
  
  writefile();
  
  return 0;
}
