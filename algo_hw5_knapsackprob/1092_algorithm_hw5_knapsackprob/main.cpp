//
//  main.cpp
//  1092_algorithm_hw5_knapsackprob
//
//  Created by rogerchang on 2021/5/18.
//

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


vector<vector<int>> data;

int num = 0;
int weight = 0;
int ans = 0;

void readfile() {
  string str;
  str = "input.txt";
  
  ifstream file((string(str)));
  
  if(!file) {
    cout << "fail\n";
  }
  
  int insert = 1;
  file >> num;
  file >> weight;
  cout << num << endl << weight << endl;
  
  file >> insert;
  vector<int> box;
  
  while(insert){
    cout << insert << ' ';
    box.push_back(insert);  //[0]: price
    file >> insert;
    cout << insert << endl; //[1]: weight
    box.push_back(insert);
    
    data.push_back(box);
    box.clear();
    insert = 0;
    file >> insert;
  }
  
  file.close();
}

void writefile(vector<int> selected) {
  
  fstream file;
  file.open("output.txt", ios::trunc | ios::out);
  
  if(!file) {
    cout << "fail\n";
  }
  
  file << ans << endl;
  while (!selected.empty()) {
    file << selected.back() << ' ';
    cout << selected.back() << ' ';
    selected.pop_back();
  }
  cout << endl;
  
  file.close();
}

vector<int> knapsack_dynamic() {
  vector<int> select;
  int *c[num];
  for (int i = 0; i <= num; i++) {
    c[i] = (int *)malloc( (weight+1) * sizeof(int));
  }
  
  for (int i = 1; i <= num; i++) {
    for (int w = 1; w <= weight; w++) {
      c[0][w] = 0;
      if (data[i-1][1] < weight) {
        if ( w-data[i-1][1] > 0) {
          if (c[i-1][w] < data[i-1][0] + c[i-1][w-data[i-1][1]]) {
            c[i][w] = data[i-1][0] + c[i-1][w-data[i-1][1]];
          }
          else {
            c[i][w] = c[i-1][w];
          }
        }
        else if (c[i-1][w] < data[i-1][0] && data[i-1][1] <= w) {
          c[i][w] = data[i-1][0];
        }
        else {
          c[i][w] = c[i-1][w];
        }
        //cout << c[i][w] << " \t";
      }
      else {
        c[i][w] = c[i-1][w];
      }
    }
    //cout << endl;
  }
  
//  for (int i = 0; i <= num; i++) {
//    for (int j = 1; j <= weight; j++) {
//      if (i == 0) {
//        cout << j << " \t";
//      }
//      else {
//        cout << c[i][j] << " \t";
//      }
//    }
//    cout << endl;
//  }
  ans = c[num][weight];
  
  for (int i = num; i > 0; ) {
    for (int j = weight; j > 0; ) {
      if (c[i][j] == c[i-1][j]) {           //it's not been picked
        i--;
      }
      else {                                //it's been picked
        select.push_back(i);
        j-=data[i-1][1];
        i--;
      }
    }
  }
  
  return select;
}




int main(int argc, const char * argv[]) {
  
  readfile();
  
  cout << endl;
  
  
  vector<int> selected = knapsack_dynamic();
  
  cout << ans << endl;
  
  writefile(selected);
  
  return 0;
}
 
