#include<stdio.h>
#include <string.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct word{
	union{
		word* llink;
		word* uplink;
	};
	int tag;
	int size;
	struct word* rlink;
	int other;
}word, head, foot, *Space;

#define FootLoc(p) p+p->size-1

int main(){
	Space pav;
	createSpace(pav);
	insertRelease();
	confirmSpace();
	return 0;
}

void createSpace(Space pav){
	int tag,pos,size;
	while(scanf("%d %d %d",&tag,&pos,&size) != EOF){
		switch(tag){
			case 1:
				;
			case 0:
				if(!pav)
					pav = (Space)malloc(sizeof(word));
					pav->tag = ;
			default:
				break;
		}
	}
}

Space AllocBoundTag(Space *pav,int n){
    Space p,f;
    int e=10;//设定常亮 e 的值
    //如果在遍历过程，当前空闲块的在存储容量比用户申请空间 n 值小，在该空闲块有右孩子的情况下直接跳过
    for (p=(*pav); p&&p->size<n&&p->rlink!=(*pav); p=p->rlink);
    //跳出循环，首先排除p为空和p指向的空闲块容量小于 n 的情况
    if (!p ||p->size<n) {
        return NULL;
    }else{
        //指针f指向p空闲块的foot域
        f=FootLoc(p);
        //调整pav指针的位置，为下次分配做准备
        (*pav)=p->rlink;
        //如果该空闲块的存储大小比 n 大，比 n+e 小，负责第一种情况，将 p 指向的空闲块全部分配给用户
        if (p->size-n <= e) {
            if ((*pav)==p) {
                pav=NULL;
            }
            else{
                //全部分配用户，即从可利用空间表中删除 p 空闲块
                (*pav)->llink=p->llink;
                p->llink->rlink=(*pav);
            }
            //同时调整head域和foot域中的tag值
            p->tag=f->tag=1;
        }
        //否则，从p空闲块中拿出 大小为 n 的连续空间分配给用户，同时更新p剩余存储块中的信息。
        else{
            //更改分配块foot域的信息
            f->tag=1;
            p->size-=n;
            //f指针指向剩余空闲块 p 的底部
            f=FootLoc(p);
            f->tag=0;   f->uplink=p;
            p=f+1;//p指向的是分配给用户的块的head域，也就是该块的首地址
            p->tag=1;   p->size=n;
        }
        return p;
    }
}

void FreeBlock(head* p){
	if(!(p-1)->tag && !((p->size)+p)->tag){
		//设定p指针指向的为用户释放的空闲块
		p->tag=0;
		//f指针指向p空闲块的foot域
		Space f=FootLoc(p);
		f->uplink=p;
		f->tag=0;
		//如果pav指针不存在，证明可利用空间表为空，此时设置p为头指针，并重新建立双向循环链表
		if (!pav) {
			pav=p->llink=p->rlink=p;
		}else{
			//否则，在p空闲块插入到pav指向的空闲块的左侧
			Space q=pav->llink;
			p->rlink=pav;
			p->llink=q;
			q->rlink=pav->llink=p;
			pav=p;
		}
	}
	else if((p-1)->tag && !((p->size)+p)->tag){
		//常量 n 表示当前空闲块的存储大小
		int n=p->size;
		Space s=(p-1)->uplink;//p-1 为当前块的左侧块的foot域，foot域中的uplink指向的就是左侧块的首地址，s指针代表的是当前块的左侧存储块
		s->size+=n;//设置左侧存储块的存储容量
		Space f=p+n-1;//f指针指向的是空闲块 p 的foot域
		f->uplink=s;//这是foot域的uplink指针重新指向合并后的存储空间的首地址
		f->tag=0;//设置foot域的tag标记为空闲块
	}
	else if(!(p-1)->tag && ((p->size)+p)->tag){
		Space t=p+p->size;//t指针指向右侧空闲块的首地址
		p->tag=0;//初始化head域的tag值为0
		//找到t右侧空闲块的前驱结点和后继结点，用当前释放的空闲块替换右侧空闲块
		Space q=t->llink;
		p->llink=q; q->rlink=p;
		Space q1=t->rlink;
		p->rlink=q1; q1->llink=p;
		//更新释放块的size的值
		p->size+=t->size;
		//更改合并后的foot域的uplink指针的指向
		Space f=FootLoc(t);
		f->uplink=p;
	}
	else{
		int n=p->size;
		Space s=(p-1)->uplink;//找到释放内存块物理位置相邻的低地址的空闲块
		Space t=p+p->size;//找到物理位置相邻的高地址处的空闲块
		s->size+=n+t->size;//更新左侧空闲块的size的值
		//从可利用空间表中摘除右侧空闲块
		Space q=t->llink;
		Space q1=t->rlink;
		q->rlink=q1;
		q1->llink=q;
		//更新合并后的空闲块的uplink指针的指向
		Space f=FootLoc(t);
		f->uplink=s;
	}
}
