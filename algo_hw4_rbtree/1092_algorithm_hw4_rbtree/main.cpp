
//
//  main.c
//  1092_algorithm_hw4_rbtree
//
//  Created by Chang Chung Che on 2021/4/22.
//

#include <iostream>

using namespace std;

struct node
{
  int key;
  char color;
  int size;
  struct node *left, *right, *parent;
};

struct node * os_select(struct node *x, int i) {
  int r = 1;
  if (x->left != NULL) {
    r += x->left->size;
  }
  
  if (r == i) {
    return x;
  }
  else if(i < r) {
    return os_select(x->left, i);
  }
  else {
    return os_select(x->right, i - r);
  }
}

void os_rank(struct node *root, int key) {
  struct node *curr = root;
  while(curr != NULL && key != curr->key) {
    
    if (curr->key > key) {
      curr = curr->left;
    }
    else {
      curr = curr->right;
    }
  }
  
  if (curr == NULL) {
    cout << "cannot find !!\n";
  }
  else {
    cout << curr->key << '\t' << curr->color << '\t' << curr->size << '\n';
  }
  
  struct node *y;
  int r = 1;
  if (curr->left) {
    r += curr->left->size;
  }
  y = curr;
  while (y != root) {
    if (y == y->parent->right) {
      r ++;
      if (y->parent->left != NULL) {
        r += y->parent->left->size;
      }
    }
    y = y->parent;
  }
  
  if (y == NULL) {
    cout << "cannot find !!\n";
  }
  else {
//    cout << y->key << '\t' << y->color << '\t' << y->size << '\n';
  }
  cout << "rank:\t" << r << '\n';
}

void LeftRotate(struct node **root,struct node *x) {
  struct node *y = x->right;
  
  if (y != NULL) {
    x->right = y->left;
  }
  
  if (x->right != NULL)
    x->right->parent = x;
  y->parent = x->parent;
  
  if (x->parent == NULL)
    (*root) = y;
  else if (x == x->parent->left)
    x->parent->left = y;
  else    x->parent->right = y;
  
  y->left = x;
  y->size = x->size;
  x->parent = y;
  x->size = 1;
  if (x->left != NULL) {
    x->size += x->left->size;
  }
  else if(x->right != NULL) {
    x->size += x->right->size;
  }
}

void rightRotate(struct node **root,struct node *y) {
  struct node *x = y->left;

  y->left = x->right;

  if (x->right != NULL)
      x->right->parent = y;
  x->parent =y->parent;

  if (x->parent == NULL)
    (*root) = x;
  else if (y == y->parent->left)
    y->parent->left = x;
  else y->parent->right = x;

  x->right = y;
  x->size = y->size;
  y->parent = x;
  y->size = 1;
  if (y->left != NULL) {
    y->size += y->left->size;
  }
  else if(y->right != NULL) {
    y->size += y->right->size;
  }
}

void insertFixUp(struct node **root,struct node *z) {
  while (z != *root && z->parent->color == 'R')
  {
    struct node *y;
    
    if (z->parent == z->parent->parent->left)
      y = z->parent->parent->right;
    else
      y = z->parent->parent->left;
    
    if (y == NULL) {
      if (z->parent == z->parent->parent->left && z == z->parent->left)
      {
        char ch = z->parent->color ;
        z->parent->color = z->parent->parent->color;
        z->parent->parent->color = ch;
        rightRotate(root,z->parent->parent);
      }
      
      if (z->parent == z->parent->parent->right && z == z->parent->right)
      {
        char ch = z->parent->color ;
        z->parent->color = z->parent->parent->color;
        z->parent->parent->color = ch;
        LeftRotate(root,z->parent->parent);
      }
    }
    else {
      if (y->color == 'R')
      {
        y->color = 'B';
        z->parent->color = 'B';
        z->parent->parent->color = 'R';
        z = z->parent->parent;
      }
      else
      {
        if (z->parent == z->parent->parent->left && z == z->parent->left)
        {
          char ch = z->parent->color ;
          z->parent->color = z->parent->parent->color;
          z->parent->parent->color = ch;
          
          rightRotate(root,z->parent->parent);
        }
        
        if (z->parent == z->parent->parent->left && z == z->parent->right)
        {
          char ch = z->color ;
          z->color = z->parent->parent->color;
          z->parent->parent->color = ch;
          
          LeftRotate(root,z->parent);
          
          rightRotate(root,z->parent->parent);
        }
        
        if (z->parent == z->parent->parent->right && z == z->parent->right)
        {
          char ch = z->parent->color ;
          z->parent->color = z->parent->parent->color;
          z->parent->parent->color = ch;
          
          LeftRotate(root,z->parent->parent);
        }
        
        if (z->parent == z->parent->parent->right && z == z->parent->left)
        {
          char ch = z->color ;
          z->color = z->parent->parent->color;
          z->parent->parent->color = ch;
          
          rightRotate(root,z->parent);
          
          LeftRotate(root,z->parent->parent);
        }
      }
    }
  }
  (*root)->color = 'B';
}

void insert(struct node **root, int data) {
  struct node *z = (struct node*)malloc(sizeof(struct node));
  z->key = data;
  z->left = z->right = z->parent = NULL;
  z->size = 1;
  
  if (*root == NULL)
  {
    z->color = 'B';
    (*root) = z;
  }
  else
  {
    struct node *y = NULL;
    struct node *x = (*root);
    
    while (x != NULL)
    {
      x->size++;
      y = x;
      if (z->key < x->key)
        x = x->left;
      else
        x = x->right;
    }
    
    z->parent = y;
    if (z->key > y->key)
      y->right = z;
    else
      y->left = z;
    z->color = 'R';
    
    insertFixUp(root,z);
  }
}

void preorder(struct node *root) {
  if (root == NULL)
    return;
  cout << root->key << '\t' << root->color << '\t' << root->size << '\n';
  preorder(root->left);
  preorder(root->right);
}

int main() {
  struct node *root = NULL;
  insert(&root,30);
  insert(&root,45);
  insert(&root,90);
  insert(&root,34);
  insert(&root,55);
  insert(&root,105);
  insert(&root,127);
  insert(&root,10);
  
  
  int choice = 10;
  while (choice) {
    cout << "-----------------------------------------------------------------------------------------------------------\n";
    cout << "select function:\n(1) preorder traversal\t(2) insert new node\t(3) OS-select\t(4) OS-rank\t(0) exit\n";
    cin >> choice;
    
    switch (choice) {
      case 1: {
        cout << "preorder traversal: \n";
        preorder(root);
        break;
      }
        
      case 2: {
        int k = 0;
        cout << "insert key:\t";
        cin >> k;
        insert(&root, k);
        break;
      }
        
      case 3: {
        int i;
        cout << "the __-th smallest key:\t";
        cin >> i;
        if (i > root->size) {
          cout << "error!!\n";
          break;
        }
        struct node *select = os_select(root, i);
        cout << "\nselect:\n";
        cout << select->key << '\t' << select->color << '\t' << select->size << '\n';
        break;
      }
      case 4: {
        int fk = 0;
        cout << "plz insert target key:\t";
        cin >> fk;
        os_rank(root, fk);
        
        break;
      }
      
      case 0: {
        break;
      }
        
      default:
        cout << "error!!\n";
        break;
    }
  }
  
  
  
  
  
  return 0;
}
