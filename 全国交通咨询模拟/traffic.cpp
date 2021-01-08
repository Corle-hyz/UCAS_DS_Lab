#include <bits/stdc++.h>
using namespace std;
#define MAXVEX 100 		//图中最大的顶点数 
void editEdgeFromFile(struct graph *g);
void editEdgeFromUser(struct graph *g);
void editCityFromUser(struct graph *gt,struct graph *ga);
void editCityFromFile(struct graph *gt,struct graph *ga);
int getnum(int &i,char* tempstr);
void buileFromUser(struct graph *g);
void buileFromFile(struct graph *g);
void initializeGraph(struct graph *g);
void city_edit(struct graph *gt,struct graph *ga);
void edge_edit(struct graph *g);
void buildgraph(struct graph *g);

struct edgeinfo{		//车次或者航班的信息 
	int ivex;			//起点城市号 
	int jvex;			//终点城市号 
	char number[10];	//车次号 
	int money;			//$ 
	int starttime;		//出发时间（用一天中的分钟表示：比如7：30为450） 
	int endtime;		//到达时间（同上） 
	int time;			//中途时间 
};

struct edgenode{		//边 
	struct edgeinfo elem;
	struct edgenode *nextedge;
}*p;

struct vnode{			//城市信息 
	char *cityname;				
	int citynumber;
	struct edgenode *firstedge;
};

struct graph{			//图的结构 
	struct vnode adjlist[MAXVEX];	//邻接表 
	int vexnum,edgenum;	//图中的顶点数和边数 
	int flag[MAXVEX];	//标记是否为图中节点，0表示不是 
};


void dijkstra_money(struct graph* g,int x,struct edgenode pre[]){
	int n=g->vexnum;
	int t[MAXVEX],d[MAXVEX],endtime[MAXVEX];
	for(int i=0;i<n;i++) d[i]=99999;
	d[x]=0; endtime[x]=-1; int min_d,num;
	for(int i=0;i<n;i++){													
		min_d=99999;
		for(int j=0;j<n;j++)									
			if(t[j]!=1&&g->flag[j]==1&&d[j]<min_d){min_d=d[j];num=j;}
		t[num]=1;
		for(p=g->adjlist[num].firstedge->nextedge;p!=NULL;p=p->nextedge){
			if(p->elem.starttime<endtime[num]) continue;
			if(d[num]+p->elem.money<d[p->elem.jvex]){
				d[p->elem.jvex]=d[num]+p->elem.money;
				pre[p->elem.jvex]=*p;
				endtime[p->elem.jvex]=p->elem.endtime;
			}
		} 
	}
}

