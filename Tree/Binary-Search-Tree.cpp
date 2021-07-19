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
     * ���������˽�к���
     */
    void __midTraverse(TreeNode *node) {
        if (node->left) __midTraverse(node->left);
        cout << node->val << " ";
        if (node->right) __midTraverse(node->right);
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
        TreeNode *node = find(val);
        if (node == nullptr) {
            cout << "Ҫɾ���Ľڵ㲻����..." << endl;
            return false;
        } else {

            int flag = -1;
            // �ҵ�Ҫɾ���Ľڵ������ֵ����ӻ����Һ��ӣ�����root�ڵ�
            if (node->parent == nullptr) {
                flag = 0; // ���ڵ�
            } else if (node->parent->left == node) {
                flag = 1; // ����
            } else {
                flag = 2; // �Һ���
            }


            // 1.û�к���
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
                    // ������еĸ��ڵ㱻ɾ���ˣ�����û�ˣ�������ɾ��
                    cout << "��ʣ���ڵ㣬������ɾ��..." << endl;
                    return false;
                }
            }

            // 2.ֻ������������������
            if (node->left != nullptr && node->right == nullptr) {
                // ѡ�������������Ǹ�����
                TreeNode *temp = node->left;
                while (temp->right) temp = temp->right;

                // �������ڵ�û���Һ�����
                if (temp == node->left) {
                    if (flag == 0) {
                        temp->parent = nullptr;
                        temp->right =
                    }
                }

                // �������ڵ㻹�����ӣ��ͰѺ��Ӹ����֣�����ֻ���������ֵ��Һ���
                if (temp->left != nullptr) {
                    if (temp->parent->left != temp)
                }
            }
        }
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