/*
-------------------------------------------------
   Author :       86178
   date:          2021/7/16 22:56
   Description :
-------------------------------------------------
*/
#include<bits/stdc++.h>

/*
 * Trie树、前缀树、字典树
 */

using namespace std;

class Trie {
private:
    // 每个节点下面都是一个vector列表，列表里存放着指向下一个节点的指针
    vector<Trie *> children;
    // 记录这个节点是否为末尾,即是否到此构成一个存储了的字符串而不是前缀
    bool isEnd;

    // 查找到符合字符串的前缀的那个指针
    Trie *searchPrefix(string prefix) {
        Trie *node = this;
        for (int i = 0; i < prefix.length(); i++) {
            int ch = prefix[i] - 'a';
            if (node->children[ch] != nullptr)
                node = node->children[ch];
            else {
                return nullptr;
            }
        }
        return node;
    }


public:
    // 初始化
    Trie() : children(26), isEnd(false) {}

    // 插入函数
    void insert(string str) {
        Trie *node = this;
        for (int i = 0; i < str.size(); i++) {
            // 利用ascii码直接找到它的指针
            int ch = str[i] - 'a';
            if (node->children[ch] == nullptr) {
                // 若是不存在这个前缀就迭代的创建下去
                node->children[ch] = new Trie();
            }
            // 当前节点指针也要一直往下走
            node = node->children[ch];
        }
        node->isEnd = true;
    }

    bool search(string str) {
        Trie *node = this->searchPrefix(str);
        // 既要有这个前缀，并且到这已经构成一个出现过的字符串
        return node != nullptr && node->isEnd;
    }

    bool isPrefix(string prefix) {
        return this->searchPrefix(prefix) != nullptr;
    }
};


int main() {
    Trie t;
    t.insert("abc");
    t.insert("abcd");
    t.insert("abdc");
    t.insert("bcde");
    cout << t.search("abc"); // true
    cout << t.search("abdc"); // true
    cout << t.search("abcde"); // false
    cout << t.isPrefix("a"); // true
    cout << t.isPrefix("abc"); // true
    cout << t.isPrefix("bcd"); //true
    cout << t.isPrefix("d"); // false
    return 0;
}