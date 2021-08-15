/*
-------------------------------------------------
   Author :       86178
   date:          2021/7/19 19:43
   Description :
-------------------------------------------------
*/
#include<bits/stdc++.h>

using namespace std;


class TreeNode {
public:
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;

    TreeNode() : val(0), left(nullptr), right(nullptr), parent(nullptr) {};

    explicit TreeNode(int val) : val(val), left(nullptr), right(nullptr), parent(nullptr) {};

    TreeNode(int val, TreeNode *left, TreeNode *right, TreeNode *parent) : val(val), left(left), right(right),
                                                                           parent(parent) {};
};


class BinarySearchTree {
private:
    int count;
    TreeNode *root;

    /*
     * 找到这个查询的值的节点（如果为空，找到最接近它的节点，如果不为空，找到它的父亲节点）
     * 这个函数是为插入函数服务的
     */
    TreeNode *findParent(int val) {
        TreeNode *node = this->root;
        TreeNode *pre = nullptr;
        while (node) {
            if (val < node->val) {
                pre = node;
                node = node->left;
            } else if (val > node->val) {
                pre = node;
                node = node->right;
            } else {
                // 这个函数是为插入函数服务的，所以如果发现已经存在这个节点，返回空，这样insert函数就能知道已经存在不用插入了
                return nullptr;
            }
        }
        return pre;
    }


    /*
     * 中序递归遍历的私有函数
     */
    void __midTraverse(TreeNode *node) {
        if (!node) return;
        __midTraverse(node->left);
        cout << node->val << " ";
        __midTraverse(node->right);
    }

    void __midStackTraverse() {
        TreeNode *p = root;
        stack<TreeNode *> stk;
        // 从头结点开始找
        while (p || !stk.empty()) {
            // 一直向左走，碰到一个节点的时候先不打印它的值（即不访问），对应__midTraverse(node->left);
            if (p) {
                stk.push(p);
                p = p->left;
            }
                // 左边没有孩子了
            else {
                // 这个时候弹出栈顶的指针，对应if (!node) return;
                p = stk.top();
                stk.pop();
                // 这个时候把栈顶的值打印（即访问）,对应cout << node->val << " ";
                cout << p->val << " ";
                // 访问完之后直接往右走，对应的是__midTraverse(node->right);
                p = p->right;
            }
        }
    }

    /*
     * 前序递归遍历的私有函数
     */
    void __preTraverse(TreeNode *node) {
        if (!node) return;
        cout << node->val << " ";
        __preTraverse(node->left);
        __preTraverse(node->right);
    }


    /*
     * 后序递归便利的私有函数
     */
    void __afterTraverse(TreeNode *node) {
        if (node->left) __afterTraverse(node->left);
        if (node->right) __afterTraverse(node->right);
        cout << node->val << " ";
    }

    /*
     * 利用栈前序遍历的函数
     */
    void __preStackTraverse() {
        stack<TreeNode *> stk;
        // 从根节点开始
        TreeNode *p = root;
        while (p || !stk.empty()) {
            // 一直往左孩子走，实际上就是__preTraverse(node->left); 这句话，并且打印了值(即访问)
            if (p != nullptr) {
                cout << p->val << " ";
                stk.push(p);
                p = p->left;
            }
                // 左孩子不存在了，这个时候把栈中最上层的元素取出，对应的是if(!node) return;这行代码
                // 拿着最上层元素对其右孩子进行探测，对应的是__preTraverse(node->right);这行代码
            else {
                p = stk.top();
                stk.pop();
                p = p->right;
            }
        }
    }

public:
    /*
     * 单值（节点）初始化一颗搜索树
     */
    BinarySearchTree(int val) {
        count = 1;
        root = new TreeNode(val);
    }

    /*
     * 数组初始化一颗搜索树
     */
    BinarySearchTree(int arr[], int n) {
        // 如果给了一个列表，为了初始化最优的查找树，可以先找到中位数
        vector<int> vec;
        for (int i = 0; i < n; i++) vec.push_back(arr[i]);
        sort(vec.begin(), vec.end());
        int mid = vec[n / 2];
        cout << "中位数为:  " << mid << endl;
        root = new TreeNode(mid);
        count = 1;
        for (int i = 0; i < n; i++) {
            this->insert(arr[i]);
        }
    }

    /*
     * 插入函数
     */
    bool insert(int val) {
        TreeNode *newNode = new TreeNode(val);
        TreeNode *parent = this->findParent(val);
        if (parent == nullptr) {
            cout << "节点已存在..." << endl;
            return false;
        } else {
            if (val < parent->val) {
                // 插入作为左孩子
                parent->left = newNode;
                newNode->parent = parent;
            } else {
                // 由于有findParent函数的帮助判断，所以这个值不可能相等
                parent->right = newNode;
                newNode->parent = parent;
            }
            this->count++;
            cout << "插入成功..." << endl;
            return true;
        }
    }

    /*
     * 从树中删除指定节点
     * 这里采用的是让被删节点的左子树的最大节点来顶替位置
     */
    bool deleteNode(int val) {

    }

    /*
     * 搜索函数
     */
    TreeNode *find(int val) {
        TreeNode *node = this->root;
        while (node) {
            if (val < node->val) node = node->left;
            else if (val > node->val) node = node->right;
            else {
                return node;
            }
        }
        return nullptr;
    }

    /*
     * Description：二叉树的中序遍历
     * parameter flag：1代表递归遍历，2代表手动用栈迭代遍历
     */
    void midTraverse(int flag) {
        if (flag == 1)
            this->__midTraverse(this->root);
        else {
            __midStackTraverse();
        }
    }

    /*
     * Description：二叉树的前序遍历
     * parameter flag：1代表递归遍历，2代表手动用栈迭代遍历
     */
    void preTraverse(int flag) {
        if (flag == 1)
            this->__preTraverse(this->root);
        else {
            this->__preStackTraverse();
        }
    }

    /*
     * Description：二叉树的后续遍历
     * parameter flag：1代表递归遍历，2代表手动用栈迭代遍历
     */
    void afterTraverse(int flag) {
        if (flag == 1)
            this->__afterTraverse(this->root);
        else {}
    }

    int getCount() { return this->count; };
};


int main() {
    int arr[] = {2, 4, 5, 6, 8, 9, 21, 4567, 6, 87,};
    BinarySearchTree t(arr, sizeof(arr) / sizeof(arr[0]));
    t.midTraverse(2);
    return 0;
}