#include <bits/stdc++.h>
using namespace std;
#define MAXVEX 100 		//ͼ�����Ķ����� 
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

struct edgeinfo{		//���λ��ߺ������Ϣ 
	int ivex;			//�����к� 
	int jvex;			//�յ���к� 
	char number[10];	//���κ� 
	int money;			//$ 
	int starttime;		//����ʱ�䣨��һ���еķ��ӱ�ʾ������7��30Ϊ450�� 
	int endtime;		//����ʱ�䣨ͬ�ϣ� 
	int time;			//��;ʱ�� 
};

struct edgenode{		//�� 
	struct edgeinfo elem;
	struct edgenode *nextedge;
}*p;

struct vnode{			//������Ϣ 
	char *cityname;				
	int citynumber;
	struct edgenode *firstedge;
};

struct graph{			//ͼ�Ľṹ 
	struct vnode adjlist[MAXVEX];	//�ڽӱ� 
	int vexnum,edgenum;	//ͼ�еĶ������ͱ��� 
	int flag[MAXVEX];	//����Ƿ�Ϊͼ�нڵ㣬0��ʾ���� 
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
		cout<<"\t��ѯ��ʡǮ����\t"<<endl;
		cout<<"1:��ѯ��"<<endl;
		cout<<"2:��ѯ�ɻ�"<<endl;
		cout<<"0:�˳�"<<endl;
		cout<<"==================================="<<endl;
		cout<<"��ѡ��:";
		scanf("%d",&a);
		if(a==1){
			char c[10];
			cout<<endl<<"���������:"; scanf("%s",c);
			for(int i=0;i<gt->vexnum;i++){								 
				if(strcmp(c,gt->adjlist[i].cityname)==0){st=i; break;}
			}
			cout<<endl<<"�������յ�:"; scanf("%s",c);
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
			cout<<"��ʡǮ·��:"<<endl; 
			for(int i=len;i>=1;i--){
				cout<<"���κ�:"<<list[i].elem.number;
				cout<<"\t"<<gt->adjlist[list[i].elem.ivex].cityname<<"--"<<gt->adjlist[list[i].elem.jvex].cityname;
				cout<<"\t��ֹʱ��:";
				printf("%02d",list[i].elem.starttime/60);
				cout<<":";
				printf("%02d",list[i].elem.starttime%60);
				cout<<"--";
				printf("%02d",list[i].elem.endtime/60);
				cout<<":";
				printf("%02d",list[i].elem.endtime%60);
				cout<<"\t��Ǯ:"<<list[i].elem.money<<endl; 
			}
			break; 
		}else if(a==2){
			char c[10];
			cout<<endl<<"���������:"; scanf("%s",c);
			for(int i=0;i<ga->vexnum;i++){							
				if(strcmp(c,ga->adjlist[i].cityname)==0){st=i; break;}
			}
			cout<<endl<<"�������յ�:"; scanf("%s",c);
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
			cout<<"��ʡǮ·��:"<<endl; 
			for(int i=len;i>=1;i--){
				cout<<"�����:"<<list[i].elem.number;
				cout<<"\t"<<ga->adjlist[list[i].elem.ivex].cityname<<"--"<<ga->adjlist[list[i].elem.jvex].cityname;
				cout<<"\t��ֹʱ��:";
				printf("%02d",list[i].elem.starttime/60);
				cout<<":";
				printf("%02d",list[i].elem.starttime%60);
				cout<<"--";
				printf("%02d",list[i].elem.endtime/60);
				cout<<":";
				printf("%02d",list[i].elem.endtime%60);
				cout<<"\t��Ǯ:"<<list[i].elem.money<<endl; 
			}
			break; 
		}else if(a==0){
			break;
		}else{
			cout<<endl<<"�������������ԡ�"<<endl;
		}
	}
}

