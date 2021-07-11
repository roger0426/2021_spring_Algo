//
//  main.cpp
//  1092_algorithm_hw3_binarytree
//
//  Created by Chang Chung Che on 2021/4/13.
//

#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

int maxnum = 0, minnum = 10000;

class tree;
class Treenode{
private:
  Treenode *parent;
  Treenode *leftchild;
  Treenode *rightchild;
  int value;
  string data;
  bool write;
  
public:
  Treenode(): parent(NULL), leftchild(NULL), rightchild(NULL), value(0), data(""), write(false){ }
  
  Treenode(int n, string d): parent(NULL), leftchild(NULL), rightchild(NULL), value(n), data(d), write(1){ }

  
  
  friend class tree;
};

class tree{
private:
  Treenode* root;
  int treesize;
public:
  tree(): root(NULL) { }
  
  tree(Treenode* node):root(node) { }
    
  void insertnode(int num, string data){
    Treenode *current = root;
    Treenode *last = NULL;
    Treenode *insert = new Treenode(num, data);
    
    current = this->root;
    
    while (current != NULL) {
      last = current;
      if (insert->value < current->value){
        current = current->leftchild;
      }
      else{
        current = current->rightchild;
      }
    }
    insert->parent = last;
    
    if (last == NULL){
      this->root = insert;
    }
    else if (insert->value < last->value){
      last->leftchild = insert;
    }
    else if (insert->value > last->value){
      last->rightchild = insert;
    }
  }
  
  Treenode* Search(int target){
    Treenode *current = root;
    while (current != NULL && target != current->value) {
      if (target < current->value){
        current = current->leftchild;
      }
      else {
        current = current->rightchild;
      }
    }
    if (current == NULL) {
      cout << "cannot find\n";
      return NULL;
    }
    else {
      cout << "find data ! value:\t" << current->value << "\tdata:\t" << current->data << endl;
      return current;
    }
  }
  
  void maximin(){
    stack<Treenode*> s;
    s.push(root);
    while (s.size() > 0) {
      Treenode *node = s.top();
      s.pop();
      
      if (node->value > maxnum && node != root) {
        maxnum = node->value;
      }
      if (node->value < minnum && node != root) {
        minnum = node->value;
      }
      
      if (node->rightchild) s.push(node->rightchild);
      if (node->leftchild) s.push(node->leftchild);
    }
    return;
  }
  
  void successor(int target) {
    Treenode *current = root;
    while (current != NULL && target != current->value) {
      if (target < current->value){
        current = current->leftchild;
      }
      else {
        current = current->rightchild;
      }
    }
    if (current == NULL) {
      cout << "cannot find\n";
    }
    else {
      cout << "find data ! value:\t" << current->value << "\tdata:\t" << current->data << endl;
      if (current->leftchild != NULL) {
        cout << "leftchild:\tvalue:\t" << current->leftchild->value << "data:\t" << current->leftchild->data << endl;
      }
      else {
        cout << "no leftdhild\n";
      }
      if (current->rightchild != NULL) {
        cout << "rightchild:\tvalue:\t" << current->rightchild->value << "data:\t" << current->rightchild->data << endl;
      }
      else {
        cout << "no rightdhild\n";
      }
    }
  }
  
  void predecessor(int target) {
    Treenode *current = root;
    while (current != NULL && target != current->value) {
      if (target < current->value){
        current = current->leftchild;   //go left
      }
      else {
        current = current->rightchild;  //go right
      }
    }
    if (current == NULL) {
      cout << "cannot find\n";
    }
    else {
      cout << "find data ! value:\t" << current->value << "\tdata:\t" << current->data << endl;
      if (current->parent != NULL && current->parent != root) {
        cout << "parent:\tvalue:\t" << current->parent->value << "data:\t" << current->parent->data << endl;
      }
      else {
        cout << "no parent\n";
      }
    }
  }
  
};


int main(int argc, const char * argv[]) {
  
  
  int select = 100;
  Treenode root(0, "root");
  Treenode* proot = &root;
  tree bigtree(proot);
  
  //set few data for testing
  bigtree.insertnode(3, "c");
  bigtree.insertnode(4, "d");
  bigtree.insertnode(5, "e");
  bigtree.insertnode(1, "a");
  bigtree.insertnode(2, "b");
  bigtree.insertnode(6, "f");
  
  while (select) {
    cout << "-----------------------------------------------------\nSelect Function\n" << "(1)insertln, (2)search, (3)max, (4)min, (5)successor, (6)predecessor, " << "(0)exit\n";
    cin >> select;
    
    switch (select) {
      case 0: {
        break;
      }
      case 1: {
        int n1;
        string s1;
        cout << "plz insert value(int) and data(string)\nvalue:\t";
        cin >> n1;
        cout << "data:\t";
        cin >> s1;
        bigtree.insertnode(n1, s1);
        break;
      }
      case 2: {
        int n2;
        cout << "plz insert value(int) that you are searching\nvalue:\t";
        cin >> n2;
        bigtree.Search(n2);
        break;
      }
      case 3: {
        //base on searching
        bigtree.maximin();
        cout << maxnum << endl;
        break;
      }
      case 4: {
        //base on searching
        bigtree.maximin();
        cout << minnum << endl;
        break;
      }
      case 5: {
        //base on searching
        int n5;
        cout << "plz insert value(int) that you are searching for successor\nvalue:\t";
        cin >> n5;
        bigtree.successor(n5);
        break;
      }
      case 6: {
        //base on searching
        int n6;
        cout << "plz insert value(int) that you are searching for predecessor\nvalue:\t";
        cin >> n6;
        bigtree.predecessor(n6);
        break;
      }
      default: {
        cout << "\nerror\n";
        break;
      }
    }
  }
  
  
  
  
  
  return 0;
}


