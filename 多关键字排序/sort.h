#ifndef SORT_H
#define SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#define MAXLEN_ITEM	100
#define MAXLEN_BT	100000
#define MAXLINE		100000
#define MAX_LINE	100
#define	OK		1
#define	ERROR		0
#define	EXIT		0
#define OVERFLOW	-1

//typedef
typedef int Status;
typedef struct Keyword{
	char	*word[MAXLEN_ITEM];
	int	num;
}Keyword;
typedef struct FileInfo{
	int	line;
	int	keynum;
	int	data[MAXLEN_ITEM][MAXLINE];
	int	order[MAXLEN_ITEM];
}File;

Keyword key;
File file;
int direction[MAXLEN_ITEM];
int cnt[MAXLEN_BT];
int dat[MAXLEN_ITEM][MAXLINE];
int max = 0;

//functions
//file
Status
ReadFile(char *fname);
Status
WriteFile(char *fname);
//user
Status
UserAsk();
//LSD-Bucket-sort
Status
LSDBucket();
//LSD-merge-sort
Status
LSDmerge(int left, int mid, int right,int keynum);
Status
LSDMergeSort(int left, int right,int keynum);
Status
LSDMerge();
//Single-time-merge-sort
Status
merge(int left, int mid, int right);
Status
MergeSort(int left, int right);
//sort-controller
Status
LSDSort(int info);

#endif