void dijkstra_time(struct graph* g,int x,struct edgenode pre[]){
	int n=g->vexnum;
	int t[MAXVEX],d[MAXVEX],endtime[MAXVEX];		//t��ʾ��û��������d��ʾ���ʱ�䣬endtime��ʾ����ʱ�� 
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
		cout<<"\t��ѯ��쵽��\t"<<endl;
		cout<<"1:��ѯ��"<<endl;
		cout<<"2:��ѯ�ɻ�"<<endl;
		cout<<"0:�˳�"<<endl;
		cout<<"==================================="<<endl;
		cout<<"��ѡ��:";
		scanf("%d",&a);
		if(a==1){
			char c[10];
			cout<<endl<<"���������:"; scanf("%s",c);
			for(int i=0;i<gt->vexnum;i++){							
				if(strcmp(c,gt->adjlist[i].cityname)==0){st=i; break;}
			}
			cout<<endl<<"�������յ�:"; scanf("%s",c);
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
			cout<<"���·��:"<<endl; 
			for(int i=len;i>=1;i--){
				cout<<"���κ�:"<<list[i].elem.number;
				cout<<"\t"<<gt->adjlist[list[i].elem.ivex].cityname<<"--"<<gt->adjlist[list[i].elem.jvex].cityname;
				cout<<"\t��ֹʱ��:";
				printf("%02d",list[i].elem.starttime/60);
				cout<<":";
				printf("%02d",list[i].elem.starttime%60);
				cout<<"--";
				printf("%02d",list[i].elem.endtime/60);
				cout<<":";
				printf("%02d",list[i].elem.endtime%60);
				cout<<"\t��Ǯ:"<<list[i].elem.money<<endl; 
			}
			break; 
		}else if(a==2){
			char c[10];
			cout<<endl<<"���������:"; scanf("%s",c);
			for(int i=0;i<ga->vexnum;i++){							
				if(strcmp(c,ga->adjlist[i].cityname)==0){st=i; break;}
			}
			cout<<endl<<"�������յ�:"; scanf("%s",c);
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
			cout<<"���·��:"<<endl; 
			for(int i=len;i>=1;i--){
				cout<<"�����:"<<list[i].elem.number;
				cout<<"\t"<<ga->adjlist[list[i].elem.ivex].cityname<<"--"<<ga->adjlist[list[i].elem.jvex].cityname;
				cout<<"\t��ֹʱ��:";
				printf("%02d",list[i].elem.starttime/60);
				cout<<":";
				printf("%02d",list[i].elem.starttime%60);
				cout<<"--";
				printf("%02d",list[i].elem.endtime/60);
				cout<<":";
				printf("%02d",list[i].elem.endtime%60);
				cout<<"\t��Ǯ:"<<list[i].elem.money<<endl; 
			}
			break; 
		}else if(a==0){
			break;
		}else{
			cout<<endl<<"�������������ԡ�"<<endl;
		}
	}
}

void inquire_menu(struct graph* gt,struct graph* ga){
	while(1){
		int a=5;
		cout<<endl;
		cout<<"==================================="<<endl;
		cout<<"\t��ѯϵͳ\t"<<endl;
		cout<<"1:��ʡǮ��ѯ"<<endl;
		cout<<"2:��쵽����ѯ"<<endl;
		cout<<"0:�˳�"<<endl;
		cout<<"==================================="<<endl;
		cout<<"��ѡ��:";
		scanf("%d",&a);
		switch(a){
			case 1: inquire_money(gt,ga);break;
			case 2: inquire_time(gt,ga);break;
			case 0: return;
			default: cout<<endl<<"�������������ԡ�"<<endl;
		}	
	}
}



