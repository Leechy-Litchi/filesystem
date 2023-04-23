#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "Node.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class FileSystem {
protected:
  int curBlock;
  Node *root;
  Node *curNode;
  void saveToFileRecursion(Node *node, ofstream &ofs);
  void loadFromFileRecursion(ifstream &ifs, Node *curNode);
  Node *findDir(string name);
  Node *findDirRecursion(Node *node, string name);
  Node *findFile(string name);
  Node *findFileRecursion(Node *node, string name);

public:
  Node *getCurNode();
  Node *getRoot();
  void cdChild(string name);
  void cdParent();
  void newDir(string name);
  Node *newFile(string name);
  void deleteFile(string name);
  void deleteDir(string name);
  void showItems(Node *curNode);
  void showPath();
  void saveToFile(string path = "fs.dat");
  void loadFromFile(string path = "fs.dat");
  int getDirSize(Node *node);
  void rename(string filename1, string filename2);
  void copyFile(string src, string dest);

  FileSystem();
};

#endif
