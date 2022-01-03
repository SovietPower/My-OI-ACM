/*
150836kb	18488ms
$Description$
��$k$�����ң�$n$�����з����ڲ�ͬ���ң�$m$���ߡ�Ҫ��ÿ��������ǡ��һ��������Ϊ�׶���ÿ����������һ���˵����׶���
���Ƿ��н⡣
$n,m,k\leq 10^6$��
$Solution$
ÿ������Ҫô���׶�Ҫô����������2-SAT 
����һ�������ڳ������������Ǻ���Ȼ�ģ����Ǳ���ΪO(n^2) 
ÿ�������н���һ�����׶��������½�ǰ׺S[i]=1/0��2n�����ʾ[1,i]�н���/û���׶� 
���ڿ�����Щ����:(A[i]=1/0��ʾi���н�/����) 
0.��A[i]=1����S[i]=1����S[i]=0����A[i]=0(����i�Լ�) 
1.��A[i]=1����S[i-1]=0����S[i-1]=1����A[i]=0 (һ������һ���׶�������)(ǰ����A[i]->A[i-1]'�Ƕ���ģ�����S_{i-1}'��Ȼ������A_{i-1}') 
2.��S[i-1]=1����S[i]=1����S[i]=0����S[i-1]=0 (ǰ׺��ϵ) 
��׺�Ż���ԭ����һ���ģ��������Ⲣ����Ҫ 
�ټ��ϱ߶˵�����ƾͿ����� 
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=4e6+5,M=N<<1;

int n,m,k,Enum,H[N],nxt[M],to[M],id,low[N],dfn[N],sk[N],top,cnt,bel[N];
bool ins[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v){
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
}
inline void Tarjan(int x)
{
	dfn[x]=low[x]=++id, ins[x]=1, sk[++top]=x;
	for(int v,i=H[x]; i; i=nxt[i])
		if(!dfn[v=to[i]]) Tarjan(v),low[x]=std::min(low[x],low[v]);
		else if(ins[v]) low[x]=std::min(low[x],dfn[v]);
	if(low[x]==dfn[x])
	{
		++cnt;
		do{
			ins[sk[top]]=0, bel[sk[top]]=cnt;
		}while(x!=sk[top--]);
	}
}

int main()
{
	n=read(),m=read(),k=read();
	for(int u,v,i=1; i<=m; ++i)
		u=read(),v=read(),AddEdge(u+n,v),AddEdge(v+n,u);
	for(int i=1; i<=n; ++i) AddEdge(i,2*n+i),AddEdge(3*n+i,i+n);
	for(int num,now,las,i=1; i<=k; ++i)
	{
		num=read(), las=read();
		for(int j=2; j<=num; ++j,las=now)
		{
			now=read(),
			AddEdge(2*n+las,2*n+now), AddEdge(3*n+now,3*n+las),
			AddEdge(now,3*n+las), AddEdge(2*n+las,now+n);
		}
	}
	for(int i=1; i<=n<<2; ++i)
		if(!dfn[i]) Tarjan(i);
	for(int i=1; i<=n; ++i)
		if(bel[i]==bel[i+n]) {printf("NIE"); return 0;}
	for(int i=n<<1|1; i<=3*n; ++i)
		if(bel[i]==bel[i+n]) {printf("NIE"); return 0;}
	printf("TAK");

	return 0;
}
//150832kb	19404ms
//{//�Ż���ŷ�ʽ ע���������Ҫ-1 -> �������������� 
//	for(int u,v,i=1; i<=m; ++i)
//		u=read()-1,v=read()-1,AddEdge(u<<1|1,v<<1),AddEdge(v<<1|1,u<<1);
//	for(int i=0; i<n; ++i) AddEdge(i<<1,i+n<<1),AddEdge(i+n<<1|1,i<<1|1);
//	for(int num,now,las,i=1; i<=k; ++i)
//	{
//		num=read(), las=read()-1;
//		for(int j=2; j<=num; las=now,++j)
//		{
//			now=read()-1,
//			AddEdge(las+n<<1,now+n<<1), AddEdge(now+n<<1|1,las+n<<1|1),
//			AddEdge(now<<1,las+n<<1|1), AddEdge(las+n<<1,now<<1|1);
//		}
//	}
//	n<<=2;
//	for(int i=0; i<n; ++i)
//		if(!dfn[i]) Tarjan(i);
//	for(int i=0; i<n; i+=2)
//		if(bel[i]==bel[i^1]) {printf("NIE"); return 0;}
//	printf("TAK");
//}
