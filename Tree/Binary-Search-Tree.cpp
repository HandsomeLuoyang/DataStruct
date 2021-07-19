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
     * 中序遍历的私有函数
     */
    void __midTraverse(TreeNode *node) {
        if (node->left) __midTraverse(node->left);
        cout << node->val << " ";
        if (node->right) __midTraverse(node->right);
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
        TreeNode *node = find(val);
        if (node == nullptr) {
            cout << "要删除的节点不存在..." << endl;
            return false;
        } else {

            int flag = -1;
            // 找到要删除的节点是他爸的左孩子还是右孩子，还是root节点
            if (node->parent == nullptr) {
                flag = 0; // 根节点
            } else if (node->parent->left == node) {
                flag = 1; // 左孩子
            } else {
                flag = 2; // 右孩子
            }


            // 1.没有孩子
            if (node->left == nullptr && node->right == nullptr) {
                if (flag == 1) {
                    node->parent->left = nullptr;
                    delete node;
                    return true;
                } else if (flag == 2) {
                    node->parent->right = nullptr;
                    delete node;
                    return true;
                } else {
                    // 如果仅有的根节点被删除了，树就没了，不允许删除
                    cout << "仅剩根节点，不允许删除..." << endl;
                    return false;
                }
            }

            // 2.只有左子树或者右子树
            if (node->left != nullptr && node->right == nullptr) {
                // 选择左子树最大的那个顶替
                TreeNode *temp = node->left;
                while (temp->right) temp = temp->right;

                // 如果这个节点没有右孩子了
                if (temp == node->left) {
                    if (flag == 0) {
                        temp->parent = nullptr;
                        temp->right =
                    }
                }

                // 如果这个节点还有左孩子，就把孩子给他爸，而他只可能是他爸的右孩子
                if (temp->left != nullptr) {
                    if (temp->parent->left != temp)
                }
            }
        }
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

    void midTraverse() {
        this->__midTraverse(this->root);
    }

    int getCount() { return this->count; };
};


int main() {
    int arr[] = {2, 4, 5, 6, 8, 9, 21, 4567, 6, 87,};
    BinarySearchTree t(arr, sizeof(arr) / sizeof(arr[0]));
    cout << t.getCount() << endl;
    t.midTraverse();
    return 0;
}