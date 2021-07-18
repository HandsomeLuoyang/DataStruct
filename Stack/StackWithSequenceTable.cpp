/*
-------------------------------------------------
   Author :       86178
   date:          2021/7/18 15:16
   Description :
-------------------------------------------------
*/
#include<bits/stdc++.h>

using namespace std;

/*
 * description: 栈结构体
 * attribute a: 存数据的数组指针
 * attribute top; 栈顶指针
 * attribute capacity: 栈容量
 */
typedef struct Stack {
    int *arr;
    int top;
    int capacity;
} Stack;

/*
 * description:栈的初始化
 * parameter capacity: 栈的容量
 * return: 栈指针
 */
Stack *initStack(int capacity) {
    // Question: 这里到底分配了多少空间给栈？因为a只是个指针，还并没有确定分配的空间大小
    // Answer: 只有16个，其中指针占8个（在64位系统中所有类型指针固定占8个，在32位中占4个），两个int各占4个
    //         并不需要去考虑指针分配的空间，因为指针是在系统栈里创建的，而当为指针分配空间的时候，是到堆里面去分配数组的

    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack->arr = (int *) malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

/*
 * Description：判满函数
 */
bool isFull(Stack *stack) {
    return stack->top == stack->capacity - 1;
}

/*
 * description: 栈的压入函数
 * parameter val: 要压入的值
 */
bool push(Stack *stack, int val) {
    if (isFull(stack)) return false;
    stack->arr[++stack->top] = val;
    return true;
}


/*
 * description:返回栈顶元素
 */
int getTop(Stack *stack) {
    return stack->arr[stack->top];
}

/*
 * Description：判空
 */
bool isEmpty(Stack *stack) {
    return stack->top == -1;
}


/*
 * Description：弹出栈顶元素并返回
 * return：栈顶元素
 */
int pop(Stack *stack) {
    if (isEmpty(stack)) return false;
    return stack->arr[stack->top--];
}

/*
 * Description：销毁栈
 */
void destroy(Stack *stack) {
    free(stack->arr);
    free(stack);
}


/*
 * Description：测试函数，并不属于栈的操作
 */
void testTraver(Stack *stack) {
    for (int i = 0; i <= stack->top; i++) {
        cout << stack->arr[i] << " ";
    }
    cout << endl;
}


int main() {
    Stack *stack = initStack(10);
    pop(stack);
    push(stack, 10);

    for (int i = 0; i < 10; ++i) {
        push(stack, i);
    }
    testTraver(stack);
    for (int i = 0; i < 4; ++i) {
        pop(stack);
    }
    testTraver(stack);
    return 0;
}