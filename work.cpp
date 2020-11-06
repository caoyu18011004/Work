#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAX 30//取决于最长单词长度
#define SIZE 20000//取决于不重复单词个数
typedef struct word{
	char words[MAX];
	int count;
}word;//存放单词及其频数
int first(word *w[],char *single,int n); 
void putin(char *str,word *w[],int i,int n);
int handle(FILE *fp,word *w[]);
void Sort(word *w[],int n);
void Swap(word *w1,word *w2);
void show(word *w[],int n);

int main()
{
	int n,i;//n代表不重复单词的总数 
	FILE *fp;
	word *w[SIZE];
	if((fp=fopen("test.txt","r"))==NULL)
	{
		printf("没有找到文件!\n");
		getchar();
		exit(1);
	}
	n=handle(fp,w);
	Sort(w,n);
	show(w,n);
	fclose(fp);
	for(i=0;i<n;i++)
		free(w[i]);
	
	return 0;
} 

int first(word *w[],char *single,int n)
//判断单词是否第一次出现
//返回i代表重复单词在结构体数组中的位置，返回-1代表第一次出现 
{
	int i;
	if(n==0)
		return -1;
	else
		for(i=0;i<n;i++)
			if(strcmp(w[i]->words,single)==0)//strcmp函数用于判断两个字符串是否相等
				return i;
	
	return -1;
}

void putin(char *str,word *w[],int i,int n)
//将单词存放结构体中 
//首次出现的单词存放进新的数组，重复出现的使对应频数+1 
//n代表不重复单词的总数 
{
	int t=0;
	
	if(i==-1)//不重复单词
	{
		while(str[t]!='\0')
		{
			w[n]->words[t]=str[t];
			t++;
		}
		w[n]->words[t]='\0'; 
		w[n]->count=1;
	}
	else//重复单词
		w[i]->count++;
}

int handle(FILE *fp,word *w[])
//将文件中的字符处理成单词（大写将全部转换成小写 
{
	int i=0,n=0;
	char ch,bh=0;//bh用于处理单词中含有单引号的情况 
	char single[MAX]={0};
	
	while((ch=fgetc(fp))!=EOF)
	{
		if(!isalpha(ch))//遇到下一个非字母字符后，重置bh
			bh=0;
		if(isalpha(ch)&&bh!=0)//当bh不为零且ch是字母时，说明当前字符处于单引号之后，跳过本次循环
			continue;
		if(!isalpha(ch)&&ch!='-')//遇到非字母字符且该字符不为连字符时跳过本次循环
			continue;
		i=0;
		while(isalpha(ch)||ch=='-')
		{
			if(ch>='A'&&ch<='Z')//将大写字母全部转换成小写字母 
				ch+=32;
			single[i++]=ch;
			ch=fgetc(fp);
		}
		single[i]='\0';//手动添加'\0' 
		if(ch=='\'')//处理单引号后面的字母序列 
			bh=ch;
		w[n]=(word*)malloc(sizeof(word));
		if(first(w,single,n)==-1)//first函数用于判断single是否第一次出现
			n++;//n代表不重复的单词的总数 
		putin(single,w,first(w,single,n),n-1);//putin函数用于将该字符串的相关数据保存进w中 
	}
	
	return n;
} 

void Swap(word *w1,word *w2)
//交换两个结构体
{
	word w;
	strcpy(w.words,w1->words);
	w.count=w1->count;
	strcpy(w1->words,w2->words);
	w1->count=w2->count;
	strcpy(w2->words,w.words);
	w2->count=w.count;
} 

void Sort(word *w[],int n)
//将单词按频数进行排序
//频数相同的按字典序排序 
{
	int i,j,f;//f作为标志
	
	for(i=0;i<n-1;i++)
	{
		f=1;
		for(j=0;j<n-1;j++)
		{
			if(w[j]->count<w[j+1]->count)//比较频数
			{
				Swap(w[j],w[j+1]);
				f=0;
			}
			else if(w[j]->count==w[j+1]->count)//频数相同则按字典序排序 
			{
				if(strcmp(w[j]->words,w[j+1]->words)>0)//比较字符串大小（字典序），大于0说明前者比后者大
					Swap(w[j],w[j+1]);
				f=0;
			}
		}
		if(f==1)//f==1说明上述排序已经完成，可提前终止 
			break;
	}
}

void show(word *w[],int n)
//输出
{
	int i;
	for(i=0;i<n;i++)
		fprintf(stdout,"%s  出现次数%d\n",w[i]->words,w[i]->count);
} 