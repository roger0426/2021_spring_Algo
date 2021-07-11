//
//  main.cpp
//  1092_algorithm_hw1_mergesort
//
//  Created by Chang Chung Che on 2021/3/27.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int size;

void randfile(int s) {
    
    srand((unsigned int)time(NULL));
    
    string str;
    str = "input.txt";
    
    //trunc: clear the file first
    fstream file;
    file.open(str, ios::trunc | ios::out);
    
    if(!file) {
        cout << "fail\n";
    }
    
    file << s << endl;
    
    for (int i = 0; i < s; i ++) {
        int p = rand() % 2;
        if (p == 0) {
            file << rand() % 10000 << endl;
        }
        else {
            file << -rand() % 10000 << endl;
        }
    }
    file.close();
}

vector<vector<int>> fewrandfile(int s, int r) {
    
    srand((unsigned int)time(NULL));
    
    string str;
    str = "input.txt";
    
    //trunc: clear the file first
    fstream file;
    file.open(str, ios::trunc | ios::out);
    
    if(!file) {
        cout << "fail\n";
    }
    
    vector<int> array;
    
    array.push_back(s);
    
    file << s << endl;
    for (int i = 0; i < s; i ++) {
        array.push_back(i+1);
    }
    
    r = r / 2;
    for (int i = 0; i < r; i ++) {
        int a = rand() % s;
        int b = rand() % s;
        int tmp = array[a];
        array[a] = array[b];
        array[b] = tmp;
    }
    
    vector<vector<int>> data;
    for (int i = 0; i < s; i ++) {
        vector<int> box;
        box.push_back(i+1);
        box.push_back(array[i]);
        data.push_back(box);
    }
    
    file.close();
    return data;
}

vector<vector<int>> readfile() {
    string str;
    //cout << "insert file name：";
    //cin >> str;
    str = "input.txt";
    
    ifstream file((string(str)));
    
    if(!file) {
        cout << "fail\n";
    }
    
    vector<vector<int>> data;
    
    file >> size;
    
    //cout << "size:" << size << endl;
    
    for (int i = 0; i < size; i ++) {
        int insert = 0;
        vector<int> box;
        file >> insert;
        
        box.push_back(i+1);
        box.push_back(insert);
        
        data.push_back(box);
    }
    file.close();
    return data;
}

vector<vector<int>> mergesort(vector<vector<int>> data, int s) {
    vector<vector<int>> sorted;
    
    vector<vector<int>> list1;
    vector<vector<int>> list2;
    
    int size1 = 0, size2 = 0;
    size1 = (s+1)/2;
    size2 = s/2;
    //keep mergesort
    if(s == 1) {
        return data;
    }
    else if (s >= 2) {
        //split to two vector
        for (int i = 0; i < size1; i ++) {
            list1.push_back(data[i]);
        }
        for (int i = 0; i < size2; i ++) {
            list2.push_back(data[i + size1]);
        }
        
        list1 = mergesort(list1, size1);
        list2 = mergesort(list2, size2);
    }
    
    //if length <= 2, merge
    //merge two vector
    //small first
    
    int a = 0, b = 0;
    for (int i = 0; i < s; i ++) {
        if (a >= size1) {
            sorted.push_back(list2[b]);
            b++;
        }
        else if (b >= size2) {
            sorted.push_back(list1[a]);
            a++;
        }
        else if (list1[a][1] >= list2[b][1]) {
            sorted.push_back(list2[b]);
            b++;
        }
        else if (list1[a][1] < list2[b][1]) {
            sorted.push_back(list1[a]);
            a++;
        }
        else {
            cout << "error\n";
        }
    }
    return sorted;
}

