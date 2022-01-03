/*
62ms	13400KB
$Description$
����һ����������ÿ����Ϊ���������У����ִ���������ɫ�ĺ͡�
$Solution$
dsu on tree.��sum[i]��ʾ���ִ���Ϊi����ɫ�ĺͣ�cnt[i]��ʾ���ִ���Ϊi����ɫ�ж��ٸ�����ʵ�и�Max��ʾ��ǰ���Ĵ�������tm�ͺ��ˣ���
��дһ��dsu on tree������̣����赱ǰ��Ϊx��
��������������Ĵ𰸣���ɾ������ӵĹ��ף������ʱ�򣩣�
�����ض��������Ĵ𰸣������ض��ӵĹ��ף���ʱ����Ҫ������
����x����������Ĺ��ף�
�õ�x�Ĵ𰸣�
���x�����ض��ӣ���ɾ�������������Ĺ��ף�����ֱ�ӽ�Max,Sum��0�ͺ��ˣ���
���Ӷ�֤����ÿ��������������ÿ����ߴ�����ͳ��һ�Ρ���ÿ���㵽���ڵ��·����ֻ��$O(\log n)$����ߡ�
������DFS�����DFS����һЩ������
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;

int Enum,H[N],nxt[N<<1],to[N<<1],Max,col[N],sz[N],son[N],tm[N],A[N],L[N],R[N];
LL Sum,Ans[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void DFS1(int x,int fa)
{
	static int Index=0;
	A[L[x]=++Index]=x;
	int mx=0; sz[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa)
		{
			DFS1(v,x), sz[x]+=sz[v];
			if(sz[v]>mx) mx=sz[v], son[x]=v;
		}
	R[x]=Index;
}
inline void Add(int c)
{
	if(++tm[c]>Max) Max=tm[c], Sum=c;
	else if(tm[c]==Max) Sum+=c;
}
void Solve(int x,int fa,int keep)
{
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=fa && to[i]!=son[x]) Solve(to[i],x,0);
	if(son[x]) Solve(son[x],x,1);

	Add(col[x]);
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa && v!=son[x])
			for(int j=L[v]; j<=R[v]; ++j) Add(col[A[j]]);
	Ans[x]=Sum;
	if(!keep)
	{
		Max=Sum=0;
		for(int i=L[x]; i<=R[x]; ++i) --tm[col[A[i]]];
	}
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) col[i]=read();
	for(int i=1; i<n; ++i) AE(read(),read());
	DFS1(1,1), Solve(1,1,1);
	for(int i=1; i<=n; ++i) printf("%I64d ",Ans[i]);

	return 0;
}
