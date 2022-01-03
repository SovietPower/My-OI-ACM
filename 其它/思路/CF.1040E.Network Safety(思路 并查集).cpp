/*
155ms	15800KB
$Description$
��һ��n����m���ߵ�����ͼ��ÿ�����е�Ȩ��ͼ�ǰ�ȫ�ĵ��ҽ������бߵ������˵�Ȩֵ��ͬ����֤��ʼʱͼ�ǰ�ȫ�ġ�
������ȨֵΪx�Ĳ�����������Ⱦ��ĳ����a����õ��Ȩ��Ϊa^x��
���ж�������(S,x)�����㲡����ȨֵΪx���Ҹ�Ⱦ��S�����е����е������ͼ���ǰ�ȫ�ġ�
$Solution$
��һ���������˵��ȨֵΪa,b������ȨֵΪx����Ϊa��b,a^x��b^x��������ĳ���ߣ�����ͬʱ��Ⱦ��ͬʱ����Ⱦ��������û�µġ�
�����ҽ���x=a^bʱ�����Ⱦĳһ���㣬����ֲ��Ϸ��������
���ǿ��Զ�ÿ������һ��Ȩֵa^b��������ȨֵΪĳ��ai^bi����Ϸ��ĸ�Ⱦ����n-(��Ȩֵ�ı��γɵ���ͨ����)(��ͨ�鿴��һ����ͬ�ĵ�)��������ֱ��sort�󲢲鼯��
����û���ֹ���ĳ��Ȩֵ����Ȼ����2^n�ַ�����
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define Mod(x) x>=mod&&(x-=mod)
#define mod 1000000007
typedef long long LL;
const int N=5e5+5;

LL A[N];
int pw[N],fa[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Edge
{
	int u,v; LL w;
	Edge() {}
	Edge(int u,int v):u(u),v(v) {w=A[u]^A[v];}
	bool operator <(const Edge &x)const{
		return w<x.w;
	}
}e[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline LL readll()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int Find(int x)
{
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}

int main()
{
	int n=read(),m=read(),K=read();
	pw[0]=1;
	for(int i=1; i<=n; ++i) fa[i]=i, pw[i]=pw[i-1]<<1, Mod(pw[i]);

	for(int i=1; i<=n; ++i) A[i]=readll();
	for(int i=1; i<=m; ++i) e[i]=Edge(read(),read());

	std::sort(e+1,e+1+m);
	long long ans=0;
	int tot=0; e[m+1].w=-1;
	for(int i=1,cnt=n,las=1,u,v; i<=m; ++i)
	{
		if(Find(u=e[i].u)!=Find(v=e[i].v)) fa[fa[u]]=fa[v], --cnt;
		if(e[i].w!=e[i+1].w)
		{
			ans+=pw[cnt], cnt=n, ++tot;
			for(int j=las; j<=i; ++j)
				fa[e[j].u]=e[j].u, fa[e[j].v]=e[j].v;
			las=i+1;
		}
	}
	printf("%I64d\n",(ans+((1ll<<K)-tot)%mod*pw[n])%mod);

	return 0;
}
