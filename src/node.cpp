#include "node.h"
using namespace std;

// Setter 方法
void Node::setName(string name) {
    this->name = name;
}
void Node::setIsFile(bool isFile) {
    this->isFile = isFile;
}
void Node::setCtime(time_t ctime) {
    this->ctime = ctime;
}
void Node::setSize(size_t size) {
    this->size = size;
}
void Node::setFirstBlock(size_t firstBlock) {
    this->firstBlock = firstBlock;
}
void Node::setParent(Node* parent) {
    this->parent = parent;
}
void Node::setChildren(vector<Node*> children) {
    this->children = children;
}

// Getter 方法
string Node::getName() {
    return name;
}
bool Node::getIsFile() {
    return isFile;
}
time_t Node::getCtime() {
    return ctime;
}
size_t Node::getSize() {
    return size;
}
size_t Node::getFirstBlock() {
    return firstBlock;
}
Node* Node::getParent() {
    return parent;
}
vector<Node*>* Node::getChildren() {
    return &children;
}
Node::Node() {}
Node::Node(string name, bool isFile, time_t ctime, size_t size, size_t firstBlock, Node* parent) {
    this->name = name;          // 文件名或目录名
    this->isFile = isFile;          // 文件或目录
    this->ctime = ctime;         // 创建时间 
    this->size = size;             // 文件大小 
    this->firstBlock = firstBlock;       // 首块磁盘号
    this->parent = parent;         // 父目录
};