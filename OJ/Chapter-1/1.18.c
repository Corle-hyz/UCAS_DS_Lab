#include<stdio.h>
#define MAXLEN 100
typedef struct
{
    char name;
    int man;
    int woman;
}data;
void initial();
void display(data dt);

data A,B,C,D,E;

int main()
{
    char school,gender,term;
    int score;
    initial();
    while(scanf(" %c %c %c %d",&term,&gender,&school,&score) != EOF)
    {
    	//fflush(stdin);
        switch(school)
        {
            case 'A':(gender == 'M')? (A.man+=score) : (A.woman+=score); break;
            case 'B':(gender == 'M')? (B.man+=score) : (B.woman+=score); break;
            case 'C':(gender == 'M')? (C.man+=score) : (C.woman+=score); break;
            case 'D':(gender == 'M')? (D.man+=score) : (D.woman+=score); break;
            case 'E':(gender == 'M')? (E.man+=score) : (E.woman+=score); break;
            default: printf("Error input!\n");
        }
    }
    display(A);
    display(B);
    display(C);
    display(D);
    display(E);
    return 0;
}

void initial()
{
    A.name = 'A';
    B.name = 'B';
    C.name = 'C';
    D.name = 'D';
    E.name = 'E';
    A.man = A.woman = B.man = B.woman = C.man = C.woman = D.man = D.woman = E.man = E.woman = 0;
}

void display(data dt)
{
    if(dt.man != 0)
        printf("%c M %d\n",dt.name,dt.man);
    if(dt.woman != 0)
        printf("%c F %d\n",dt.name,dt.woman);
    if(dt.man+dt.woman != 0)
        printf("%c %d\n",dt.name,dt.man+dt.woman);
}
