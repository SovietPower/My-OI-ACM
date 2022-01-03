/*
546ms	89700KB
��Ȼ����$d_{x,i}$��������$d_{x,i}=\sum_{v=son[x]}d_{v,i-1}$
*Dominant Indices*��������$d_{x,i}$���±���С��$i$�����ǿ�����������ʽ�ϲ���$d_x$������ʽ�ϲ�һ��ĸ��Ӷ���$O(n\log n)$�ģ����ڱ����У����Ӷ�ֻ��sz��С�ĵ������йأ������ǵ��������Ը��Ӷ���$O(n)$�ġ�
���ǻ���Ҫ�������������ƣ��Ա����һ��$d_{x,0}=1$��������map($O(n\log n)$)��Ҳ������vector����洢����������$O(n)$���ˡ�
Ҳ����ֱ���ø�����($O(n)$��ʵ�͹���)���飬ÿ����ά���������е�λ�á�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1e6+5;

int n,Enum,H[N],nxt[N<<1],to[N<<1],Ans[N],A[N],pos[N],len[N],mx[N],mxpos[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void Merge(int x,int y)//x<-y
{
	if(len[x]<len[y])
	{
		std::swap(pos[x],pos[y]), std::swap(len[x],len[y]), 
		std::swap(mx[x],mx[y]), std::swap(mxpos[x],mxpos[y]);
	}
	for(int i=0,ly=len[y],px=pos[x],py=pos[y]; i<ly; ++i)
	{
		A[px+i]+=A[py+i]; //A[px+i+1]+=A[py+i];
		if(A[px+i]>mx[x]) mx[x]=A[px+i], mxpos[x]=i;
		else if(A[px+i]==mx[x] && i<mxpos[x]) mxpos[x]=i;
	}
}
void DFS(int x,int f)
{
	A[pos[x]]=1, len[x]=1, mx[x]=1, mxpos[x]=0;
	for(int v,i=H[x]; i; i=nxt[i])
		if((v=to[i])!=f)
		{
			pos[v]=pos[x]+len[x]+1, DFS(v,x);//��v�ڳ�һλ���ϲ�ǰ��v����һλ������len[x]==len[v]ʱ���ص�����
			A[--pos[v]]=0, ++len[v], ++mxpos[v], Merge(x,v);
		}
	Ans[x]=mxpos[x];
}

int main()
{
	n=read();
	for(int i=1; i<n; ++i) AddEdge(read(),read());
	pos[1]=1, DFS(1,1);
	for(int i=1; i<=n; ++i) printf("%d\n",Ans[i]);

	return 0;
}