void inquire_money(struct graph* gt,struct graph* ga){
	int st,end;
	struct edgenode pre[MAXVEX];
	while(1){
		int a=5;
		cout<<endl;
		cout<<"==================================="<<endl;
		cout<<"\t咨询最省钱到达\t"<<endl;
		cout<<"1:查询火车"<<endl;
		cout<<"2:查询飞机"<<endl;
		cout<<"0:退出"<<endl;
		cout<<"==================================="<<endl;
		cout<<"请选择:";
		scanf("%d",&a);
		if(a==1){
			char c[10];
			cout<<endl<<"请输入起点:"; scanf("%s",c);
			for(int i=0;i<gt->vexnum;i++){								 
				if(strcmp(c,gt->adjlist[i].cityname)==0){st=i; break;}
			}
			cout<<endl<<"请输入终点:"; scanf("%s",c);
			for(int i=0;i<gt->vexnum;i++){								
				if(strcmp(c,gt->adjlist[i].cityname)==0){end=i; break;}
			}
			dijkstra_money(gt,st,pre);
			int k=end;
			struct edgenode list[MAXVEX];
			int len=0;
			while(k!=st){
				list[++len]=pre[k];
				k=pre[k].elem.ivex;
			}
			cout<<"最省钱路径:"<<endl; 
			for(int i=len;i>=1;i--){
				cout<<"车次号:"<<list[i].elem.number;
				cout<<"\t"<<gt->adjlist[list[i].elem.ivex].cityname<<"--"<<gt->adjlist[list[i].elem.jvex].cityname;
				cout<<"\t起止时间:";
				printf("%02d",list[i].elem.starttime/60);
				cout<<":";
				printf("%02d",list[i].elem.starttime%60);
				cout<<"--";
				printf("%02d",list[i].elem.endtime/60);
				cout<<":";
				printf("%02d",list[i].elem.endtime%60);
				cout<<"\t价钱:"<<list[i].elem.money<<endl; 
			}
			break; 
		}else if(a==2){
			char c[10];
			cout<<endl<<"请输入起点:"; scanf("%s",c);
			for(int i=0;i<ga->vexnum;i++){							
				if(strcmp(c,ga->adjlist[i].cityname)==0){st=i; break;}
			}
			cout<<endl<<"请输入终点:"; scanf("%s",c);
			for(int i=0;i<ga->vexnum;i++){								
				if(strcmp(c,ga->adjlist[i].cityname)==0){end=i; break;}
			}
			dijkstra_money(ga,st,pre);
			int k=end;
			struct edgenode list[MAXVEX];
			int len=0;
			while(k!=st){
				list[++len]=pre[k];
				k=pre[k].elem.ivex;
			}
			cout<<"最省钱路径:"<<endl; 
			for(int i=len;i>=1;i--){
				cout<<"航班号:"<<list[i].elem.number;
				cout<<"\t"<<ga->adjlist[list[i].elem.ivex].cityname<<"--"<<ga->adjlist[list[i].elem.jvex].cityname;
				cout<<"\t起止时间:";
				printf("%02d",list[i].elem.starttime/60);
				cout<<":";
				printf("%02d",list[i].elem.starttime%60);
				cout<<"--";
				printf("%02d",list[i].elem.endtime/60);
				cout<<":";
				printf("%02d",list[i].elem.endtime%60);
				cout<<"\t价钱:"<<list[i].elem.money<<endl; 
			}
			break; 
		}else if(a==0){
			break;
		}else{
			cout<<endl<<"输入有误，请重试。"<<endl;
		}
	}
}

void dijkstra_time(struct graph* g,int x,struct edgenode pre[]){
	int n=g->vexnum;
	int t[MAXVEX],d[MAXVEX],endtime[MAXVEX];		//t表示有没有锁定，d表示最短时间，endtime表示到达时间 
	for(int i=0;i<n;i++) d[i]=99999;
	d[x]=0; endtime[x]=-1; int min_d,num;
	for(int i=0;i<n;i++){												
		min_d=99999;
		for(int j=0;j<n;j++)								
			if(t[j]!=1&&g->flag[j]==1&&d[j]<min_d){min_d=d[j];num=j;}
		t[num]=1;
		for(p=g->adjlist[num].firstedge->nextedge;p!=NULL;p=p->nextedge){
			if(p->elem.starttime<endtime[num]) continue;
			if(d[num]+p->elem.time<d[p->elem.jvex]){
				d[p->elem.jvex]=d[num]+p->elem.time;
				pre[p->elem.jvex]=*p;
				endtime[p->elem.jvex]=p->elem.endtime;
			}
		} 
	}
}

