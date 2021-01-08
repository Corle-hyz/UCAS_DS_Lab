#include<stdio.h>
#include<ctype.h>
#include<stdbool.h>
#include<stdlib.h>

typedef struct a{
    char op;
    struct a* next;
}Stack,*pStack;

typedef struct b{
    char op;
    struct b* next;
}Queue,*pQueue;

pQueue line(pQueue rear,char c);
pStack push(pStack top,char c);
pStack pop(pStack top,char* back);
char gettop(pStack top);
bool prior(char c,char top);
void print(pQueue front);

int main(){
    char c,t;
    char tempt;
    char elemtop;
    char* back;
    back = &elemtop;
    c=getchar();
    pStack base,top;
    pQueue front,rear;
    base = (pStack)malloc(sizeof(Stack));
    top = base;
    front = (pQueue)malloc(sizeof(Queue));
    rear = front;
    base->next = NULL;
    front->next = NULL;
    while(c!=EOF && c!='\n'){
        if(isalnum(c))
            rear = line(rear,c);//操作数入队
        else if(c == '(')
            top = push(top,c);//括号无条件入栈
        else if(c == ')'){
            top = pop(top,back);
            while(elemtop != '('){
                rear = line(rear,elemtop);
                top = pop(top,back);
            }
        }
        else if(prior(c,gettop(top)))
            top = push(top,c);//优先级高的入栈
        else{
            top = pop(top,back);//优先级低的等高/同优先级的出栈再入栈
            rear = line(rear,elemtop);
            continue;
        }
        c = getchar();//读取下一个输入
    }
    while(top->next){
        top = pop(top,back);
        rear = line(rear,elemtop);//清栈
    }
    print(front);//输出队列
    return 0;
}

pQueue line(pQueue rear,char c){
    pQueue temp;
    temp = (pQueue)malloc(sizeof(Queue));
    rear->op = c;
    rear->next = temp;
    rear = temp;
    temp->next = NULL;
    return rear;
}

pStack push(pStack top,char c){
    pStack temp;
    temp = (pStack)malloc(sizeof(Stack));
    top->op = c;
    temp->next = top;//栈顶指针所指结点未初始化
    top = temp;
    return top;
}

pStack pop(pStack top,char* back){//top实际上没有下移---how to solve?
    pStack temp = top;
    (*back) = top->next->op;//将栈顶指针所指的下一个元素出栈，指针下移
    top = top->next;
    free(temp);
    return top;
}

char gettop(pStack top){
    return top->next?top->next->op:'$';//返回栈顶指针所指的下一个元素的值
}

bool prior(char c,char top){//判断优先级
    if(((c=='*'||c=='/') && (top=='+'||top=='-')) || top=='$' || top=='(')
        return true;
    else
        return false;
}

void print(pQueue front){
    while(front->next){
        printf("%c",front->op);
        front = front->next;
    }
}
