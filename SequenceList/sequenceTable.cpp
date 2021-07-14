/*
-------------------------------------------------
   Author :       86178
   date:          2021/7/14 10:52
   Description :
-------------------------------------------------
*/
#include<bits/stdc++.h>

using namespace std;
const int MAXSIZE = 100;

// 定义顺序表结构体
typedef struct {
    int *data;
    int MaxSize;
    int curSize;
} Sequence;

/*
 * isFull函数
 * parameter L:顺序表指针
 * return : 顺序表是否为满
 */
bool isFull(Sequence *L) {
    return L->curSize == L->MaxSize;
}

/*
 * parameter L:顺序表指针
 * return: 是否为空
 */
bool isEmpty(Sequence *L) {
    return L->curSize == 0;
}

/*
 * parameter L
 * parameter val:要追加的值
 * return 是否插入成功
 */
bool append(Sequence *L, int val) {
    if (!isFull(L)) {
        L->data[L->curSize++] = val;
        return true;
        L->curSize++;
    }
    return false;
}

/*
 * parameter L
 * parameter index: 要插入的位置，从0开始
 * parameter val:要插入的值
 * return 是否插入成功
 */
bool insert(Sequence *L, int index, int val) {
    if (!isFull(L) && 0 <= index && index < L->MaxSize) {
        for (int i = L->curSize - 1; i >= index; i--) {
            L->data[i + 1] = L->data[i];
        }
        L->data[index] = val;
        L->curSize++;
        return true;
    }
    return false;
}

/*
 * parameter L is a sequence
 * parameter index：要获取的位置
 * return 值或者报错（-1）
 */
int get(Sequence *L, int index) {
    if (0 <= index && index < L->curSize) {
        return L->data[index];
    }
    printf("读取数据出错!\n");
    return -1;
}

/*
 * parameter L
 * parameter index：要删除的索引，从0开始
 * return 是否成功删除
 */
bool s_delete(Sequence *L, int index) {
    if (!isEmpty(L) && 0 <= index && index < L->curSize) {
        for (int i = index; i < L->curSize; i++) {
            L->data[i] = L->data[i + 1];
        }
        L->curSize--;
    }
    return false;
}

/*
 * parameter L
 * parameter val：要查找的值
 * return 如果查找到返回索引最小的那个，否则返回-1
 */
int find(Sequence* L, int val)
{
    for (int i = 0;i<L->curSize;i++)
    {
        if (L->data[i] == val) return i;
    }
    return -1;
}

/*
 * parameter L
 * 遍历顺序表
 * return None
 */
void traverse(Sequence* L)
{
    for (int i = 0;i<L->curSize;i++){
        printf("%d ", L->data[i]);
    }
    printf("\n");
}

/*
 * parameter L
 * parameter size 新的数据的长度
 * description： 拓展顺序表的长度
 * return 原地修改，return None
 */
void expand(Sequence* L, int size)
{
    if (size <= L->MaxSize) return ;
    int* new_data = (int*)malloc(sizeof(int) * size);
    if (new_data == nullptr) return ;
    for(int i = 0;i<L->curSize;i++)
    {
        new_data[i] = L->data[i];
    }
    L->MaxSize = size;
    free(L->data);
    L->data = new_data;
}


int main() {
    Sequence *L = (Sequence *) malloc(sizeof(Sequence));
    L->MaxSize = MAXSIZE;
    L->data = (int *) malloc(L->MaxSize * sizeof(int));
    L->curSize = 0;

    append(L, 10);
    append(L, 20);
    append(L, 30);
    append(L, 40);
    printf("当前大小: %d\n", L->curSize);
    traverse(L);
    insert(L, 0, 2);
    printf("当前大小: %d\n", L->curSize);
    traverse(L);
    s_delete(L, 1);
    printf("当前大小: %d\n", L->curSize);
    traverse(L);
    printf("当前容量: %d\n", L->MaxSize);
    expand(L, 200);
    traverse(L);
    printf("当前容量: %d\n", L->MaxSize);
    return 0;
}