void inquire_time(struct graph* gt,struct graph* ga){
	int st,end;
	struct edgenode pre[MAXVEX]; 
	while(1){
		int a=5;
		cout<<endl;
		cout<<"==================================="<<endl;
		cout<<"\t咨询最快到达\t"<<endl;
		cout<<"1:查询火车"<<endl;
		cout<<"2:查询飞机"<<endl;
		cout<<"0:退出"<<endl;
		cout<<"==================================="<<endl;
		cout<<"请选择:";
		scanf("%d",&a);
		if(a==1){
			char c[10];
			cout<<endl<<"请输入起点:"; scanf("%s",c);
			for(int i=0;i<gt->vexnum;i++){							
				if(strcmp(c,gt->adjlist[i].cityname)==0){st=i; break;}
			}
			cout<<endl<<"请输入终点:"; scanf("%s",c);
			for(int i=0;i<gt->vexnum;i++){							
				if(strcmp(c,gt->adjlist[i].cityname)==0){end=i; break;}
			}
			dijkstra_time(gt,st,pre);
			int k=end;
			struct edgenode list[MAXVEX];
			int len=0;
			while(k!=st){
				list[++len]=pre[k];
				k=pre[k].elem.ivex;
			}
			cout<<"最快路径:"<<endl; 
			for(int i=len;i>=1;i--){
				cout<<"车次号:"<<list[i].elem.number;
				cout<<"\t"<<gt->adjlist[list[i].elem.ivex].cityname<<"--"<<gt->adjlist[list[i].elem.jvex].cityname;
				cout<<"\t起止时间:";
				printf("%02d",list[i].elem.starttime/60);
				cout<<":";
				printf("%02d",list[i].elem.starttime%60);
				cout<<"--";
				printf("%02d",list[i].elem.endtime/60);
				cout<<":";
				printf("%02d",list[i].elem.endtime%60);
				cout<<"\t价钱:"<<list[i].elem.money<<endl; 
			}
			break; 
		}else if(a==2){
			char c[10];
			cout<<endl<<"请输入起点:"; scanf("%s",c);
			for(int i=0;i<ga->vexnum;i++){							
				if(strcmp(c,ga->adjlist[i].cityname)==0){st=i; break;}
			}
			cout<<endl<<"请输入终点:"; scanf("%s",c);
			for(int i=0;i<ga->vexnum;i++){							
				if(strcmp(c,ga->adjlist[i].cityname)==0){end=i; break;}
			}
			dijkstra_time(ga,st,pre);
			int k=end;
			struct edgenode list[MAXVEX];
			int len=0;
			while(k!=st){
				list[++len]=pre[k];
				k=pre[k].elem.ivex;
			}
			cout<<"最快路径:"<<endl; 
			for(int i=len;i>=1;i--){
				cout<<"航班号:"<<list[i].elem.number;
				cout<<"\t"<<ga->adjlist[list[i].elem.ivex].cityname<<"--"<<ga->adjlist[list[i].elem.jvex].cityname;
				cout<<"\t起止时间:";
				printf("%02d",list[i].elem.starttime/60);
				cout<<":";
				printf("%02d",list[i].elem.starttime%60);
				cout<<"--";
				printf("%02d",list[i].elem.endtime/60);
				cout<<":";
				printf("%02d",list[i].elem.endtime%60);
				cout<<"\t价钱:"<<list[i].elem.money<<endl; 
			}
			break; 
		}else if(a==0){
			break;
		}else{
			cout<<endl<<"输入有误，请重试。"<<endl;
		}
	}
}

void inquire_menu(struct graph* gt,struct graph* ga){
	while(1){
		int a=5;
		cout<<endl;
		cout<<"==================================="<<endl;
		cout<<"\t咨询系统\t"<<endl;
		cout<<"1:最省钱咨询"<<endl;
		cout<<"2:最快到达咨询"<<endl;
		cout<<"0:退出"<<endl;
		cout<<"==================================="<<endl;
		cout<<"请选择:";
		scanf("%d",&a);
		switch(a){
			case 1: inquire_money(gt,ga);break;
			case 2: inquire_time(gt,ga);break;
			case 0: return;
			default: cout<<endl<<"输入有误，请重试。"<<endl;
		}	
	}
}



void manage_menu(struct graph* gt,struct graph* ga){
	while(1){
		int a=5;
		cout<<endl;
		cout<<"==================================="<<endl;
		cout<<"\t管理系统\t"<<endl;
		cout<<"1:城市编辑"<<endl;
		cout<<"2:列车时刻表编辑"<<endl;
		cout<<"3:航班时刻表编辑"<<endl;
		cout<<"0:退出"<<endl;
		cout<<"==================================="<<endl;
		cout<<"请选择:";
		scanf("%d",&a);
		switch(a){
			case 1: city_edit(gt,ga);break;	
			case 2: edge_edit(gt);break;	
			case 3: edge_edit(ga);break;		
			case 0: return;
			default: cout<<"输入有误，请重试"<<endl;
		}
	}
}

void main_menu(struct graph* gt,struct graph* ga){
	while(1){ 
		int a=3;
		cout<<endl;
		cout<<"==================================="<<endl;
		cout<<"\t全国交通咨询系统\t"<<endl;
		cout<<"1:咨询系统"<<endl;
		cout<<"2:管理系统"<<endl;
		cout<<"0:退出"<<endl;
		cout<<"==================================="<<endl;
		cout<<"请选择:";
		scanf("%d",&a);
		switch(a){
			case 1: inquire_menu(gt,ga);break;
			case 2: manage_menu(gt,ga);break;
			case 0: return;
			default: cout<<endl<<"输入有误，请重试。"<<endl;
		}
	}
}


