#define MAXSIZE 505
#include<stdio.h>
#include<stdlib.h>
typedef struct//
{
	int date[MAXSIZE];
	int last;
}SeqList;

SeqList *init_SeqList()
{
	SeqList * L;
	L=(SeqList*)malloc(sizeof(SeqList));
	L->last=-1;
	return L;
}

void PrintfSeqList(SeqList * L)
{
	int i=0;
	while(i<=L->last)
	{
		printf("%6d",L->date[i]);
		i++;
	}

}

SeqList *CreatSeqList()
{
    SeqList * L;
    int i=0,t;
	L=init_SeqList();
	printf("请输入\n");
	scanf("%d",&t);
	fflush(stdin);//
	while(t!=0)
	{

		L->date[i]=t;
		L->last++;
		printf("打印此时链表：");
		PrintfSeqList(L);
		printf("\n");
		scanf("%d",&t);
		fflush(stdin);//
	
		i++;
	}
	printf("已终止\n");
	return L;
}

void merge (SeqList A,SeqList B,SeqList * C)
{
	int i,j,k;
	i=0;
	j=0;
	k=0;
	while(i<=A.last && j<=B.last)
	{
		if(A.date[i]<B.date[j])
			C->date[k++]=A.date[i++];
		else
			C->date[k++]=B.date[j++];
	}
	while(i<=A.last)
	{
		C->date[k++]=A.date[i++];
	}
	while(j<=B.last)
	{
		C->date[k++]=B.date[j++];
	}
	    C->last=k-1;
}


int main()
{
	SeqList * A;
	A=CreatSeqList();
    PrintfSeqList(A);
	SeqList * B;
	B=CreatSeqList();
	PrintfSeqList(B);
	SeqList * C=init_SeqList();
	merge(*A, *B,C);
	PrintfSeqList(C);
    return 0;
}
