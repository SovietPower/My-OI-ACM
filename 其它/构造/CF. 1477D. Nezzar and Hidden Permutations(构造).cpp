/*
857ms	54100KB
$Description$
����$m$����Ԫ��$(a,b)$������������$p,q$��ʹ��$\forall i\in[1,m]$��$(p_{a_i}-p_{b_i})(q_{a_i}-q_{b_i})>0$�����$\sum_i[p_i\neq q_i]$��
$n,m\leq 5\times 10^5$��
$Solution$
�����ƿ��ɱߡ�������Ի�Ϊ����һ������ͼ�����߶���ʹ����������������$p_i=q_i$�ĵ㾡���١����о�Ҳ�ܳ��󣬶���ûʲô�ã�
����ʲôʱ���$x$һ����$p_x=q_x$�����������е������ĵ�϶��ǡ������Ƚ�����Ϊ$n-1$�ĵ�ɾ����
Ȼ��ÿ�������ٺ�һ����û�����ߡ�����һ����$x$��һ���㼯$S$��$k=|S|\geq 1$��������$x$��$S$�����е������ߣ���$x$��$S$��С��ϵ���⣩����ôȡ$p_{x,S_1,S_2,...}=1,2,3,...,k,\ q_{x,S_1,S_2,...}=k,1,2,...,k-1$��Ȼ����ʹ$x,S$�Ϸ���
������ܽ�ͼ���ֳ����ɸ�$(x,S)$�Ľṹ����Ϊÿ��$(x,S)$�ڲ����������$(x,S)$֮��Ĵ�С��ϵ�Ͳ���ı䣬��ô���ҵ����ˡ�

�����Ǿ�ģ��������̡����������$S$�����ߵ�$x$Ϊ�ؼ��㡣
����һ����δ���ǵ�$x$����ȡ��$x$�����ߵĵ��Ϊ$y$��

* ���$y$Ҳ��û���ǹ���û�����κ�$(x,S)$������ô��$x,y$���ֵ�һ���ṹ�С�
* ���$y$��ĳ���ṹ�У����Ǹýṹ�Ĺؼ��� �� �ýṹ��СΪ$2$����ô$y$����Ϊ�ؼ��㣬��$x$����ýṹ��$S$�
* ���$y$��ĳ���ṹ�е����Ǹýṹ�Ĺؼ��㣨��$|(x,S)|>2$������ô��$y$�Ӹýṹ��ɾ������$x,y$���ֵ�һ���ṹ�С�

���Է����������ֻ�����㡰����������һ������û�����ߵĵ㡱��������ÿ���㶼����һ���ṹ��ÿ���ṹ��һ���ؼ����$|S|\geq 1$������һ���н�ʹ����$i$����$p_i\neq q_i$��
��`set`ά�������Ӷ�$O(n\log n)$������`unordered_map`����$O(n)$����������һ����$x$�����ߵĵ���Ҫ`sort`һ����$x$�����ĵ㣬Ͱ��̫�鷳����û��Ҫ$O(n)$��

**��һ���������ٷ���⣩��**
���ǲ�ͼ����ͼ��ı߼���С��ϵδ���ĵ�ԡ�
ֻ�迼�Ƕ���$\leq n-2$�ĵ㣬�����ڲ�ͼ�ж���$\geq 1$��Ҳ�����ٺ�һ����δȷ����С��ϵ��
����һ����С���ܵ����Ľṹ���ջ�ͼ��һ����$x$��һ������$S$�����е���б߹��ɵľջ���$|S|\geq 1$����������ʽͬ�ϡ�
���������ɣ���һ��ͼ����һ���߼�ʹ��ÿ����ͨ�鶼��һ���ջ�ͼ��
��ֻ���ÿ����ͨ���������һ����������DFS�Ϳ�����һ�����Բ�����ɾջ�ͼ��Ȼ����ÿ���ջ��ϵ�����С��ϵ���ɡ�
DFS��$O(n)$�ġ�����һ��д����ǿ��/kel��
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb emplace_back
typedef long long LL;
const int N=5e5+5;

int bel[N],pnt[N],P[N],Q[N];
std::set<int> st[N];
std::vector<int> e[N];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
void Solve()
{
	const int n=read(),m=read();
	for(int i=1,u,v; i<=m; ++i) u=read(),v=read(), e[u].pb(v), e[v].pb(u);
	for(int i=1; i<=n; ++i) std::sort(e[i].begin(),e[i].end());

	int tot=0,now=0;
	for(int x=1; x<=n; ++x)
		if(e[x].size()==n-1) P[x]=Q[x]=++now;
		else if(!bel[x])
		{
			int y=0; e[x].pb(N);
			for(auto v:e[x])
			{
				if(++y==x) ++y;
				if(y!=v) break;
			}
			int bely=bel[y];
			if(!bely)
				bel[x]=bel[y]=++tot, pnt[tot]=x, st[tot].insert(x), st[tot].insert(y);
			else if(pnt[bely]==y||st[bely].size()==2)
				pnt[bely]=y, bel[x]=bely, st[bely].insert(x);
			else
				st[bely].erase(y), bel[x]=bel[y]=++tot, pnt[tot]=x, st[tot].insert(x), st[tot].insert(y);
		}
	for(int i=1; i<=tot; ++i)
	{
		int p=pnt[i]; P[p]=++now;
		for(auto x:st[i])
			if(x!=p) Q[x]=now, P[x]=++now;
		Q[p]=now;
	}
	for(int i=1; i<=n; ++i) printf("%d ",P[i]); pc('\n');
	for(int i=1; i<=n; ++i) printf("%d ",Q[i]); pc('\n');

	for(int i=1; i<=n; ++i) bel[i]=0;
	for(int i=1; i<=tot; ++i) std::set<int>().swap(st[i]);
	for(int i=1; i<=n; ++i) std::vector<int>().swap(e[i]);
}

int main()
{
	for(int T=read(); T--; Solve());
	return 0;
}