int main(){
	struct graph gt;	//火车交通图 
	struct graph ga;		//飞机交通图 
	buildgraph(&gt);			//建立火车交通图 		
	buildgraph(&ga);			//建立飞机交通图 
	main_menu(&gt,&ga);
	return 0;
}









#define MAXL 100
/*删除城市时仅仅将其flag设置为0，没有删除与之相关联的边*/
void city_edit(struct graph* gt,struct graph* ga){
	cout<<"==================================="<<endl;
	cout<<"选择修改模式"<<endl<<"\t1：用户输入"<<endl<<"\t2：文件输入"<<endl<<"\t3：退出"<<endl;
	int mode;
	scanf("%d",&mode);
	switch (mode)
	{
	case 0:
		break;
	case 1:
		editCityFromUser(gt,ga);
		break;
	case 2:
		editCityFromFile(gt,ga);
		break;
	default:
		cout<<"输入错误，已退出编辑，请重新尝试"<<endl;
		cout<<"==================================="<<endl;
		return;
	}
	cout<<"==================================="<<endl;
}

void edge_edit(struct graph* g){
	cout<<"==================================="<<endl;
	cout<<"选择修改模式"<<endl<<"\t1：用户输入"<<endl<<"\t2：文件输入"<<endl<<"\t3：退出"<<endl;
	int mode;
	scanf("%d",&mode);
	switch (mode)
	{
	case 0:
		break;
	case 1:
		editEdgeFromUser(g);
		break;
	case 2:
		editEdgeFromFile(g);
		break;
	default:
		cout<<"输入错误，已退出编辑，请重新尝试"<<endl;
		cout<<"==================================="<<endl;
		return;
	}
	cout<<"==================================="<<endl;
}

void initializeGraph(struct graph* g){
	int i;
	for(i=0;i<MAXVEX;i++){
		g->flag[i] = 0;
		g->adjlist[i].citynumber = i;
		g->adjlist[i].firstedge = (struct edgenode*)malloc(sizeof(struct edgenode));
		g->adjlist[i].firstedge->nextedge = NULL;
		g->adjlist[i].firstedge->elem.ivex = -1;
	}
	cout<<"==================================="<<endl;
	cout<<"按顺序输入城市的名称，以'-1'结束"<<endl;
	cout<<"\tmode 1: 用户输入"<<endl<<"\tmode 2: 文件输入"<<endl;
	int mode;
	scanf("%d",&mode);
	int out = 0;
	while(!out){
		switch(mode){
			case 1:
				i = 0;
				while(1){
					scanf("%s",g->adjlist[i].cityname);
					if(g->adjlist[i].cityname[0]=='-'){
						out = 1;
						break;
					}
					g->flag[i] = 1;
				}
				break;
			case 2:
				cout<<"请输入文件位置："<<endl;
				char filePosition[MAXL];
				char tempstr[MAXL];
				FILE* fp;
				while(1){
					scanf("%s",filePosition);
					if((fp=fopen(filePosition,"r")) == NULL)
						cout<<"打开文件失败，请重新尝试"<<endl;
					else 
						break;
				}
				i = 0;
				while(fgets(tempstr,MAXL,fp)!=NULL){
					if(tempstr[0]=='-')
						break;
					else{
						g->flag[i] = 1;
						g->adjlist[i].firstedge->elem.ivex = i;
						g->adjlist[i].cityname = (char *)malloc((strlen(tempstr)) * sizeof(char));
						memcpy(g->adjlist[i].cityname,tempstr,strlen(tempstr)-1);
						g->adjlist[i].cityname[strlen(tempstr)-1] = '\0';
						i++;
					}
				}
				out = 1;
				fclose(fp);
				break;
			default:
				cout<<"输入有误，请重新输入"<<endl;
				cout<<"\tmode 1: 用户输入"<<endl<<"\tmode 2: 文件输入"<<endl;
				scanf("%d",&mode);
				out = 0;
				break;
		}
	}
	cout<<"城市名称输入结束"<<endl;
	cout<<"==================================="<<endl;
	g->vexnum = i--;
	g->edgenum = 0;
}

