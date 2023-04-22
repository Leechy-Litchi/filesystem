#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <iostream>  
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <vector>
#include "Node.h"

using namespace std;

class FileSystem {
public:
    Node* root;          
    Node* curNode;        
    int curBlock;         
    FileSystem();

    void showPath();
    void showItems(Node* curNode);
    void cdParent();
    void cdChild(string name);
    Node* newFile(string name);
    void deleteFile(string name);
    void newDir(string name); 
    void deleteDir(string name);
    void saveToFile(string path = "fs.dat");
    void saveToFileRecursive(Node* node, ofstream& ofs);
    void loadFromFile(string path = "fs.dat");
    void loadFromFileRecursive(ifstream& ifs, Node* curNode);
    Node* findDir(string name); 
    void findDirRecursive(Node* node, string name, Node*& res);
    int getDirSize(Node* node);
    Node* findFile(string name);
    void rename(string filename1, string filename2);
    Node* getParentDir(Node* curNode);
    Node* findFileRecursive(Node* node, string name);
    void copyFile(string src, string dest);
};

#endif