void manage_menu(struct graph* gt,struct graph* ga){
	while(1){
		int a=5;
		cout<<endl;
		cout<<"==================================="<<endl;
		cout<<"\t����ϵͳ\t"<<endl;
		cout<<"1:���б༭"<<endl;
		cout<<"2:�г�ʱ�̱�༭"<<endl;
		cout<<"3:����ʱ�̱�༭"<<endl;
		cout<<"0:�˳�"<<endl;
		cout<<"==================================="<<endl;
		cout<<"��ѡ��:";
		scanf("%d",&a);
		switch(a){
			case 1: city_edit(gt,ga);break;	
			case 2: edge_edit(gt);break;	
			case 3: edge_edit(ga);break;		
			case 0: return;
			default: cout<<"��������������"<<endl;
		}
	}
}

void main_menu(struct graph* gt,struct graph* ga){
	while(1){ 
		int a=3;
		cout<<endl;
		cout<<"==================================="<<endl;
		cout<<"\tȫ����ͨ��ѯϵͳ\t"<<endl;
		cout<<"1:��ѯϵͳ"<<endl;
		cout<<"2:����ϵͳ"<<endl;
		cout<<"0:�˳�"<<endl;
		cout<<"==================================="<<endl;
		cout<<"��ѡ��:";
		scanf("%d",&a);
		switch(a){
			case 1: inquire_menu(gt,ga);break;
			case 2: manage_menu(gt,ga);break;
			case 0: return;
			default: cout<<endl<<"�������������ԡ�"<<endl;
		}
	}
}


int main(){
	struct graph gt;	//�𳵽�ͨͼ 
	struct graph ga;		//�ɻ���ͨͼ 
	buildgraph(&gt);			//�����𳵽�ͨͼ 		
	buildgraph(&ga);			//�����ɻ���ͨͼ 
	main_menu(&gt,&ga);
	return 0;
}









#define MAXL 100
/*ɾ������ʱ��������flag����Ϊ0��û��ɾ����֮������ı�*/
void city_edit(struct graph* gt,struct graph* ga){
	cout<<"==================================="<<endl;
	cout<<"ѡ���޸�ģʽ"<<endl<<"\t1���û�����"<<endl<<"\t2���ļ�����"<<endl<<"\t3���˳�"<<endl;
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
		cout<<"����������˳��༭�������³���"<<endl;
		cout<<"==================================="<<endl;
		return;
	}
	cout<<"==================================="<<endl;
}

void edge_edit(struct graph* g){
	cout<<"==================================="<<endl;
	cout<<"ѡ���޸�ģʽ"<<endl<<"\t1���û�����"<<endl<<"\t2���ļ�����"<<endl<<"\t3���˳�"<<endl;
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
		cout<<"����������˳��༭�������³���"<<endl;
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
	cout<<"��˳��������е����ƣ���'-1'����"<<endl;
	cout<<"\tmode 1: �û�����"<<endl<<"\tmode 2: �ļ�����"<<endl;
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
				cout<<"�������ļ�λ�ã�"<<endl;
				char filePosition[MAXL];
				char tempstr[MAXL];
				FILE* fp;
				while(1){
					scanf("%s",filePosition);
					if((fp=fopen(filePosition,"r")) == NULL)
						cout<<"���ļ�ʧ�ܣ������³���"<<endl;
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
				cout<<"������������������"<<endl;
				cout<<"\tmode 1: �û�����"<<endl<<"\tmode 2: �ļ�����"<<endl;
				scanf("%d",&mode);
				out = 0;
				break;
		}
	}
	cout<<"���������������"<<endl;
	cout<<"==================================="<<endl;
	g->vexnum = i--;
	g->edgenum = 0;
}

void buildgraph(struct graph* g){
	initializeGraph(g);
	int a=3;
	cout<<endl;
	cout<<"==================================="<<endl;
	cout<<"\t�����ʼ��Ϣ\t"<<endl;
	cout<<"1:�û�����"<<endl;
	cout<<"2:�ļ�����"<<endl;
	cout<<"0:�˳�"<<endl;
	cout<<"��ѡ��:";
	scanf("%d",&a);
	switch(a){
		case 1: 
			buileFromUser(g);
			break;
		case 2: 
			buileFromFile(g);
			break;
		case 0: 
			cout<<"�������\n"<<"==================================="<<endl;
			return;
		default: cout<<endl<<"�������������ԡ�"<<endl;
			buildgraph(g);
	}
}