void buildgraph(struct graph* g){
	initializeGraph(g);
	int a=3;
	cout<<endl;
	cout<<"==================================="<<endl;
	cout<<"\t输入初始信息\t"<<endl;
	cout<<"1:用户输入"<<endl;
	cout<<"2:文件输入"<<endl;
	cout<<"0:退出"<<endl;
	cout<<"请选择:";
	scanf("%d",&a);
	switch(a){
		case 1: 
			buileFromUser(g);
			break;
		case 2: 
			buileFromFile(g);
			break;
		case 0: 
			cout<<"输入结束\n"<<"==================================="<<endl;
			return;
		default: cout<<endl<<"输入有误，请重试。"<<endl;
			buildgraph(g);
	}
}

void buileFromUser(struct graph* g){
	cout<<"==================================="<<endl;
	cout<<"请依次输入: 起点 终点 车次 票价 出发时间 到达时间\n"<<"输入以-1结束"<<endl;
	int edge=0,start=0;
	#define edgeinfo pointer->elem
	int count = 0;
	while(1){
		scanf("%d",&start);
		if(start==-1){
			cout<<"==================================="<<endl;
			return;
		}
		struct edgenode* pointer,*temp;
		if(!g->adjlist[start].firstedge)
			g->adjlist[start].firstedge = (struct edgenode*)malloc(sizeof(struct edgenode));
		temp = g->adjlist[start].firstedge->nextedge;
		pointer = (struct edgenode*)malloc(sizeof(struct edgenode));
		g->adjlist[start].firstedge->nextedge = pointer;
		pointer->nextedge = temp;
		edgeinfo.ivex = start;
		scanf("%d %s %d %d %d",&edgeinfo.jvex,edgeinfo.number,&edgeinfo.money,&edgeinfo.starttime,&edgeinfo.endtime);
		edgeinfo.time = edgeinfo.endtime - edgeinfo.starttime;
		count++;
	}
	g->edgenum = count;
}

void buileFromFile(struct graph* g){
	cout<<"==================================="<<endl;
	cout<<"请输入文件位置："<<endl;
	char filePosition[MAXL];
	char tempstr[MAXL];
	FILE* fp;
	while(1){
		scanf("%s",filePosition);
		if((fp=fopen(filePosition,"r")) == NULL)
			cout<<"打开文件失败，请重新尝试"<<endl;
		else 
			break;
	}
	#define edgeinfo pointer->elem
	int count = 0;
	while(fgets(tempstr,MAXL,fp)!=NULL){
		char c;
		int i=0,start=0;
		start = getnum(i,tempstr);
		struct edgenode* pointer, *temp;
		if(!g->adjlist[start].firstedge){
			g->adjlist[start].firstedge = (struct edgenode*)malloc(sizeof(struct edgenode));
			g->adjlist[start].firstedge->nextedge = NULL;
		}
		pointer = NULL;
		temp = g->adjlist[start].firstedge->nextedge;
		pointer = (struct edgenode*)malloc(sizeof(struct edgenode));
		g->adjlist[start].firstedge->nextedge = pointer;
		pointer->nextedge = temp;
		edgeinfo.ivex = start;
		edgeinfo.jvex = getnum(i,tempstr);
		int j=0;
		while(isalnum(tempstr[i]))
			edgeinfo.number[j++] = tempstr[i++];
		i++;
		edgeinfo.money = getnum(i,tempstr);
		edgeinfo.starttime = getnum(i,tempstr);
		edgeinfo.endtime = getnum(i,tempstr);
		edgeinfo.time = edgeinfo.endtime - edgeinfo.starttime;
		count++;
	}
	fclose(fp);
	g->edgenum = count;
	cout<<"==================================="<<endl;
	return;
}

int getnum(int &i,char* tempstr){
	char c;
	int num = 0,sign = 1;
	while((c=tempstr[i++])!=' ' && (isdigit(c) || c=='-')){
			if(c=='-')
				sign = -1;
			num = num*10 + c - '0';
	}
	return num*sign;
}

