/*
4884kb	9220ms
$Description$
给出一个n个点的有向图，任意两个点之间有且仅一条有向边。对于每个点v，求出从v出发的一条经过点数最多，且没有重复经过同一个点一次以上的简单路径。
n<=2000
$Solution$
竞赛图缩点后得到的拓扑图一定是一条链，因为竞赛图任意两点前后关系确定，所以只有一种拓扑序列 
从前边强连通分量中的任意一点出来 都可以到达后边强连通分量的任意一点 
因为竞赛图的每个强连通分量一定存在一条哈密顿回路 
所以只需要求出每一个强连通分量的哈密顿回路，然后在链上走，把每个强连通分量的回路存起来中，最后按拓扑序从后往前输出即可 
*/
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
#define gc() getchar()
const int N=2005;

int n,dfn[N],low[N],id,cnt,bel[N],sk[N],top,nxt[N],dgr[N],pos[N];
bool mp[N][N],ins[N];
std::vector<int> scc[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void Tarjan(int x)
{
	dfn[x]=low[x]=++id, sk[++top]=x, ins[x]=1;
	for(int i=1; i<=n; ++i)
		if(mp[x][i])
			if(!dfn[i]) Tarjan(i),low[x]=std::min(low[x],low[i]);
			else if(ins[i]) low[x]=std::min(low[x],dfn[i]);
			else ;//
	if(low[x]==dfn[x])
	{
		++cnt;
		do{
			bel[sk[top]]=cnt, ins[sk[top]]=0, scc[cnt].push_back(sk[top]);
		}while(x!=sk[top--]);
	}
}
inline bool cmp(const int &a,const int &b){
	return dgr[a]<dgr[b];
}
void Insert(int x)
{
	sk[++top]=x;
	for(int i=nxt[x]; i/*necessary(对于单独一个点)*/&&i!=x; i=nxt[i]) sk[++top]=i;
}

int main()
{
	n=read();
	for(int i=2; i<=n; ++i)
		for(int j=1; j<i; ++j)
			mp[j][i]=read(), mp[i][j]=mp[j][i]^1;
	for(int i=1; i<=n; ++i)
		if(!dfn[i]) Tarjan(i);
	for(int l,r,sz,i=1; i<=cnt; ++i)
	{
		l=r=scc[i][0], sz=scc[i].size();
		for(int tmp,j=1; j<sz; ++j)//从1个点开始 扩展成哈密顿路径 
		{
			tmp=scc[i][j];
			if(mp[tmp][l]) nxt[tmp]=l, l=tmp;
			else if(mp[r][tmp]) nxt[r]=tmp, r=tmp;
			else
			{
				for(int k=l; nxt[k]; k=nxt[k])
					if(mp[k][tmp]&&mp[tmp][nxt[k]])//在当前路径上找 连向tmp同时tmp连向其后边节点的 
					{
						nxt[tmp]=nxt[k], nxt[k]=tmp;
						break;
					}
			}
		}
		r=0;
		for(int j=l; j; j=nxt[j])
			if(r)
			{
				for(int k=r,las=l; ; las=k,k=nxt[k])
				{
					if(mp[j][k])
					{
						nxt[las]=nxt[l];
						if(las!=l) nxt[l]=r;
						r=k, l=j;
						break;
					}
					if(k==l) break;
				}
			}
			else if(mp[j][l]) r=l, l=j;
		nxt[l]=r;
	}
	for(int i=1; i<=n; ++i)//对每个强连通分量拓扑排序 
		for(int j=1; j<=n; ++j)
			if(bel[i]!=bel[j]&&mp[i][j]) ++dgr[bel[j]];
	for(int i=1; i<=cnt; ++i) pos[i]=i, dgr[i]/=scc[i].size();
	//度数要除以size 因为连向强连通分量i的点会连向i中所有点(竞赛图) 而此时拓扑是要对强连通分量的入度排序 
	std::sort(pos+1,pos+1+cnt,cmp);
	for(int i=1; i<=n; ++i)
	{
		top=0, Insert(i);//直接加入i这个强连通分量即可，走一遍回路，然后再从终点走到下一个强连通分量 
		//bel[i]中每个点一定都可以走到下一个强连通分量j，否则bel[i]和j就成了环(同一个强连通分量)了 
		for(int j=1; j<=cnt; ++j)//按照拓扑序添加scc(路径) 
			if(dgr[pos[j]]>dgr[bel[i]])
				Insert(scc[pos[j]][0]);
		printf("%d ",top);
		for(int i=1; i<top; ++i) printf("%d ",sk[i]);
		printf("%d\n",sk[top]);
	}
	return 0;
}
