/*
8760kb	192ms
���⣺����������ͼ����ȨΪ1������ֱ����
����������ֱ����������(����)����DP��ÿ����������(���������Ͼ����յ���ͼ)������γ�������ÿ�����ӽڵ㲻ͬ������ max{���}+max{�γ���} ���´𰸡�(����Ҫ��γ��������������ȸ���ans��Ȼ���ٸ����������)
��f[i]Ϊ��i���յ���ͼ������ĳ��ȡ�
���ڻ���������һ������dep[]��С�ĵ�x��������� ����һ����(depΪ��DFS˳����µ�)�����f[x]��������Ĳ�������һ��ֱ�����Ϳ��ԡ�
���ڻ��Ĵ���f[x]�Ƚ���Ȼ��f[x]=max{f[v]+dis(x,v)}��vΪ�价��һ�㣬dis(x,v)Ϊx,v�ڻ��ϵ���С���롣
������θ��´𰸣��ѻ������е㶼�ó�����ans=max{f[u]+f[v]+dis(u,v)}��
u,v�ǻ��ϵĵ㣬��˳���ţ�dis(u,v)=v-u(v-u<=len/2)����ôans����д�� max{f[u]-u+f[v]+v}���̶�v����Ϊu�ǵ����ģ�����֮ǰ����f[u]-u�ں���Ҳ�����ģ������õ�������ά����
dis()�ǻ�����С���룬����v-u���ܳ��� ����/2����Ϊ�Ǹ��������԰������һ��3/2*len�����и���ans��
֮����f[v]+dis(x,v)����f[x]��
ɨһ�����еĻ����ܹ����Ӷ���$O(m)$��

�ܽ᣺Tarjan�����ڲ���ͬһ���ϵĵ㣬��f[x]+f[v]+1����ans������f[v]����f[x]�����������ĵ㣬����������ȡ�����������д���
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=5e4+5,M=N<<2;//��������������2n����

int n,m,Ans,Enum,H[N],to[M],nxt[M],dfn[N],low[N],id,fa[N],dep[N],f[N],q[N],A[N<<1];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v){
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void DP(int x,int ed)
{
	int n=dep[ed]-dep[x]+1;//length
	for(int i=n; i; --i) A[i]=f[ed], ed=fa[ed];
	int n2=n+(n>>1);//��ͬʱ���±�ĵ����ֻ��n/2���㣬����ֻ��Ҫ3/2*n 
	for(int i=n+1; i<=n2; ++i) A[i]=A[i-n];
	int h=1,t=1; q[1]=1;
	for(int i=2; i<=n2; ++i)//i,q[]�ǵ㣬�ó�����A[]��f[]��
	{
		while(h<t && i-q[h]>(n>>1)) ++h;
		Ans=std::max(Ans,A[q[h]]-q[h]+A[i]+i);
		while(h<=t && A[q[t]]-q[t]<=A[i]-i) --t;//ע������Ƚ���<����Ϊ���¶���ʱ���Ǹ���ֵ�Ĵ�С��������������(<=��Ȼ��90...) 
		q[++t]=i;
	}
	for(int i=2; i<=n; ++i)
		f[x]=std::max(f[x],A[i]+std::min(i-1,n-i+1));
}
void DFS(int x)
{
	dfn[x]=low[x]=++id;
	for(int v,i=H[x]; i; i=nxt[i])
		if((v=to[i])!=fa[x])
		{
			if(!dfn[v])
				fa[v]=x, dep[v]=dep[x]+1, DFS(v), low[x]=std::min(low[x],low[v]);
			if(low[v]>dfn[x])//���ǻ� 
				Ans=std::max(Ans,f[x]+f[v]+1), f[x]=std::max(f[x],f[v]+1);
			low[x]=std::min(low[x],dfn[v]);//����ͼ���Ͳ���Ҫʲô��ջ���� //ֻ���л������Ժ���һ��д��һ�� 
//			low[x]=std::min(low[x],low[v]);
		}
	for(int i=H[x]; i; i=nxt[i])
		if(fa[to[i]]!=x&&dfn[to[i]]>dfn[x]) DP(x,to[i]);//�һ�����һ���˵� 
		//�˵��Ǻ���ʵĵ㣬����ֻ��&&to[i]!=fa[x]��(��xͬʱ����������ʱ)���ҵ�֮ǰ�Ļ���x֮��Ļ�����x������(û��Ҫ)֮ǰ���ʵĻ��������һ����鷳����������to[i]��fa��x��
}

int main()
{
	n=read(),m=read();
	int num,u,v;
	while(m--){
		num=read()-1, u=read();
		while(num--) v=read(),AddEdge(u,v),u=v;
	}
	DFS(1);
	printf("%d",Ans);

	return 0;
}
