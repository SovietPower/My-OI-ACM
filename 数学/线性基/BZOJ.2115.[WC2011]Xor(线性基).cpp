/*
6016kb	500ms
$Description$
����һ���������Ȩͼ(�����Ի����ر�)����һ��1->n��·����ʹ��·�������ߵ�Ȩֵ��Xor����󡣿��ظ�������/�ߣ��ұ�Ȩ�ͼ����Ρ�
$Solution$
����һЩ���ʡ���һ�����������������һ�����ԭ·���أ���ô�õ��ĺ���Ϊ0�������������һ������ԭ·���أ����õ��������Xor�͡�
��ô��1��Ϳ��Եõ��κ�һ������Xor�͡����ǻ���Ҫһ��1->n��·����ʹ�ô�����ĳЩ���������������ǾͿ��ԶԻ���Ȩֵ�������Ի�����·��Xor�������������ֵ��
ѡȡ����·���أ�������ڶ���1->n��·����ʵ������������Ҳ������һ����������Ҳ��ͳ�������ˡ�
�����ǿ�������ѡȡһ��1->n��·��(��������Ȼûɶ��)������������ţ�������ĳ����Xor�󻻳�һ�����ŵ�·����(ͬ������·���ϵ��ѡ��Ҳ������ġ����л���Ҫ����)
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 100000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=5e4+5,M=2e5+5;

int n,Enum,H[N],nxt[M],to[M];
LL base[69],len[M],val[N];
bool vis[N];
char IN[MAXIN],*SS=IN,*TT=IN;

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
inline void AddEdge(LL w,int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, len[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, len[Enum]=w;
}
inline void Insert(LL x)
{
	for(int i=60; ~i; --i)
		if(x&(1ll<<i))
		{
			if(base[i]) x^=base[i];
			else {base[i]=x; break;}
		}
}
inline LL Query(LL x)
{
	for(int i=60; ~i; --i)
		x=std::max(x,x^base[i]);
	return x;
}
void DFS(int x,int f)
{
	vis[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]]) val[v]=val[x]^len[i], DFS(v,x);
		else if(v!=f) Insert(val[v]^val[x]^len[i]);
}

int main()
{
	n=read();
	for(int i=1,m=read(); i<=m; ++i) AddEdge(readll(),read(),read());
	DFS(1,1);
	printf("%lld\n",Query(val[n]));

	return 0;
}
