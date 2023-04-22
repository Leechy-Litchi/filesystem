#ifndef NODE_H
#define NODE_H

#include <string> 
#include <vector>
#include <ctime>

using namespace std;

class Node {
protected:
    string name;          // 文件名或目录名
    bool isFile;          // 文件或目录
    time_t ctime;         // 创建时间
    int size;             // 文件大小
    int firstBlock;       // 首块磁盘号
    Node* parent;         // 父目录
    vector<Node*> children; // 子文件或子目录 
public:
    // Setter 方法
    void setName(string name);
    void setIsFile(bool isFile);
    void setCtime(time_t ctime); 
    void setSize(int size);
    void setFirstBlock(int firstBlock);
    void setParent(Node* parent);
    void setChildren(vector<Node*> children);

    // Getter 方法
    string getName();
    bool getIsFile();
    time_t getCtime();
    int getSize();
    int getFirstBlock();
    Node* getParent();
    vector<Node*>* getChildren();

    Node();
    Node(string name, bool isFile, time_t ctime, int size, int firstBlock, Node* parent);
};

#endif