#include <bits/stdc++.h>

using namespace std;

enum NodeType { FILE_TYPE, DIR_TYPE };

class Node {
public:
    string name;
    NodeType type;
    Node* parent;
    map<string, Node*> children;

    Node(string n, NodeType t, Node* p) : name(n), type(t), parent(p) {}

    ~Node() {
        for (auto const& [name, node] : children) {
            delete node;
        }
    }
};

class FileExplorer {
private:
    Node* root;
    Node* cwd;

    vector<string> split(const string& s, char c) {
        vector<string> tokens;
        string token;
        istringstream tokenStream(s);
        while (getline(tokenStream, token, c)) {
            if (!token.empty()) tokens.push_back(token);
        }
        return tokens;
    }

public:
    FileExplorer() {
        root = new Node("/", DIR_TYPE, nullptr);
        cwd = root;
    }
    ~FileExplorer() {
        delete root;
    }


    void printCwd() {
        if (cwd == root) {
            cout << "/" << endl;
            return;}
        string path = "";
        Node* temp = cwd;
        while (temp != root) {
            path = "/" + temp->name + path;
            temp = temp->parent;
        }
        cout << path << endl;
    }

    void ls() {
        bool first = true;
        for (auto const& [name, node] : cwd->children) {
            if (!first) cout << " ";
            cout << name;
            first = false;
        }
        cout << endl;
    }

    void mkdir(string name) {
        if (cwd->children.count(name)) {
            cout << name << " already exists" << endl;
        } else {
            cwd->children[name] = new Node(name, DIR_TYPE, cwd);
        }
    }

    void touch(string name) {
        if (cwd->children.count(name)) {
            cout << name << " already exists" << endl;
        } else {
            cwd->children[name] = new Node(name, FILE_TYPE, cwd);
        }
    }

    void cd(string path) {
        if (path == "/") {
            cwd = root;
            return;
        }

        Node* target = (path[0] == '/') ? root : cwd;
        vector<string> parts = split(path, '/');

        for (const string& part : parts) {
            if (part == "..") {
                if (target->parent == nullptr) {
                    cout << "currently at root" << endl;
                    return;
                }
                target = target->parent;
            } else {
                if (target->children.find(part) == target->children.end()) {
                    cout << part << " not found" << endl;
                    return;
                }
                if (target->children[part]->type == FILE_TYPE) {
                    cout << part << " is not a directory" << endl;
                    return;
                }
                target = target->children[part];
            }
        }
        cwd = target;
    }
};

int main() {
    FileExplorer fe;
    string line, cmd, arg;

    while (getline(cin, line)) {
        if (line == "exit") break;
        
        stringstream ss(line);
        ss >> cmd;

        if (cmd == "cwd") {
            fe.printCwd();
        } else if (cmd == "ls") {
            fe.ls();
        } else if (cmd == "mkdir") {
            if (ss >> arg) fe.mkdir(arg);
        } else if (cmd == "touch") {
            if (ss >> arg) fe.touch(arg);
        } else if (cmd == "cd") {
            if (ss >> arg) fe.cd(arg);
        }
    }

}