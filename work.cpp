#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAX 30//ȡ��������ʳ���
#define SIZE 20000//ȡ���ڲ��ظ����ʸ���
typedef struct word{
	char words[MAX];
	int count;
}word;//��ŵ��ʼ���Ƶ��
int first(word *w[],char *single,int n); 
void putin(char *str,word *w[],int i,int n);
int handle(FILE *fp,word *w[]);
void Sort(word *w[],int n);
void Swap(word *w1,word *w2);
void show(word *w[],int n);

int main()
{
	int n,i;//n�����ظ����ʵ����� 
	FILE *fp;
	word *w[SIZE];
	if((fp=fopen("test.txt","r"))==NULL)
	{
		printf("û���ҵ��ļ�!\n");
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
//�жϵ����Ƿ��һ�γ���
//����i�����ظ������ڽṹ�������е�λ�ã�����-1�����һ�γ��� 
{
	int i;
	if(n==0)
		return -1;
	else
		for(i=0;i<n;i++)
			if(strcmp(w[i]->words,single)==0)//strcmp���������ж������ַ����Ƿ����
				return i;
	
	return -1;
}

void putin(char *str,word *w[],int i,int n)
//�����ʴ�Žṹ���� 
//�״γ��ֵĵ��ʴ�Ž��µ����飬�ظ����ֵ�ʹ��ӦƵ��+1 
//n�����ظ����ʵ����� 
{
	int t=0;
	
	if(i==-1)//���ظ�����
	{
		while(str[t]!='\0')
		{
			w[n]->words[t]=str[t];
			t++;
		}
		w[n]->words[t]='\0'; 
		w[n]->count=1;
	}
	else//�ظ�����
		w[i]->count++;
}

int handle(FILE *fp,word *w[])
//���ļ��е��ַ�����ɵ��ʣ���д��ȫ��ת����Сд 
{
	int i=0,n=0;
	char ch,bh=0;//bh���ڴ������к��е����ŵ���� 
	char single[MAX]={0};
	
	while((ch=fgetc(fp))!=EOF)
	{
		if(!isalpha(ch))//������һ������ĸ�ַ�������bh
			bh=0;
		if(isalpha(ch)&&bh!=0)//��bh��Ϊ����ch����ĸʱ��˵����ǰ�ַ����ڵ�����֮����������ѭ��
			continue;
		if(!isalpha(ch)&&ch!='-')//��������ĸ�ַ��Ҹ��ַ���Ϊ���ַ�ʱ��������ѭ��
			continue;
		i=0;
		while(isalpha(ch)||ch=='-')
		{
			if(ch>='A'&&ch<='Z')//����д��ĸȫ��ת����Сд��ĸ 
				ch+=32;
			single[i++]=ch;
			ch=fgetc(fp);
		}
		single[i]='\0';//�ֶ����'\0' 
		if(ch=='\'')//�������ź������ĸ���� 
			bh=ch;
		w[n]=(word*)malloc(sizeof(word));
		if(first(w,single,n)==-1)//first���������ж�single�Ƿ��һ�γ���
			n++;//n�����ظ��ĵ��ʵ����� 
		putin(single,w,first(w,single,n),n-1);//putin�������ڽ����ַ�����������ݱ����w�� 
	}
	
	return n;
} 

void Swap(word *w1,word *w2)
//���������ṹ��
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
//�����ʰ�Ƶ����������
//Ƶ����ͬ�İ��ֵ������� 
{
	int i,j,f;//f��Ϊ��־
	
	for(i=0;i<n-1;i++)
	{
		f=1;
		for(j=0;j<n-1;j++)
		{
			if(w[j]->count<w[j+1]->count)//�Ƚ�Ƶ��
			{
				Swap(w[j],w[j+1]);
				f=0;
			}
			else if(w[j]->count==w[j+1]->count)//Ƶ����ͬ���ֵ������� 
			{
				if(strcmp(w[j]->words,w[j+1]->words)>0)//�Ƚ��ַ�����С���ֵ��򣩣�����0˵��ǰ�߱Ⱥ��ߴ�
					Swap(w[j],w[j+1]);
				f=0;
			}
		}
		if(f==1)//f==1˵�����������Ѿ���ɣ�����ǰ��ֹ 
			break;
	}
}

void show(word *w[],int n)
//���
{
	int i;
	for(i=0;i<n;i++)
		fprintf(stdout,"%s  ���ִ���%d\n",w[i]->words,w[i]->count);
} 