void buileFromUser(struct graph* g){
	cout<<"==================================="<<endl;
	cout<<"����������: ��� �յ� ���� Ʊ�� ����ʱ�� ����ʱ��\n"<<"������-1����"<<endl;
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
	cout<<"�������ļ�λ�ã�"<<endl;
	char filePosition[MAXL];
	char tempstr[MAXL];
	FILE* fp;
	while(1){
		scanf("%s",filePosition);
		if((fp=fopen(filePosition,"r")) == NULL)
			cout<<"���ļ�ʧ�ܣ������³���"<<endl;
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
	cout<<"���������� ���� ������"<<endl<<"(����1������룬0����ɾ��)"<<endl;
	cout<<"������2��ͷ����"<<endl;
	int op;
	char cityname[10];
	while(1){
		scanf("%d",&op);
		if(op==2){
			cout<<"�������"<<endl;
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
						cout<<"���в����ڣ������³���"<<endl;
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
				cout<<"�������"<<endl;
				cout<<"==================================="<<endl;
				return;
			default:
				cout<<"������������������"<<endl;
				break;
		}
	}
}

//��Ҫ���� ���� ������
void editCityFromFile(struct graph* gt,struct graph* ga){
	cout<<"==================================="<<endl;
	cout<<"�������ļ�λ�ã�"<<endl;
	char filePosition[MAXL];
	char tempstr[MAXL];
	FILE* fp;
	while(1){
		scanf("%s",filePosition);
		if((fp=fopen(filePosition,"r")) == NULL)
			cout<<"���ļ�ʧ�ܣ������³���"<<endl;
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
						cout<<"���в����ڣ������³���"<<endl;
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
				cout<<"�������"<<endl;
				cout<<"==================================="<<endl;
				fclose(fp);
				return;
			default:
				cout<<"������������������"<<endl;
				break;
		}
	}
	fclose(fp);
	return;
}

void editEdgeFromUser(struct graph* g){
	cout<<"==================================="<<endl;
	cout<<"����������: ���� ��� �յ� ���� Ʊ�� ����ʱ�� ����ʱ��"<<endl<<"(����1������룬0����ɾ��)"<<endl;
	cout<<"������2��ͷ����"<<endl;
	int op,startcity,endcity,price,starttime,endtime;
	char cityname[10];
	char number[MAXL];
	while(1){
		scanf("%d",&op);
		if(op==2){
			cout<<"�������"<<endl;
			return;
		}
		int i=0;
		scanf("%s",cityname);
		for(i=0;i<g->vexnum;i++){
			if(!strcmp(cityname,g->adjlist[i].cityname))
				break;
			else if(i==g->vexnum-1){
				cout<<"���в����ڣ������³���"<<endl;
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
				cout<<"���в����ڣ������³���"<<endl;
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
				cout<<"�������"<<endl;
				cout<<"==================================="<<endl;
				return;
			default:
				cout<<"������������������"<<endl;
				break;
		}
	}
}

void editEdgeFromFile(struct graph* g){
	cout<<"==================================="<<endl;
	cout<<"�������ļ�λ�ã�"<<endl;
	char filePosition[MAXL];
	char tempstr[MAXL];
	FILE* fp;
	while(1){
		scanf("%s",filePosition);
		if((fp=fopen(filePosition,"r")) == NULL)
			cout<<"���ļ�ʧ�ܣ������³���"<<endl;
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
				cout<<"���в����ڣ������³���"<<endl;
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
				cout<<"���в����ڣ������³���"<<endl;
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
				cout<<"�������"<<endl;
				cout<<"==================================="<<endl;
				fclose(fp);
				return;
			default:
				cout<<"������������������"<<endl;
				break;
		}
	}
	fclose(fp);
	return;
}

