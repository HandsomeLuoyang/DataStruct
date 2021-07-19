/*
-------------------------------------------------
   Author :       86178
   date:          2021/7/18 16:16
   Description :
-------------------------------------------------
*/
#include<bits/stdc++.h>

using namespace std;

/*
 * ����ƥ����������
 */

/*
 * description: ջ�ṹ��
 * attribute a: �����ݵ�����ָ��
 * attribute top; ջ��ָ��
 * attribute capacity: ջ����
 */
typedef struct Stack {
    char *arr;
    int top;
    int capacity;
} Stack;

/*
 * description:ջ�ĳ�ʼ��
 * parameter capacity: ջ������
 * return: ջָ��
 */
Stack *initStack(int capacity) {
    // Question: ���ﵽ�׷����˶��ٿռ��ջ����Ϊaֻ�Ǹ�ָ�룬����û��ȷ������Ŀռ��С
    // Answer: ֻ��16��������ָ��ռ8������64λϵͳ����������ָ��̶�ռ8������32λ��ռ4����������int��ռ4��
    //         ������Ҫȥ����ָ�����Ŀռ䣬��Ϊָ������ϵͳջ�ﴴ���ģ�����Ϊָ�����ռ��ʱ���ǵ�������ȥ���������

    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack->arr = (char *) malloc(capacity * sizeof(char));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

/*
 * Description����������
 */
bool isFull(Stack *stack) {
    return stack->top == stack->capacity - 1;
}

/*
 * description: ջ��ѹ�뺯��
 * parameter val: Ҫѹ���ֵ
 */
bool push(Stack *stack, char val) {
    if (isFull(stack)) return false;
    stack->arr[++stack->top] = val;
    return true;
}


/*
 * description:����ջ��Ԫ��
 */
int getTop(Stack *stack) {
    return stack->arr[stack->top];
}

/*
 * Description���п�
 */
bool isEmpty(Stack *stack) {
    return stack->top == -1;
}


/*
 * Description������ջ��Ԫ�ز�����
 * return��ջ��Ԫ��
 */
int pop(Stack *stack) {
    if (isEmpty(stack)) return false;
    return stack->arr[stack->top--];
}

/*
 * Description������ջ
 */
void destroy(Stack *stack) {
    free(stack->arr);
    free(stack);
}


/*
 * Description�����Ժ�������������ջ�Ĳ���
 */
void testTraver(Stack *stack) {
    for (int i = 0; i <= stack->top; i++) {
        cout << stack->arr[i] << " ";
    }
    cout << endl;
}


bool ParenthesisMatching(string s) {
    // ����һ��ջ
    Stack *stk = initStack(s.size() + 1);
    for (int i = 0; i < s.length(); i++) {
        char temp_s = s[i];
        if (temp_s == '(' || temp_s == '{' || temp_s == '[') {
            push(stk, temp_s);
        } else {
            if (isEmpty(stk)) return false;
            char top = pop(stk);
            if ((top == '(' && temp_s == ')') || (top == '{' && temp_s == '}') || (top == '[' && temp_s == ']')) {

            } else {
                return false;
            }
        }
    }
    return isEmpty(stk);
}


int main() {
    cout << "�����������У�������(){}[]�����ַ���: ";
    string ss;
    cin >> ss;
    bool isSuccess = ParenthesisMatching(ss);
    if (isSuccess) cout << "ƥ��ɹ�" << endl;
    else cout << "ƥ��ʧ��" << endl;
    return 0;
}