void editCityFromUser(struct graph* gt,struct graph* ga){
	cout<<"==================================="<<endl;
	cout<<"请依次输入 操作 城市名"<<endl<<"(其中1代表插入，0代表删除)"<<endl;
	cout<<"输入以2开头结束"<<endl;
	int op;
	char cityname[10];
	while(1){
		scanf("%d",&op);
		if(op==2){
			cout<<"输入结束"<<endl;
			return;
		}
		scanf("%s",cityname);
		int i=0;
		switch(op){
			case 0: 
				for(;i<gt->vexnum;i++){
					if(!strcmp(cityname,gt->adjlist[i].cityname))
						break;
					else if(i==gt->vexnum-1){
						cout<<"城市不存在，请重新尝试"<<endl;
						cout<<"==================================="<<endl;
						return;
					}
				}
				gt->flag[i] = 0;
				ga->flag[i] = 0;
				gt->vexnum--;
				ga->vexnum--;
				break;
			case 1:
				gt->flag[gt->vexnum] = 1;
				ga->flag[ga->vexnum] = 1;
				gt->adjlist[gt->vexnum].cityname = (char*)malloc(sizeof(cityname));
				ga->adjlist[gt->vexnum].cityname = (char*)malloc(sizeof(cityname));
				memcpy(gt->adjlist[gt->vexnum].cityname,cityname,sizeof(cityname));
				memcpy(ga->adjlist[ga->vexnum].cityname,cityname,sizeof(cityname));
				gt->vexnum++;
				ga->vexnum++;
				break;
			case 2:
				cout<<"输入结束"<<endl;
				cout<<"==================================="<<endl;
				return;
			default:
				cout<<"输入有误，请重新输入"<<endl;
				break;
		}
	}
}

//需要输入 操作 城市名
void editCityFromFile(struct graph* gt,struct graph* ga){
	cout<<"==================================="<<endl;
	cout<<"请输入文件位置："<<endl;
	char filePosition[MAXL];
	char tempstr[MAXL];
	FILE* fp;
	while(1){
		scanf("%s",filePosition);
		if((fp=fopen(filePosition,"r")) == NULL)
			cout<<"打开文件失败，请重新尝试"<<endl;
		else 
			break;
	}
	#define edgeinfo pointer->elem
	while(fgets(tempstr,MAXL,fp)!=NULL){
		int i=0,j=0,mode;
		char cityname[MAXL];
		mode = getnum(i,tempstr);
		while(isalnum(tempstr[i]))
			cityname[j++] = tempstr[i++];
		int k=0; 
		switch(mode){
			case 0:
				for(;k<gt->vexnum;k++){
					if(!strcmp(cityname,gt->adjlist[k].cityname))
						break;
					else if(k==gt->vexnum-1){
						cout<<"城市不存在，请重新尝试"<<endl;
						return;
					}
				}
				gt->flag[k] = 0;
				ga->flag[k] = 0;
				gt->vexnum--;
				ga->vexnum--;
				break;
			case 1:
				gt->flag[gt->vexnum] = 1;
				ga->flag[ga->vexnum] = 1;
				gt->adjlist[gt->vexnum].cityname = (char*)malloc(sizeof(cityname));
				ga->adjlist[ga->vexnum].cityname = (char*)malloc(sizeof(cityname));
				memcpy(gt->adjlist[gt->vexnum].cityname,cityname,sizeof(cityname));
				memcpy(ga->adjlist[ga->vexnum].cityname,cityname,sizeof(cityname));
				gt->vexnum++;
				ga->vexnum++;
				break;
			case 2:
				cout<<"输入结束"<<endl;
				cout<<"==================================="<<endl;
				fclose(fp);
				return;
			default:
				cout<<"输入有误，请重新输入"<<endl;
				break;
		}
	}
	fclose(fp);
	return;
}

