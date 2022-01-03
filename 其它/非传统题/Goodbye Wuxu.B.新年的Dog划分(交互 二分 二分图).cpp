/*
4955ms	1584kb
**Subtask1��**
�����Ļ����¿���$2^n$ö�ٵ㼯$A,B$��������$A,B$֮��ı�ȫ��ɾ����Ȼ��ѯ�ʡ�һ��������һ��$A,B$������ͨ��
�����ͼ���ߵĵ㼯�ֱ���$S,T$���ܲµ���ʱ$S=A,T=B$������$S\cap A\neq\emptyset$��$T\cap A\neq\emptyset$����$A,B$��ͨ˵��$S,T$ͨ��ͬһ������ͨ����Ȼ���ᣬ���$T\cap A=\emptyset$��ͬ��$S\cap B\neq\emptyset$��������$S=A,T=B$��ѯ�ʴ���$O(2^n)$��
**Subtask2��**
���ͼ�Ƕ���ͼ�������ҵ�ԭͼ��һ����������Ȼ��Ϳ��Ժڰ�Ⱦɫ�ҳ�$S$�ˡ�
��������ɾ��ͼ�����бߡ����ɾ��һ����ʱ����ͨ��Ϊ����ͨ��˵�������������ϣ����������ߣ�����ɾ�������ߡ�����һ��ʣ��$n-1$���ߣ�����ԭͼ����������
ѯ�ʴ���$O(\frac{n(n-1)}{2})$��
**Subtask3��**
��������ʱһ��һ��ö�ٱ�̫���ˣ����Զ��֡����ɾ��$1\sim mid$�еı�ͼ����ͨ����ɾ���������ҵ���������߱�����
�������¼������$n-1$�Σ�ÿ����Ҫ����$\log\frac{n(n-1)}{2}\approx2\log n$�Ρ�
�ڰ�Ⱦɫ��õ�$S,T$��ֻ���������ǿ�������$S,T$�ġ����ͼ���Ƕ���ͼ����ô��$S,T$֮��ķ�����ȫɾ����һ������ĳһ�����ߣ�ʹ��ɾ���������ߺ�ͼ����ͨ��
��ѯ�ʴ���$2(n-1)\log n+n-1$��
**Subtask4��**
���ǶԵ���֣��Ѷ���ʱ$2$�ĳ���ȥ����
ö��ÿ���㣬���������ĸ���֮��ı߱��뱣�����ɡ�
ѯ�ʴ���$n\log n$��
*/
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define pb push_back
#define fir first
#define sec second
#define mp std::make_pair
#define pr std::pair<int,int>

#include "graph.h"

const int N=233;

int Enum,H[N],nxt[N<<1],to[N<<1],col[N];
bool tag[N][N];
std::vector<pr> tr;

inline void AE(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void DFS(int x)
{
	for(int i=H[x],v; i; i=nxt[i])
		if(!col[v=to[i]]) tag[x][v]=tag[v][x]=1, tr.push_back(mp(x,v)), col[v]=col[x]^1, DFS(v);
}
std::vector<int> check_bipartite(int n)
{
	std::vector<pr> q;
	for(int x=0; x+1<n; ++x)
	{
		int now=x+1;
		while(now<n)
		{
			for(int i=now; i<n; ++i) q.push_back(mp(x,i));
			if(query(q)) break;
			for(int i=now; i<n; ++i) q.pop_back();
			int l=now,r=n-1,mid;
			while(l<r)
			{
				int mid=l+r>>1;
				for(int i=l; i<=mid; ++i) q.push_back(mp(x,i));
				if(query(q)) l=mid+1;
				else r=mid;
				for(int i=l; i<=mid; ++i) q.pop_back();
			}
			AE(x,l), now=l+1;
		}
	}
	col[0]=2, DFS(0);
	std::vector<int> ans; q.clear();
	for(int i=0; i<n; ++i)//Check if it's a Bipartite Graph
		for(int j=i+1; j<n; ++j)
			if(col[i]!=col[j] && !tag[i][j]) q.push_back(mp(i,j));
	for(int i=0,l=tr.size(); i<l; ++i)
	{
		q.push_back(tr[i]);
		if(query(q)) return ans;
		q.pop_back();
	}
	for(int i=0; i<n; ++i) if(col[i]==2) ans.push_back(i);
	return ans;
}
