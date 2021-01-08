#include "sort.h"

Status
ReadFile(char *fname){
	FILE *fp = NULL;
	char line[1000];
	int ptr = 0,i = 0;
	if((fp = fopen(fname,"r")) != NULL){
		char delims[] = "\t";
		char *result = NULL;
		fgets(line,MAX_LINE,fp);
		while(result = strtok((key.num == 0) ? line : NULL,delims)){
			if(result == NULL){
				key.num--;
				break;
			}
			if(result[0] == '\n')
				break;
			key.word[key.num] = (char *)malloc(strlen(result)*sizeof(char));
			strcpy(key.word[key.num],result);
			key.num++;
		};
		file.keynum = key.num;
		while(fgets(line,MAX_LINE,fp)){
			result = NULL;
			ptr=0;
			while(1){
				result = strtok((ptr == 0) ? line : NULL,delims);
				if(result == NULL){
					break;
				}
				file.data[ptr][file.line] = atoi(result);
				if(file.data[ptr][file.line]>max)
					max = file.data[ptr][file.line];
				ptr++;
			};
			file.line++;
		}
		printf("\e[1;32mINFO\e[0m: File found. Loading file \"%s\".\n",fname);
		system("clear");
		printf("\n\n\t\t\t\e[32m\e[1mMultiple Keywords Sorting\e[0m\n");
		printf("\n\t\t\tAuthor: LandonWong, ucas\n\n");
		printf("\e[1;32mINFO\e[0m: Successfully load file \"%s\".\n",fname);
		printf("\e[1;32mINFO\e[0m: File \"%s\" has %d keywords, %d lines.\n",fname,file.keynum,file.line);
		printf("\e[1mKeywords List\e[0m: \n");
		for(i=1;i<key.num;i++){
			printf("%-10s",key.word[i-1]);
			if(i%5 == 0)
				printf("\n");
		}
		printf("%-10s\n",key.word[i-1]);
		fclose(fp);
		return OK;
	}else
		return ERROR;
}

Status
WriteFile(char *fname){
	FILE *fp = NULL;
	int ptr = 0,i = 0;
	if((fp = fopen(fname,"w+")) != NULL){
		for(i=0;i<key.num;++i)
			fprintf(fp,"%s\t",key.word[i]);
		fprintf(fp,"\n");
		for(i=0;i<file.line-1;++i){
			if(file.data[0][i] == 0)
				continue;
			for(ptr=0;ptr<key.num;++ptr)
				fprintf(fp,"%d\t",file.data[ptr][i]);
			fprintf(fp,"\n");
		}
		printf("\e[1;32mINFO\e[0m: Successfully write to file \"%s\".\n",fname);
		fclose(fp);
		return OK;
	}else
		return ERROR;
}

Status
UserAsk(){
	Status getinfo = 0;
	int info,i=0,ptr=0,pos=0;
	char keyinfo[MAXLEN_ITEM],dir[MAXLEN_ITEM];
	printf("Please choose \e[1mSORT WAY\e[0m: Merge(1) or Merge_LSD(2) or Bucket_LSD(3)\n(sort) ");
	scanf("%d",&info);
	getinfo = (info == 1 || info == 2 || info == 3);
	while(!getinfo){
		printf("\e[1;31mError\e[0m: Please input 1 or 2.\n\nPlease choose \e[1mSORT WAY\e[0m: Merge(1) or Buttom(2) or Bucket_LSD(3)\n(sort) ");
		scanf("%d",&info);
		getinfo = (info == 1 || info == 2 || info == 3);
	}
	printf("Please input \e[1mKEYWORD ORDER\e[0m in one line:\n(sort) ");
	while(1){
		pos=-1;
		scanf("%s",keyinfo);
		for(i=0;i<key.num;++i){
			if(strcmp(key.word[i],keyinfo) == 0){
				pos = i;
				break;
			}
		}
		if(pos == -1){
			printf("\e[1;31mError\e[0m: No keyword \"%s\". Please input again:\n(sort) ",keyinfo);
			ptr = 0;
		}else{
			file.order[ptr++] = pos;
			scanf("%s",dir);
			if(dir[0] == 'u')
				direction[ptr-1] = 1;
			else direction[ptr-1] = -1;
		}
		if(ptr == key.num){
			printf("\e[1;32mINFO\e[0m: Successfully get order: \n");
			for(i=1;i<key.num;i++){
				printf("%10s %-4s",key.word[file.order[i-1]],(direction[i-1] == 1) ? "up" : "down");
				if(i%5 == 0)
					printf("\n");
			}
			printf("%10s %-4s",key.word[file.order[i-1]],(direction[i-1] == 1) ? "up\n" : "down\n");
			break;
		}
	}
	return info;
}

