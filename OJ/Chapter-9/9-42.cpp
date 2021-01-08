#include <bits/stdc++.h>
using namespace std;

 
typedef struct Trie_node
{
	int count[26];                    // 统计单词前缀出现的次数
	struct Trie_node* next[26];   // 指向各个子树的指针
	bool exist;                   // 标记该结点处是否构成单词  
}TrieNode , *Trie;
 
void Trie_insert(Trie root, char* word);
TrieNode* createTrieNode();
int Trie_search(Trie root, char* word);
void getString(char* s,char &c);
void Node_search(Trie root,int level);
int getnum(void);
int space = 0;
int ternal;
TrieNode* createTrieNode()
{
	TrieNode* node = (TrieNode *)malloc(sizeof(TrieNode));
    memset(node->count,0,26*sizeof(int));
	//node->count = 0;
	node->exist = false;
	memset(node->next , 0 , sizeof(node->next));    // 初始化为空指针
	return node;
}
 
void Trie_insert(Trie root, char* word)
{
	Trie node = root;
	char *p = word;
	int id;
	while( *p )
	{
		id = *p - 'a';
		if(node->next[id] == NULL)
			node->next[id] = createTrieNode();
        node->count[id] += 1;
		node = node->next[id];
		++p;
	}
	node->exist = true;
}
 
// int Trie_search(Trie root, char* word)
// {
// 	Trie node = root;
// 	char *p = word;
//     int i=0;
// 	int id;
// 	while( *p )
// 	{
// 		id = *p - 'a';
// 		node = node->next[id];
// 		++p;
// 		if(node == NULL)
// 			return 0;
// 	}
// 	return node->count;
// }

void Node_search(Trie root,int level){
    if(level==ternal)
        return;
    Trie node = root;
    int id;
    for(id=0;id<26;id++)
        if(node->next[id]){
            if(node->count[id]){
                if(space)
                    printf(",");
                printf("%d",node->count[id]);
                space++;
            }
            Node_search(node->next[id],level+1);
        }
}

int main(void)
{
    Trie root = createTrieNode();     // 初始化字典树的根节点
    char str[12][12] ;
    int i = 0;
	bool flag = false;
    char c = '.';
    ternal = getnum();
	while(c!='\n' && c!=EOF)
	{
        getString(str[i],c);
        Trie_insert(root , str[i]);
        i++;
	}
    int count = i;
    Node_search(root,0);
    return 0;
}

void getString(char* s,char &c){
    int i=0;
    while((c=getchar())!=';' && c!=EOF && c!='\n')
        s[i++] = c;
    s[i] = '\0';
}

int getnum(void){
    char c;
    char m;
    int num = 0;
    int sign = 1;
    while((c=getchar())!=EOF && c!='\n' && isdigit(c)){
        if(c=='-')
            sign = -1;
        num = num*10 + c - '0';
    }
    if(c=='n'){
        m = getchar();
        m = getchar();
        m = getchar();
        c = getchar();
        return -1;
    }
    return num*sign;
}
