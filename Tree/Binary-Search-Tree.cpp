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
     * �ҵ������ѯ��ֵ�Ľڵ㣨���Ϊ�գ��ҵ���ӽ����Ľڵ㣬�����Ϊ�գ��ҵ����ĸ��׽ڵ㣩
     * ���������Ϊ���뺯�������
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
                // ���������Ϊ���뺯������ģ�������������Ѿ���������ڵ㣬���ؿգ�����insert��������֪���Ѿ����ڲ��ò�����
                return nullptr;
            }
        }
        return pre;
    }


    /*
     * ����ݹ������˽�к���
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
        // ��ͷ��㿪ʼ��
        while (p || !stk.empty()) {
            // һֱ�����ߣ�����һ���ڵ��ʱ���Ȳ���ӡ����ֵ���������ʣ�����Ӧ__midTraverse(node->left);
            if (p) {
                stk.push(p);
                p = p->left;
            }
                // ���û�к�����
            else {
                // ���ʱ�򵯳�ջ����ָ�룬��Ӧif (!node) return;
                p = stk.top();
                stk.pop();
                // ���ʱ���ջ����ֵ��ӡ�������ʣ�,��Ӧcout << node->val << " ";
                cout << p->val << " ";
                // ������֮��ֱ�������ߣ���Ӧ����__midTraverse(node->right);
                p = p->right;
            }
        }
    }

    /*
     * ǰ��ݹ������˽�к���
     */
    void __preTraverse(TreeNode *node) {
        if (!node) return;
        cout << node->val << " ";
        __preTraverse(node->left);
        __preTraverse(node->right);
    }


    /*
     * ����ݹ������˽�к���
     */
    void __afterTraverse(TreeNode *node) {
        if (node->left) __afterTraverse(node->left);
        if (node->right) __afterTraverse(node->right);
        cout << node->val << " ";
    }

    /*
     * ����ջǰ������ĺ���
     */
    void __preStackTraverse() {
        stack<TreeNode *> stk;
        // �Ӹ��ڵ㿪ʼ
        TreeNode *p = root;
        while (p || !stk.empty()) {
            // һֱ�������ߣ�ʵ���Ͼ���__preTraverse(node->left); ��仰�����Ҵ�ӡ��ֵ(������)
            if (p != nullptr) {
                cout << p->val << " ";
                stk.push(p);
                p = p->left;
            }
                // ���Ӳ������ˣ����ʱ���ջ�����ϲ��Ԫ��ȡ������Ӧ����if(!node) return;���д���
                // �������ϲ�Ԫ�ض����Һ��ӽ���̽�⣬��Ӧ����__preTraverse(node->right);���д���
            else {
                p = stk.top();
                stk.pop();
                p = p->right;
            }
        }
    }

public:
    /*
     * ��ֵ���ڵ㣩��ʼ��һ��������
     */
    BinarySearchTree(int val) {
        count = 1;
        root = new TreeNode(val);
    }

    /*
     * �����ʼ��һ��������
     */
    BinarySearchTree(int arr[], int n) {
        // �������һ���б�Ϊ�˳�ʼ�����ŵĲ��������������ҵ���λ��
        vector<int> vec;
        for (int i = 0; i < n; i++) vec.push_back(arr[i]);
        sort(vec.begin(), vec.end());
        int mid = vec[n / 2];
        cout << "��λ��Ϊ:  " << mid << endl;
        root = new TreeNode(mid);
        count = 1;
        for (int i = 0; i < n; i++) {
            this->insert(arr[i]);
        }
    }

    /*
     * ���뺯��
     */
    bool insert(int val) {
        TreeNode *newNode = new TreeNode(val);
        TreeNode *parent = this->findParent(val);
        if (parent == nullptr) {
            cout << "�ڵ��Ѵ���..." << endl;
            return false;
        } else {
            if (val < parent->val) {
                // ������Ϊ����
                parent->left = newNode;
                newNode->parent = parent;
            } else {
                // ������findParent�����İ����жϣ��������ֵ���������
                parent->right = newNode;
                newNode->parent = parent;
            }
            this->count++;
            cout << "����ɹ�..." << endl;
            return true;
        }
    }

    /*
     * ������ɾ��ָ���ڵ�
     * ������õ����ñ�ɾ�ڵ�������������ڵ�������λ��
     */
    bool deleteNode(int val) {

    }

    /*
     * ��������
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
     * Description�����������������
     * parameter flag��1����ݹ������2�����ֶ���ջ��������
     */
    void midTraverse(int flag) {
        if (flag == 1)
            this->__midTraverse(this->root);
        else {
            __midStackTraverse();
        }
    }

    /*
     * Description����������ǰ�����
     * parameter flag��1����ݹ������2�����ֶ���ջ��������
     */
    void preTraverse(int flag) {
        if (flag == 1)
            this->__preTraverse(this->root);
        else {
            this->__preStackTraverse();
        }
    }

    /*
     * Description���������ĺ�������
     * parameter flag��1����ݹ������2�����ֶ���ջ��������
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