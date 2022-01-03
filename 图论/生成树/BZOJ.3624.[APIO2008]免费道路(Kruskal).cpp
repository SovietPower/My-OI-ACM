/*
2464kb	96ms
���Ƿ�����Щ�ױ��Ǳ���ӵģ���Щ�Ƕ���ġ�
��ô�����Ȱ����кڱ߼ӽ�ȥ��Ȼ��ѱ���Ҫ�ӵİױ��ҳ�����
Ȼ��Kruskal���ѱ���Ҫ�ӵİױ��ȼӽ�ȥ��С��K�Ļ��ټ��ܼӵİױߡ�Ȼ��Ӻڱߡ�
Ҫ�������һ������ûע�⣬�տ�ʼ��Ϊ�ױ߻�Ҫ���дΡ�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=2e4+5,M=1e5+5;

int fa[N];
bool chose[M];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Edge
{
	int fr,to,val;
	inline void Print(){
		printf("%d %d %d\n",fr,to,val);
	}
	bool operator <(const Edge &x)const{
		return val<x.val;
	}
}e[M];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
#define Init() for(int i=1; i<=n; ++i) fa[i]=i
int Find(int x)
{
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
bool Solve(int n,int m,int K)
{
	Init();
	std::sort(e+1,e+1+m);
	int k=1;
	for(int i=m,r1,r2; i; --i)
	{
		if((r1=Find(e[i].fr))==(r2=Find(e[i].to))) continue;
		fa[r1]=r2;
		if(!e[i].val) e[i].val=-1;//mark the white edge
		if(++k==n) break;
	}
	if(k<n) return 0;

	Init();
	std::sort(e+1,e+1+m);
	int used=0; k=1;
	for(int i=1,r1,r2; i<=m; ++i)
	{
		if((r1=Find(e[i].fr))==(r2=Find(e[i].to))) continue;
		if(used<K || e[i].val==1)
		{
			fa[r1]=r2, chose[i]=1;
			if(e[i].val<=0) e[i].val=0, ++used;
			if(++k==n) break;
		}
	}
	return used==K&&k==n;
}

int main()
{
	int n=read(),m=read(),K=read();
	for(int i=1; i<=m; ++i) e[i]=(Edge){read(),read(),read()};
	if(!Solve(n,m,K)) puts("no solution");
	else for(int i=1; i<=m; ++i) if(chose[i]) e[i].Print();

	return 0;
}
