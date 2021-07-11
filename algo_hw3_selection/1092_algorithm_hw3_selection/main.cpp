//
//  main.cpp
//  1092_algorithm_hw3_selection
//
//  Created by Chang Chung Che on 2021/4/12.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int datasize, target;

vector<int> readfile() {
    string str;
    //cout << "insert file name:";
    //cin >> str;
    str = "input.txt";
    
    ifstream file((string(str)));
    
    if(!file) {
        cout << "fail\n";
    }
    
    vector<int> data;
    
    file >> datasize;
    file >> target;
    cout << "size:\t" << datasize << endl << "target:\t" << target << endl << "-------\n";
    //data.push_back(datasize);
    //data.push_back(target);
    
    
    //cout << "size:" << size << endl;
    
    for (int i = 0; i < datasize; i ++) {
        int insert;
        file >> insert;
        //cout << insert << endl;
        data.push_back(insert);
    }
    file.close();
    return data;
}

vector<vector<int>> dividedata(vector<int> data) {
    vector<vector<int>> datagroup;
    vector<int> array;
    
    for (int i = 0; i < int(data.size()); i++) {
        cout << data[i] << "\t";
    }
    cout << endl;
    
    for (int i = 0; i < int(data.size()); i++) {
        if (array.size() == 5) {
            datagroup.push_back(array);
            array.clear();
        }
        array.push_back(data[i]);
    }
    if (!array.empty()) {
        datagroup.push_back(array);
    }
    return datagroup;
}

vector<vector<int>> partitiondata(vector<int> data, int key) {
    vector<vector<int>> r;
    vector<int> frontarray;
    vector<int> backarray;
    int size = int(data.size());
    
    for (int i = 0; i < size; i++) {
        if (data[i] < key) {
            frontarray.push_back(data[i]);
        }
        else if (data[i] > key) {
            backarray.push_back(data[i]);
        }
    }
    
    r.push_back(frontarray);
    r.push_back(backarray);
    
    return r;
}

vector<int> insertsort(vector<int> data, int s) {
    for (int i = 1; i < s; i ++) {
        int key = data[i];
        int j = i - 1;
        while (j >= 0 && key < data[j]) {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = key;
    }
    return data;
}

int findmedian(vector<int> data) {
    int median = 0;
    
    data = insertsort(data, int(data.size()));
    
    median = data[int(data.size() + 1) / 2 - 1];
    
    cout << "*" << median << "*\n";
    
    return median;
}

int select(vector<int> data, int fnum, int bnum) {
    cout << "--------------------------------\n";
    int targetnum = 0;
    int median_median = 0;
    vector<vector<int>> datagroup = dividedata(data);
    vector<int> mediumgroup;
    vector<int> newdata;
    
    int r = int(data.size());
    for (int i = 0; i < int(data.size())/5 + 1; i++) {
        
        int t = 0;
        for (int j = 0; j < 5 ; j++) {
            if (r) {
                cout << datagroup[i][j] << "\t";
                r--;
                t = 1;
            }
        }
        if (t) {
            mediumgroup.push_back(findmedian(datagroup[i]));
        }
        cout << endl;
    }
    
    median_median = findmedian(mediumgroup);
    
    vector<vector<int>> d;
    d = partitiondata(data, median_median);
    vector<int> fdata = d[0];
    vector<int> bdata = d[1];
    
    
    int curr = fnum + int(fdata.size()) + 1;
    
    cout << "fnum:\t" << fnum << "bnum:\t" << bnum << "curr:\t" << curr << endl;
    
    if (curr == target) {
        targetnum = median_median;
        //cout << "find target !! answer is:\t" << data[];
    }
    else if (curr < target) {           //target is bigger, recursive back array
        fnum ++;
        fnum += fdata.size();
        targetnum = select(bdata, fnum, bnum);
    }
    else if (target < curr) {           //target is smaller, recursive front array
        bnum ++;
        bnum += bdata.size();
        targetnum = select(fdata, fnum, bnum);
    }
    return  targetnum;
}

void writefile(int ans) {
    
    //trunc: clear the file first
    fstream file;
    file.open("output.txt", ios::trunc | ios::out);
    
    if(!file) {
        cout << "fail\n";
    }
    
    file << datasize << endl << target << endl;
    file << ans;
    
    file.close();
}

int main(int argc, const char * argv[]) {
    
    vector<int> insertdata = readfile();
    
    for (int i = 0; i < datasize; i++) {
        //cout << insertdata[i] << endl;
    }
    
    int fnum = 0, bnum = 0;
    int ans = select(insertdata, fnum, bnum);
    
    writefile(ans);
    
    return 0;
}