int
main(){
	char file_name[MAXLEN_ITEM],output_name[MAXLEN_ITEM];
	int info;
	struct timeval begin,end;
	system("clear");
	printf("\n\n\t\t\t\e[32m\e[1mMultiple Keywords Sorting\e[0m\n");
	printf("\n\t\t\tAuthor: LandonWong, ucas\n\n");
	#ifdef _WIN32
	printf("[WARNING]: To ensure the user experience, please run in linux system. \n");
	printf("[WARNING]: In Windows system, program interaction may be abnormal. \n");
	printf("[INFO]: Program exit. Please use linux system. \n");
	exit(0);
	#endif
	printf("Please input \e[1mFILE NAME\e[0m:\n(sort) ");
	scanf("%s",file_name);
	while(!ReadFile(file_name)){
		printf("\e[1;31mError\e[0m: File must be in the same directory as programs.\n\nPlease input \e[1mFILE NAME\e[0m:\n(sort) ");
		scanf("%s",file_name);
		if(file_name[0] == 'q')
			return EXIT;
	}
	info = UserAsk();
	gettimeofday(&begin,NULL);	
	if(LSDSort(info)){
		gettimeofday(&end,NULL);
		printf("\e[1;32mINFO\e[0m: Sort finished successfully. ");
		printf("Finished in \e[1;32m%.2lfms\e[0m\n",(double)((end.tv_sec*1000 + end.tv_usec/1000) - (begin.tv_sec*1000 + begin.tv_usec/1000)));
	}else{
		printf("\e[1;31mError\e[0m: Sort failed.\n ");
	}
	printf("Please input \e[1mOUTPUT FILE NAME\e[0m:\n(sort) ");
	scanf("%s",output_name);
	WriteFile(output_name);
	return OK;
}

Status
LSDBucket(){
	int k = key.num;
	int i;
	while(k>0){
		k--;
		for (i = max; i >= 0; --i)
			cnt[i] = 0;
		for (i = file.line; i > 0; )
			++cnt[file.data[file.order[k]][--i]];
		if(direction[k] != 1){
			for (i = max; i >= 0; --i)
				cnt[i - 1] += cnt[i];
		}else{
			for (i = 0; i <= max; ++i)
				cnt[i + 1] += cnt[i];	
		}
		for (i = file.line; i > 0; ){
			--i;
			--cnt[file.data[file.order[k]][i]];
			for(int ptr=0;ptr<key.num;++ptr){
				dat[ptr][cnt[file.data[file.order[k]][i]]] = file.data[ptr][i];
			}
			//data[--cnt[a[i].key[k]]] = a[i];
		}
		for (i = file.line; i > 0; ){
			--i;
			for(int ptr=0;ptr<key.num;++ptr){
				file.data[ptr][i] = dat[ptr][i];
			}
			//a[i] = data[i];
		}
	}
	return OK;
}


Status
LSDmerge(int left, int mid, int right,int keynum){
	int n1 = mid - left + 1;
	int n2 = right - mid;
	int l[MAXLEN_ITEM][n1], r[MAXLEN_ITEM][n2];
	int i, j, k;
	for(i = 0;i < n1;i++){
		for(int ptr=0;ptr<key.num;++ptr){
			l[ptr][i] = file.data[ptr][left+i];
		}
	}
	for(j = 0;j < n2;j++){
		for(int ptr=0;ptr<key.num;++ptr){
			r[ptr][j] = file.data[ptr][mid+1+j];
		}
	}	
	i = j = 0;
	for(k = left;i < n1 && j < n2;++k) {
		if(direction[keynum] != 1 ? (l[keynum][i] >= r[keynum][j]) : (l[keynum][i] <= r[keynum][j])) { //l[i] > r[j]
			for(int ptr=0;ptr<key.num;++ptr){
				file.data[ptr][k] = l[ptr][i];
			}
			++i;
		}else{
			for(int ptr=0;ptr<key.num;++ptr){
				file.data[ptr][k] = r[ptr][j];
			}
			++j;
		}
	}
	if (i < n1)
		for (;i < n1;i++) {
			for(int ptr=0;ptr<key.num;++ptr){
				file.data[ptr][k] = l[ptr][i];
			}
			//a[k] = l[i];
			++k;
		}
	if (j < n2)
		for (; j < n2; ++j) {
			for(int ptr=0;ptr<key.num;++ptr){
				file.data[ptr][k] = r[ptr][j];
			}
			//a[k] = r[j];
			++k;
		}
	return OK;
}

