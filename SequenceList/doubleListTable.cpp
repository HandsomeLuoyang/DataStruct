/*
-------------------------------------------------
   Author :       86178
   date:          2021/7/18 13:48
   Description :
-------------------------------------------------
*/
#include<bits/stdc++.h>

using namespace std;


/*
 * 链表节点结构体
 */
typedef struct LinkNode {
    int val;
    struct LinkNode *next;
    struct LinkNode *prev;
    int length;
} Node, *LinkList;

/*
 * Description：链表的空初始化，生成一个头结点
 * parameter: None
 * return：头结点
 */
LinkList initLinkList() {
    LinkList L = (Node *) malloc(sizeof(Node));
    L->next = nullptr, L->prev = nullptr, L->val = 0, L->length = 0;
    return L;
}


/*
 * Description：内部函数，通过给的索引找到节点，方便之后的一些操作
 * parameter L
 * parameter index：索引（从0开始）
 * return：索引处的节点指针
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
 * Description：插入节点
 * parameter L
 * parameter index：插入的位置（从0开始）
 * parameter val:节点的值
 * return：是否插入成功
 */
bool insert(LinkList L, int index, int val) {
    // 找到第index个节点
    Node *node = search(L, index);
    if (node == nullptr) return false;
    Node *new_node = (Node *) malloc(sizeof(Node));
    // 考虑分配失败的情况
    if (new_node == nullptr) return false;
    new_node->val = val;

    // 双链表的插入
    new_node->next = node->next;
    if (node->next != nullptr)
        node->next->prev = new_node;
    node->next = new_node;
    new_node->prev = node;

    L->length++;
    return true;
}

/*
 * Description：头插法建立单链表
 * parameter arr：传值建立
 * parameter length：数组长度
 * return：头结点
 */
LinkList initLinkListHead(int arr[], int length) {
    LinkList L = initLinkList();
    for (int i = 0; i < length; i++) {
        // 头插法永远在第0个位置插入数据
        insert(L, 0, arr[i]);
    }
    return L;
}

/*
 * Description：尾插法建立单链表
 * parameter arr：传值建立
 * parameter length：数组长度
 * return：头结点
 */
LinkList initLinkListTail(int arr[], int length) {
    LinkList L = initLinkList();
    Node *node = L;
    // 尾插法每次在末尾插入元素，不要持续使用insert函数，复杂度会到n^2
    for (int i = 0; i < length; i++) {
        Node *new_node = (Node *) malloc(sizeof(Node));
        new_node->val = arr[i];

        new_node->next = node->next;
        node->next = new_node;
        new_node->prev = node;

        node = node->next;

        L->length++;
    }
    return L;
}

/*
 * parameter L
 * parameter index：要删除的元素的索引（从0开始）
 */
bool l_delete(LinkList L, int index) {
    // 双链表删除一个节点可以直接找到它
    Node *del = search(L, index + 1);
    if (del == nullptr) return false;

    del->prev->next = del->next;
    del->next->prev = del->prev;

    free(del);
    L->length--;
    return true;
}

/*
 * Description：获得index处节点的值
 * parameter L
 * parameter index：索引（从0开始）
 * return 索引值
 */
int getVal(LinkList L, int index) {
    Node *node = search(L, index + 1);
    if (node == nullptr) {
        printf("越界错误！");
        return -1;
    }
    return node->val;
}

/*
 * Description：通过值寻找到链表中的节点
 * parameter L
 * parameter val：值
 * return：匹配的节点
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
 * Description：求链表长度
 * parameter L
 * return：链表长度
 */
int getLength(LinkList L) {
    return L->length;
}


/*
 * Description：遍历链表
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
    printf("头插法初始化：\n");
    LinkList L = initLinkListHead(a, sizeof(a) / sizeof(a[0]));
    traverse(L);
    printf("尾插法初始化：\n");
    L = initLinkListTail(a, sizeof(a) / sizeof(a[0]));
    traverse(L);
    printf("链表长度：%d\n", getLength(L));
    insert(L, getLength(L), 0);
    traverse(L);

    printf("链表长度：%d\n", getLength(L));
    l_delete(L, 1);
    traverse(L);

    printf("索引3处的节点值为%d\n", getVal(L, 3));

    return 0;
    return 0;
}