/*
-------------------------------------------------
   Author :       86178
   date:          2021/7/14 14:24
   Description :
-------------------------------------------------
*/
#include<bits/stdc++.h>

using namespace std;

/*
 * ����ڵ�ṹ��
 */
typedef struct LinkNode {
    int val;
    struct LinkNode *next;
    int length;
} Node, *LinkList;

/*
 * Description������Ŀճ�ʼ��������һ��ͷ���
 * parameter: None
 * return��ͷ���
 */
LinkList initLinkList() {
    LinkList L = (Node *) malloc(sizeof(Node));
    L->next = nullptr, L->val = 0, L->length = 0;
    return L;
}


/*
 * Description���ڲ�������ͨ�����������ҵ��ڵ㣬����֮���һЩ����
 * parameter L
 * parameter index����������0��ʼ��
 * return���������Ľڵ�ָ��
 */
Node *search(LinkList L, int index) {
    if (index > L->length || index < 0) return nullptr;
    Node *node = L;
    while (index--) {
        node = node->next;
    }
    return node;
}

/*
 * Description������ڵ�
 * parameter L
 * parameter index�������λ�ã���0��ʼ��
 * parameter val:�ڵ��ֵ
 * return���Ƿ����ɹ�
 */
bool insert(LinkList L, int index, int val) {
    Node *node = search(L, index);
    if (node == nullptr) return false;
    Node *new_node = (Node *) malloc(sizeof(Node));
    if (new_node == nullptr) return false;
    new_node->val = val;
    new_node->next = node->next;
    node->next = new_node;
    L->length++;
    return true;
}

/*
 * Description��ͷ�巨����������
 * parameter arr����ֵ����
 * parameter length�����鳤��
 * return��ͷ���
 */
LinkList initLinkListHead(int arr[], int length) {
    LinkList L = initLinkList();
    for (int i = 0; i < length; i++) {
        // ͷ�巨��Զ�ڵ�0��λ�ò�������
        insert(L, 0, arr[i]);
    }
    return L;
}

/*
 * Description��β�巨����������
 * parameter arr����ֵ����
 * parameter length�����鳤��
 * return��ͷ���
 */
LinkList initLinkListTail(int arr[], int length) {
    LinkList L = initLinkList();
    Node *node = L;
    // β�巨ÿ����ĩβ����Ԫ�أ���Ҫ����ʹ��insert���������ӶȻᵽn^2
    for (int i = 0; i < length; i++) {
        Node *new_node = (Node *) malloc(sizeof(Node));
        new_node->val = arr[i];
        new_node->next = node->next;
        node->next = new_node;
        node = node->next;
        L->length++;
    }
    return L;
}

/*
 * parameter L
 * parameter index��Ҫɾ����Ԫ�ص���������0��ʼ��
 */
bool l_delete(LinkList L, int index) {
    // ɾ����Ҫ�ҵ���ǰһ���Ľڵ�ָ��
    Node *pre = search(L, index);
    if (pre == nullptr) return false;
    Node *del = pre->next;
    pre->next = del->next;
    free(del);
    L->length--;
    return true;
}

/*
 * Description�����index���ڵ��ֵ
 * parameter L
 * parameter index����������0��ʼ��
 * return ����ֵ
 */
int getVal(LinkList L, int index) {
    Node *node = search(L, index+1);
    if (node == nullptr) {
        printf("Խ�����");
        return -1;
    }
    return node->val;
}

/*
 * Description��ͨ��ֵѰ�ҵ������еĽڵ�
 * parameter L
 * parameter val��ֵ
 * return��ƥ��Ľڵ�
 */
Node *find(LinkList L, int val) {
    Node *node = L;
    while (node) {
        node = node->next;
        if (node->val == val)
            return node;
    }
    return nullptr;
}

/*
 * Description����������
 * parameter L
 * return��������
 */
int getLength(LinkList L) {
    return L->length;
}


/*
 * Description����������
 */
void traverse(LinkList L) {
    Node *node = L->next;
    while (node) {
        printf("%d ", node->val);
        node = node->next;
    }
    printf("\n");
}


int main() {
    int a[] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    printf("ͷ�巨��ʼ����\n");
    LinkList L = initLinkListHead(a, sizeof(a) / sizeof(a[0]));
    traverse(L);
    printf("β�巨��ʼ����\n");
    L = initLinkListTail(a, sizeof(a) / sizeof(a[0]));
    traverse(L);
    printf("�����ȣ�%d\n", getLength(L));
    insert(L, getLength(L), 0);
    traverse(L);

    printf("�����ȣ�%d\n", getLength(L));
    l_delete(L, 1);
    traverse(L);

    printf("����3���Ľڵ�ֵΪ%d\n", getVal(L, 3));

    return 0;
}