#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include<bits/stdc++.h> 

using namespace std;

struct node 
{ 
    int key;
    int count;
    node *left, *right; 
    vector<string> words;
}; 

node* search(node* root, int key, string str) 
{ 
  // Base Cases: root is null or key is present at root 
    if (root == NULL || root->key == key) 
       return root; 

    // Key is greater than root's key 
    if (root->key < key) 
       return search(root->right, key); 

    // Key is smaller than root's key 
    return search(root->left, key); 
}


// A utility function to create a new BST node 
node *newNode(int key, string str) 
{ 
    node *temp =  new node;
    temp->key = key; 
    temp->left = temp->right = NULL;
    temp->words.push_back(str);
    return temp; 
} 

// A utility function to do inorder traversal of BST 
void inorder(node *root) 
{ 
    if (root != NULL) 
    { 
        inorder(root->left); 
        cout << root->key << endl;
        inorder(root->right); 
    } 
} 

/* A utility function to insert a new node with given key in BST */ 
node* insert(node* node, int key, string str) 
{ 
    /* If the tree is empty, return a new node */
    if (node == NULL) return newNode(key, str); 
    
    /* Otherwise, recur down the tree */
    if(key == node->key) {
        node->count++;
        node->words.push_back(str);
        return node;
    }
    else if(key < node->key)
        node->left = insert(node->left, key, str);
    else if(key > node->key)
        node->right = insert(node->right, key, str);

    /* return the (unchanged) node pointer */
    return node; 
}


void populate(vector<string> &file) {
   ifstream inFile;
   inFile.open("file.txt");
   
   //Check for error
   if(inFile.fail()){
       cerr << "Error opening file" << endl;
       exit(1);
   }
   
   string item;
   int count = 0;
   
   while(!inFile.eof()){
       inFile >> item;
       // using transform() function and ::tolower in STL 
       transform(item.begin(), item.end(), item.begin(), ::tolower);
       
       // Remove Non Alpha Characters
       item.erase(remove_if(item.begin(), item.end(), [](char c) { return !isalpha(c); } ), item.end());
       
       file.push_back(item);
   }
}

void createTree(vector<string> &file, node *root) {
    root = insert(root, file[0].length(), file[0]);
    
    for(int i = 1; i < file.size(); i++) {
        //node, key, str
        insert(root, file[i].length(), file[i]);
    }
}

// Driver Program to test above functions 
int main() 
{ 
    vector<string> file;
    node *root = NULL;

    // Populate the contents of the file in the vector
    populate(file);
    
    createTree(file, root);

    // for(int i = 0; i < file.size(); i++) {
    //   // cout << file[i] << endl;
    // }



    return 0; 
}