void editEdgeFromUser(struct graph* g){
	cout<<"==================================="<<endl;
	cout<<"请依次输入: 操作 起点 终点 车次 票价 出发时间 到达时间"<<endl<<"(其中1代表插入，0代表删除)"<<endl;
	cout<<"输入以2开头结束"<<endl;
	int op,startcity,endcity,price,starttime,endtime;
	char cityname[10];
	char number[MAXL];
	while(1){
		scanf("%d",&op);
		if(op==2){
			cout<<"输入结束"<<endl;
			return;
		}
		int i=0;
		scanf("%s",cityname);
		for(i=0;i<g->vexnum;i++){
			if(!strcmp(cityname,g->adjlist[i].cityname))
				break;
			else if(i==g->vexnum-1){
				cout<<"城市不存在，请重新尝试"<<endl;
				cout<<"==================================="<<endl;
				return;
			}
		}
		startcity = i;
		scanf("%s",cityname);
		for(i=0;i<g->vexnum;i++){
			if(!strcmp(cityname,g->adjlist[i].cityname))
				break;
			else if(i==g->vexnum-1){
				cout<<"城市不存在，请重新尝试"<<endl;
				cout<<"==================================="<<endl;
				return;
			}
		}
		endcity = i;
		scanf("%s %d %d %d",number,&price,&starttime,&endtime);
		switch(op){
			case 0:
				struct edgenode* pre,*next;
				pre = g->adjlist[startcity].firstedge;
				while(pre->nextedge!=NULL){
					if(strcmp(number,pre->nextedge->elem.number))
						break;
					else 
						pre = pre->nextedge;
				}
				next = pre->nextedge;
				pre->nextedge = next->nextedge;
				free(next);
				g->edgenum--;
				break;
			case 1:
				struct edgenode* pointer,*temp;
				pointer = g->adjlist[startcity].firstedge->nextedge;
				temp = (struct edgenode*)malloc(sizeof(struct edgenode));
				temp->elem.ivex = startcity; temp->elem.jvex = endcity; memcpy(temp->elem.number,number,sizeof(number));
				temp->elem.money = price; temp->elem.starttime = starttime; temp->elem.endtime = endtime;
				temp->elem.time = endtime - starttime;
				g->adjlist[startcity].firstedge->nextedge = temp;
				temp->nextedge = pointer;
				g->edgenum++;
				break;
			case 2:
				cout<<"输入结束"<<endl;
				cout<<"==================================="<<endl;
				return;
			default:
				cout<<"输入有误，请重新输入"<<endl;
				break;
		}
	}
}

void editEdgeFromFile(struct graph* g){
	cout<<"==================================="<<endl;
	cout<<"请输入文件位置："<<endl;
	char filePosition[MAXL];
	char tempstr[MAXL];
	FILE* fp;
	while(1){
		scanf("%s",filePosition);
		if((fp=fopen(filePosition,"r")) == NULL)
			cout<<"打开文件失败，请重新尝试"<<endl;
		else 
			break;
	}
	#define edgeinfo pointer->elem
	while(fgets(tempstr,MAXL,fp)!=NULL){
		int i=0,j=0;
		int op;
		char number[MAXL];
		struct edgenode* store;
		store = (struct edgenode*)malloc(sizeof(struct edgenode));
		char cityname[10];
		op = getnum(i,tempstr);
		while(isalnum(tempstr[i]))
			cityname[j++] = tempstr[i++];
		cityname[j] = '\0';
		int q;
		for(q=0;q<g->vexnum;q++){
			if(!strcmp(cityname,g->adjlist[q].cityname))
				break;
			else if(q==g->vexnum-1){
				cout<<"城市不存在，请重新尝试"<<endl;
				cout<<"==================================="<<endl;
				return;
			}
		}
		store->elem.ivex = q;
		j = 0;
		i++;
		while(isalnum(tempstr[i]))
			cityname[j++] = tempstr[i++];
		cityname[j] = '\0';
		for(q=0;q<g->vexnum;q++){
			if(!strcmp(cityname,g->adjlist[q].cityname))
				break;
			else if(q==g->vexnum-1){
				cout<<"城市不存在，请重新尝试"<<endl;
				cout<<"==================================="<<endl;
				return;
			}
		}
		store->elem.jvex = q;
		i++;
		while(isalnum(tempstr[i]))
			store->elem.number[j++] = tempstr[i++];
		i++;
		store->elem.money = getnum(i,tempstr);
		store->elem.starttime = getnum(i,tempstr);
		store->elem.endtime = getnum(i,tempstr);
		store->elem.time = store->elem.endtime - store->elem.starttime;
		switch(op){
			case 0:
				struct edgenode* pre,*next;
				pre = g->adjlist[store->elem.ivex].firstedge;
				while(pre->nextedge!=NULL){
					if(strcmp(store->elem.number,pre->nextedge->elem.number))
						break;
					else 
						pre = pre->nextedge;
				}
				next = pre->nextedge;
				pre->nextedge = next->nextedge;
				free(next);
				g->edgenum--;
				break;
			case 1:
				struct edgenode* temp;
				temp = g->adjlist[store->elem.ivex].firstedge->nextedge;
				g->adjlist[store->elem.ivex].firstedge->nextedge = store;
				store->nextedge = temp;
				g->edgenum++;
				break;
			case 2:
				cout<<"输入结束"<<endl;
				cout<<"==================================="<<endl;
				fclose(fp);
				return;
			default:
				cout<<"输入有误，请重新输入"<<endl;
				break;
		}
	}
	fclose(fp);
	return;
}

