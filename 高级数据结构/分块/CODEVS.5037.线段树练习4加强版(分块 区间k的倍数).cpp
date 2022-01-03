/*
������߶�����ÿ���ڵ�Ҫ�ٿ�k�Ŀռ䣬��Ȼ���С����Ƿֿ����(��Ȼ�ռ����ɱ�ը)

�ֿ顣��bloans[i][j]��ʾ ��i�� ģkΪj ���ж��ٸ� 
���ڲ�������ģ���ѯʱӦ�ж� A[i]+tag[belong[i]] ==k || ==0 
�������飬ά������tag��һ��������ļӱ�ǣ���һ���������mod�����tag2����ʼʱtag2Ϊ0 
������+vʱ��tag2 -=v����Ϊ��ѯ��Ӧ�� ģk=0 �����ĸ���������+v�����Ҫ��ľ��� ģk=k-v ((k-v+v)%k=0)�ĸ��� 
�����ͺ�����ؽ�����ӱ���˸�ѯ�� 
*/
#include<cmath>
#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;
const int N=2e5+5,MAXSZ=460;

int n,m,k,size,A[N],belong[N],bloans[MAXSZ][N],tag[MAXSZ],tag2[MAXSZ];

inline int read()
{
	int now=0,f=1;register char c=getchar();
	for(;!isdigit(c);c=getchar())
	  if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=getchar());
	return now*f;
}

void Update(int p,int v)
{
	--bloans[belong[p]][A[p]];
	A[p]+=v;
	if(A[p]>=k) A[p]-=k;
	++bloans[belong[p]][A[p]];
}
void Add(int l,int r,int v)
{
	int t=min(r,belong[l]*size);
	for(int i=l; i<=t; ++i)
		Update(i,v);
	if(belong[l]!=belong[r])
		for(int i=(belong[r]-1)*size+1; i<=r; ++i)
			Update(i,v);
	for(int i=belong[l]+1; i<belong[r]; ++i)
	{
		tag[i]+=v, tag2[i]-=v;
		if(tag[i]>=k) tag[i]-=k;
		if(tag2[i]<0) tag2[i]+=k;
	}
}
int Query(int l,int r)
{
	int res=0, t=min(r,belong[l]*size);
	for(int i=l; i<=t; ++i)
		if(A[i]+tag[belong[l]]==k || !(A[i]+tag[belong[l]]))
			++res;
	if(belong[l]!=belong[r])
		for(int i=(belong[r]-1)*size+1; i<=r; ++i)
			if(A[i]+tag[belong[r]]==k || !(A[i]+tag[belong[r]]))//beblong[l] belong[r]��д���� 
				++res;
	for(int i=belong[l]+1; i<belong[r]; ++i)
		res+=bloans[i][tag2[i]];
	return res;
}

int main()
{
	n=read(),m=read(),k=read();size=sqrt(n);
	for(int i=1;i<=n;++i)
	{
		A[i]=read()%k, belong[i]=(i-1)/size+1;
		if(A[i]<0) A[i]+=k;
		++bloans[belong[i]][A[i]];
	}
	char opt[9];int l,r,v;
	while(m--)
	{
		scanf("%s",opt);l=read(),r=read();
		if(opt[0]=='a')
			v=read(), Add(l,r,(v%k+k)%k);
		else
			printf("%d\n",Query(l,r));
	}

	return 0;
}
