#include "Filesystem.h"

void interaction() {
    FileSystem fs;
    cout << "输入 man 以查看各个函数及其功能" << endl;
    while (true) {
        cout << fs.getCurNode()->getName() << "> ";
        string cmd;
        getline(cin, cmd);

        if (cmd == "ls") {
            fs.showItems(fs.getCurNode());
        }
        else if (cmd == "cd ..") {
            fs.cdParent();
        }
        else if (cmd.substr(0, 3) == "cd ") {
            fs.cdChild(cmd.substr(3));
        }
        else if (cmd == "pwd") {
            fs.showPath();
        }
        else if (cmd.substr(0, 6) == "mkdir ") {
            fs.newDir(cmd.substr(6));
        }
        else if (cmd.substr(0, 6) == "touch ") {
            auto file = fs.newFile(cmd.substr(6));
            int size;
            cout << "输入文件大小：";
            cin >> size;
            file->setSize(size);
            fflush(stdin);
            // system("cls");
        }
        else if (cmd.substr(0, 6) == "rm -r ") {
            fs.deleteDir(cmd.substr(6));
        }
        else if (cmd.substr(0, 6) == "rm -f ") {
            fs.deleteFile(cmd.substr(6));
        }
        else if (cmd.substr(0, 4) == "save") {
            string path = cmd.substr(4);
            if (path == "" || path == " ") { path = "fs.dat"; }
            else {
                path = cmd.substr(5);
            }
            fs.saveToFile(path);
        }
        else if (cmd.substr(0, 4) == "load") {
            string path = cmd.substr(4);
            if (path == "" || path == " ") { path = "fs.dat"; }
            else {
                path = cmd.substr(5);
            }
            fs.loadFromFile(path);
        }
        else if (cmd.substr(0, 5) == "total") {
            cout << fs.getDirSize(fs.getRoot()) << endl;
        }
        else if (cmd.substr(0, 7) == "rename ") {
            size_t pos = cmd.find(' ');
            if (pos != string::npos) {
                string name1 = cmd.substr(7, pos - 7);
                string name2 = cmd.substr(pos + 1);
                fs.rename(name1, name2);
                fs.getCurNode()->getName() = name2;
            }
            else {
                cout << "用法：rename <oldName> <newName>" << endl;
            }
        }
        else if (cmd.substr(0, 5) == "copy ") {
            size_t pos = cmd.find(' ');
            if (pos != string::npos) {
                string src = fs.getCurNode()->getName();
                string dest = cmd.substr(pos + 1);
                fs.copyFile(src, dest);
            }
            else {
                cout << "用法:copy <src> <dest>" << endl;
            }
        }
        else if (cmd == "cls") {
            system("cls");
        }
        else if (cmd == "exit") {
            return;
        }
        else if (cmd == "man") {
            cout << "用法\t\t\t功能" << endl;
            cout << "ls\t\t\t列出目录内容" << endl;
            cout << "cd ..\t\t\t进入父目录" << endl;
            cout << "cd <dir>\t\t进入子目录<dir>" << endl;
            cout << "pwd\t\t\t显示当前路径" << endl;
            cout << "mkdir <dir>\t\t创建目录<dir>" << endl;
            cout << "touch <file>\t\t创建空文件<file>" << endl;
            cout << "rm -r <dir>\t\t删除目录<dir>" << endl;
            cout << "rm -f <file>\t\t删除文件<file>" << endl;
            cout << "save <file>\t\t将文件系统保存到<file>" << endl;
            cout << "load <file>\t\t从<file>载入文件系统" << endl;
            cout << "total\t\t\t显示当前目录总大小" << endl;
            cout << "rename <old> <new> \t将<old>重命名为<new>" << endl;
            cout << "copy <src> <dest> \t复制<src>为<dest>" << endl;
            cout << "cls\t\t\t清空输出" << endl;
            cout << "exit\t\t\t退出" << endl;
        }
    }
}
int main() {
    system("chcp 65001");
    system("cls");
    interaction();
    return 0;
}