#include "filesystem.h"

FileSystem::FileSystem() {
    curBlock = 0;
    root = new Node("root", false, time(NULL), 0, ++curBlock, root);
    root->setParent(root);
    root->setChildren(vector<Node*>());
    curNode = root;
}

// 显示当前路径
void FileSystem::showPath() {
    cout << root->getName() << "/";
    Node* p = curNode;
    while (p != root) {
        cout << p->getName() << "/";
        p = p->getParent();
    }
    cout << endl;
}

// 显示当前路径下所有文件和目录
void FileSystem::showItems(Node* curNode) {
    if (curNode == nullptr) return;    // 检查 curNode 指针

    cout << (curNode->getIsFile() ? "FILE: " : "DIR: ");
    cout << curNode->getName() << endl;

    for (auto child : *curNode->getChildren()) {
        if (child->getName() != "") {
            showItems(child);
        }
    }
}

// 切换到父目录
void FileSystem::cdParent() {
    curNode = curNode->getParent();
}

// 切换到子目录
void FileSystem::cdChild(string name) {
    for (auto child : *curNode->getChildren()) {
        if (child->getName() == name) {
            curNode = child;
            return;
        }
    }
}
// 在当前目录下新建一个新的空文件  
Node* FileSystem::newFile(string name) {
    Node* newNode = new Node(name, true, time(NULL), 0, ++curBlock, curNode);
    curNode->getChildren()->push_back(newNode);
    return newNode;
}

// 在当前目录下删除一个文件  
void FileSystem::deleteFile(string name) {
    for (auto it = curNode->getChildren()->begin(); it != curNode->getChildren()->end(); ++it) {
        if ((*it)->getName() == name && (*it)->getIsFile()) {
            delete* it;
            curNode->getChildren()->erase(it);
            return;
        }
    }
}

// 在当前目录下创建一个新文件夹  
void FileSystem::newDir(string name) {
    Node* newNode = new Node(name, false, time(NULL), 0, ++curBlock, curNode);
    curNode->getChildren()->push_back(newNode);
}

// 在当前目录下删除一个文件夹  
void FileSystem::deleteDir(string name) {
    for (auto it = curNode->getChildren()->begin(); it != curNode->getChildren()->end(); ++it) {
        if ((*it)->getName() == name && !(*it)->getIsFile()) {
            delete* it;    // 递归删除子文件和子目录
            curNode->getChildren()->erase(it);
            return;
        }
    }
}

// 把当前文件系统存入文件
void FileSystem::saveToFile(string path) {
    ofstream ofs(path);
    saveToFileRecursive(this->root, ofs);
}
void FileSystem::saveToFileRecursive(Node* node, ofstream& ofs) {
    char blockStr[10];
    sprintf(blockStr, "%d", node->getFirstBlock());

    ofs << node->getName() << ' ' << node->getIsFile() << ' '
        << node->getCtime() << ' ' << node->getSize() << ' '
        << blockStr << ' '
        << (node->getParent() == nullptr ? "null" : node->getParent()->getName()) << endl;
    for (auto child : *node->getChildren()) {
        saveToFileRecursive(child, ofs);
    }
    cout << "正在存储：" << node->getName() << endl;
}

void FileSystem::loadFromFile(string path) {
    if (path == "" || path == " ") { path = "fs.dat"; }
    ifstream ifs(path);
    if (!ifs.good()) return;

    curNode->setSize(0);      // 初始化 size

    loadFromFileRecursive(ifs, root);
}
void FileSystem::loadFromFileRecursive(ifstream& ifs, Node* curNode) {
    if (curNode == nullptr) return;

    string line;
    getline(ifs, line);

    istringstream iss(line);

    string name, parentName;
    bool isFile;
    time_t ctime;
    int size, firstBlock;
    iss >> name >> isFile >> ctime >> size >> firstBlock >> parentName;

    Node* child = new Node(name, isFile, ctime, size, firstBlock, findDir(parentName));

    if (name != "root") {
        curNode->setSize(curNode->getSize() + size);
        curNode->getChildren()->push_back(child);
    }
    else {
        curNode = child;
        child = curNode;
        child->setParent(child);
    }
    if (line != "") {
        cout << "正在读取：" << name << endl;
        loadFromFileRecursive(ifs, child);
    }

}

Node* FileSystem::findDir(string name) {
    if (name == "root" or name == "null") { return root; }
    Node* res = nullptr;
    findDirRecursive(root, name, res);
    return res;
}

void FileSystem::findDirRecursive(Node* node, string name, Node*& res) {
    if (node->getName() == name && !node->getIsFile()) {
        res = node;
        return;
    }

    for (auto child : *node->getChildren()) {
        findDirRecursive(child, name, res);
    }
}
// 计算当前目录下文件总大小  
int FileSystem::getDirSize(Node* node) {
    int size = 0;
    for (auto child : *node->getChildren()) {
        if (child->getIsFile()) size += child->getSize();
        else size += getDirSize(child);
    }
    return size;
}

// 查找文件，返回文件节点  

Node* FileSystem::findFile(string name) {
    Node* curNode = root;
    while (curNode != nullptr) {
        if (curNode->getName() == name) {
            return curNode;
        }

        if (!curNode->getIsFile()) {
            for (auto child : *curNode->getChildren()) {
                if (child->getName() == name) {
                    return child;
                }
            }
            curNode = nullptr;
        }
    }
    return nullptr;
}

// 重命名文件或目录
void FileSystem::rename(string filename1, string filename2) {
    Node* file1 = findFile(filename1);
    if (file1 == nullptr) {
        cout << "文件不存在：" << filename1 << endl;
        return;
    }

    Node* file2 = findFile(filename2);
    if (file2 != nullptr) {
        cout << "文件已存在：" << filename2 << endl;
        return;
    }

    file1->getName() = filename2;
}
Node* FileSystem::getParentDir(Node* curNode) {
    Node* parent = curNode->getParent();
    while (parent != nullptr && parent != root) {
        curNode = parent;
        parent = curNode->getParent();
    }
    return curNode;
}
Node* FileSystem::findFileRecursive(Node* node, string name) {
    Node* res = nullptr;
    if (node->getName() == name) return node;

    for (auto child : *node->getChildren()) {
        res = findFileRecursive(child, name);
        if (res != nullptr) return res;
    }
    return res;
}

// 复制文件
void FileSystem::copyFile(string src, string dest) {
    Node* srcNode = findFile(src);
    Node* destNode = findFile(dest);
    if (srcNode != nullptr && destNode == nullptr && srcNode->getIsFile()) {
        destNode = new Node(dest, srcNode->getIsFile(), time(NULL), srcNode->getSize(), srcNode->getFirstBlock(), srcNode->getParent());
        srcNode->getParent()->getChildren()->push_back(destNode);
    }
};