vector<vector<int>> insertsort(vector<vector<int>> data, int s) {
    for (int i = 1; i < s; i ++) {
        vector<int> keyv = data[i];
        int key = data[i][1];
        int j = i - 1;
        while (j >= 0 && key < data[j][1]) {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = keyv;
    }
    return data;
}

vector<vector<int>> quicksort(vector<vector<int>> data, int s, int k) {
    演算法有誤
    if (s <= k) {
        data = insertsort(data, s);
        return data;
    }
    
    //vector<int> pvec = data[0];
    //int pnum = data[0][1];
    
    vector<int> pvec = data[s/2];
    int pnum = data[s/2][1];
    
    vector<vector<int>> data1;
    vector<vector<int>> data2;
    vector<vector<int>> tmp;
    int a = 0, b = 0;
    for (int i = 1; i < s; i ++) {
        if (data[i][1] == pnum) {
            tmp.push_back(data[i]);
        }
        else if (data[i][1] < pnum) {
            data1.push_back(data[i]);
            a++;
        }
        else if (data[i][1] > pnum) {
            data2.push_back(data[i]);
            b++;
        }
    }
    
    data1 = quicksort(data1, a, k);
    data2 = quicksort(data2, b, k);
    
    data.clear();
    
    data.insert(data.end(), data1.begin(), data1.end());
    data.insert(data.end(), tmp.begin(), tmp.end());
    data.push_back(pvec);
    data.insert(data.end(), data2.begin(), data2.end());
    
    if (data.size() != s) {
        cout << "error\n";
    }
    
    return data;
}

void writefile(vector<vector<int>> data, int s, string str) {
    
    //trunc: clear the file first
    fstream file;
    file.open(str, ios::trunc | ios::out);
    
    if(!file) {
        cout << "fail\n";
    }
    
    file << s << endl;
    for (int i = 0; i < s; i ++) {
        file << data[i][1] << endl;
    }
    file.close();
}

int main(int argc, const char * argv[]) {
    
    vector<vector<int>> data;
    vector<vector<int>> sorted;
    
    
    int inputsize = 10000;
    float testtime = 5;
    int fewrnum = 200;
    int k = 2500;
    
    string randkind;
    
    //print original data
    //cout << "original:\n";
//    for (int i = 0; i < size; i ++) {
//        cout << data[i][0] << "    " << data[i][1] << endl;
//    }
    
    double mstime = 0, istime = 0, qstime = 0, qsktime = 0;
    
    
    int num = inputsize;
    for (int i = 0; i < testtime; i ++) {
        //cout << "--------" << i << "--------";
        //num -= inputsize / testtime;
        
        //generate random input
        //randfile(num);
        //randkind = "fully random";
        
        //generate few random input
        data = fewrandfile(num, fewrnum);
        writefile(data, num, "input.txt");
        randkind = "partly random";
        
        //read file from input.txt
        data = readfile();
        
        
        clock_t start, end;
        
        //cout << "CPU Time:\n";
        //sort data
        start = clock();
        sorted = mergesort(data, size);
        end = clock();
        double mergesort_cputime = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "merge sort: \t\t" << mergesort_cputime << " s\n";
        mstime += mergesort_cputime;
        
        //insert sort
        start = clock();
        sorted = insertsort(data, size);
        end = clock();
        double insertsort_cputime = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "insert sort: \t\t" << insertsort_cputime << " s\n";
        istime += insertsort_cputime;
        
        double quicksort_cputime;
        //quick sort
        start = clock();
        sorted = quicksort(data, size, 1);
        end = clock();
        quicksort_cputime = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "quick sort: \t\t" << quicksort_cputime << " s\n";
        qstime += quicksort_cputime;
        
        int v = k;
        
        //for (int j = 0; j < 10; j ++) {
        //    v -= k / 10;
            //quick sort
            start = clock();
            //sorted = quicksort(data, size, v);
            end = clock();
            quicksort_cputime = ((double) (end - start)) / CLOCKS_PER_SEC;
            cout << "quick sort k=" << v << ": \t" << quicksort_cputime << " s\n";
            qsktime += quicksort_cputime;
        //}
        cout << "\n\n";
    }
    
    //print sorted data
    cout << "\n----------------------------\n";
    //cout << "sorted:\n";
    for (int i = 0; i < size; i ++) {
        //cout << sorted[i][0] << "\t\t" << sorted[i][1] << endl;
    }
    
    //write data to output.txt
    writefile(sorted, size, "output.txt");
    
    
    cout << "data size:\t" << inputsize << endl;
    cout << randkind << ":\t" << fewrnum << endl;
    cout << "test  " << testtime << "  times\n";
    cout << "-----------------------------\n";
    cout << "-----Average CPU Time--------" << endl;
    cout << "merge sort: \t\t" << mstime / testtime << " s\n";
    cout << "insert sort: \t\t" << istime / testtime << " s\n";
    cout << "quick sort: \t\t" << qstime / testtime << " s\n";
    cout << "quick sort k=" << k << ": \t" << qsktime / testtime << " s\n";
    return 0;
}