Status
LSDMergeSort(int left, int right,int keynum){
        int mid;
        if (left < right) {
                mid = (left + right) / 2;
                if(!LSDMergeSort(left,mid,keynum))
                	return ERROR;
                if(!LSDMergeSort(mid+1,right,keynum))
                	return ERROR;
                if(!LSDmerge(left,mid,right,keynum))
                	return ERROR;
        }
        return OK;
}

Status
LSDMerge(){
	for(int i=key.num-1;i>=0;i--){
		if(!LSDMergeSort(0,file.line-1,file.order[i]))
			return ERROR;
	}
	return OK;
}

Status
merge(int left, int mid, int right){
	int n1 = mid - left + 1;
	int n2 = right - mid;
	int l[MAXLEN_ITEM][n1], r[MAXLEN_ITEM][n2];
	int i, j, k;
	for(i = 0;i < n1;i++){
		for(int ptr=0;ptr<key.num;++ptr){
			l[ptr][i] = file.data[ptr][left+i];
		}
	}
	//	l[i] = a[left+i];
	for(j = 0;j < n2;j++){
		for(int ptr=0;ptr<key.num;++ptr){
			r[ptr][j] = file.data[ptr][mid+1+j];
		}
	}
	//	r[j] = a[mid+1+j];
		
	i = j = 0;
	for(k = left;i < n1 && j < n2;++k) {
		int cmp=0;
		for(int ptr=0;ptr<key.num;ptr++){
			if(direction[ptr] != 1 ? l[file.order[ptr]][i] < r[file.order[ptr]][j] : l[file.order[ptr]][i] > r[file.order[ptr]][j])
				{cmp=1;break;}
			if(direction[ptr] != 1 ? l[file.order[ptr]][i] > r[file.order[ptr]][j] : l[file.order[ptr]][i] < r[file.order[ptr]][j])
				{cmp=-1;break;}
		}
		//printf("[%d]",cmp);
		if(cmp<0) { //l[i] < r[j]
			for(int ptr=0;ptr<key.num;++ptr){
				file.data[ptr][k] = l[ptr][i];
			}
			//a[k] = l[i];
			++i;
		}else{
			for(int ptr=0;ptr<key.num;++ptr){
				file.data[ptr][k] = r[ptr][j];
			}
			//a[k] = r[j];
			++j;
		}
	}
	if (i < n1)
		for (;i < n1;i++) {
			for(int ptr=0;ptr<key.num;++ptr){
				file.data[ptr][k] = l[ptr][i];
			}
			//a[k] = l[i];
			++k;
		}
	if (j < n2)
		for (; j < n2; ++j) {
			for(int ptr=0;ptr<key.num;++ptr){
				file.data[ptr][k] = r[ptr][j];
			}
			//a[k] = r[j];
			++k;
		}
	return OK;
}

Status
MergeSort(int left, int right){
        int mid;
        if (left < right) {
                mid = (left + right) / 2;
                if(!MergeSort(left,mid))
                	return ERROR;
                if(!MergeSort(mid+1,right))
                	return ERROR;
                if(!merge(left,mid,right))
                	return ERROR;
        }
        return OK;
}

Status
LSDSort(int info){
	if(info == 1)
		if(!MergeSort(0,file.line-1))
			return ERROR;
	if(info == 2)
		if(!LSDMerge())
			return ERROR;
	if(info == 3)
		if(!LSDBucket())
			return ERROR;
	return OK;
};

