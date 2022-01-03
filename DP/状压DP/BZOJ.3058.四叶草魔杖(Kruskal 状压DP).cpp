/*
1080kb	40ms
$2^{16}=65536$，可以想到状压DP。但是又有∑Ai≠0的问题。。
但是$2^n$这么小，完全可以枚举所有子集找到∑Ai=0的，先使这整个子集内满足平衡，求一棵最小生成树就一定可以了。
这样可能会不最优，但是我们可以用更小的子集(小的话还是最优的)去更新大的。
还需要合并这些子集。将任意两个ΣAi=0的子集都是合法的，且会更新到所有情况。
$2^n*2^n$枚举ΣAi=0的子集。。这个数量到不了$2^{16}$，常数也很小。~~（反正我知道它能A）~~
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=(1<<16)+1,M=250,INF=0x3f3f3f3f;

int n,m,A[20],fa[20],f[N];
struct Edge{
	int fr,to,cost;
	bool operator <(const Edge &x)const{
		return cost<x.cost;
	}
}e[M];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
int Get_fa(int x){
	return x==fa[x]?x:fa[x]=Get_fa(fa[x]);
}
int Kruskal(int s)
{
	int cnt=0;
	for(int i=0; i<n; ++i)
		if(s>>i&1) fa[i]=i, ++cnt;
	int res=0; --cnt;
	for(int r1,r2,i=1; i<=m; ++i)
	{
		if(!(s>>e[i].fr&1)||!(s>>e[i].to&1)) continue;
		if((r1=Get_fa(e[i].fr))==(r2=Get_fa(e[i].to))) continue;
		fa[r1]=r2, res+=e[i].cost;
		if(!--cnt) break;
	}
	return cnt?INF:res;//生成树可能构不成！
}

int main()
{
	n=read(), m=read();
	for(int i=0; i<n; ++i) A[i]=read();
	for(int i=1; i<=m; ++i) e[i].fr=read(),e[i].to=read(),e[i].cost=read();
	std::sort(e+1,e+1+m);

	int lim=(1<<n)-1;
	for(int s=1; s<=lim; ++s)
	{
		int sum=0;
		for(int i=0; i<n; ++i) if(s>>i&1) sum+=A[i];
		if(sum) f[s]=INF;
		else f[s]=Kruskal(s);
	}
	for(int s1=1; s1<=lim; ++s1)
	{
		if(f[s1]==INF) continue;
		for(int s2=1; s2<=lim; ++s2)
		{
			if(f[s2]==INF||s1&s2) continue;
			f[s1|s2]=std::min(f[s1|s2],f[s1]+f[s2]);
		}
	}
	if(f[lim]==INF) puts("Impossible");//Impossible打错WA三遍→_→(倒找出俩错)
	else printf("%d\n",f[lim]);

	return 0;
}
