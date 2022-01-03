/*
28360kb	7720ms
$Description$
给定一棵$n$个点的树，每个点有一个属性$1\leq r_i\leq R$。$Q$次询问，每次询问给定$r1,r2$，求有多少点对$(x,y)$满足，$r_x=r1,\ r_y=r2$，且$x$是$y$的祖先。
$n,q\leq2\times10^5,\ R\leq25000$。

$Solution$
对属性为$r2$的有多少个点分类讨论。
若$\leq\sqrt n$，在每个点处暴力统计它祖先的贡献；
若$\gt\sqrt n$，则这样的属性不超过$\sqrt n$种，在属性为$r1$的点上暴力枚举这些$r2$更新答案（这里可以差分：进入子树前与访问完子树后）。
显然对于第二种情况，在每个点上，要对询问的$r2$去重才能保证复杂度（然而数据没卡不去重好像也能过...）。
关于如何去重，自己想的是，对$r2$相同的一些询问，要同时更新它们。大概以$r2$为关键字`sort`下，就可以差分了？
事实上对询问点对$(r1,r2)$判一下重就可以了...如果出现够询问$(r1,r2)$，就直接用之前的作答案。
复杂度$O(n\sqrt n+q\sqrt n)$。

有[树分块做法]，然而懒得看。
*/
#include <map>
#include <cmath>
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e5+5,M=25005;

int Enum,H[N],nxt[N],A[N],Ans[N];
std::vector<pr> v1[M],v2[M];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int u,int v)
{
	nxt[v]=H[u], H[u]=v;
}
void DFS(int x)
{
	static int sum1[N],sum2[N];

	const std::vector<pr> &vec2=v2[A[x]];//一开始&忘了写...我说怎么MLE=-= 
	for(int i=0,l=vec2.size(); i<l; ++i)
		Ans[vec2[i].second]+=sum2[vec2[i].first];

	++sum1[A[x]], ++sum2[A[x]];
	const std::vector<pr> &vec1=v1[A[x]];
	for(int i=0,l=vec1.size(); i<l; ++i)
		Ans[vec1[i].second]-=sum1[vec1[i].first];

	for(int v=H[x]; v; v=nxt[v]) DFS(v);

	for(int i=0,l=vec1.size(); i<l; ++i)
		Ans[vec1[i].second]+=sum1[vec1[i].first];
	--sum2[A[x]];
}

int main()
{
	static int pos[N],cnt[M];

	const int n=read(),R=read(),Q=read(),size=sqrt(n);
	++cnt[A[1]=read()];
	for(int i=2; i<=n; ++i) AE(read(),i), ++cnt[A[i]=read()];

	std::map<pr,int> f;
	std::map<pr,int>::iterator it;
	for(int i=1; i<=Q; ++i)
	{
		int r1=read(),r2=read();
		if((it=f.find(mp(r1,r2)))==f.end())
		{
			f[mp(r1,r2)]=pos[i]=i;
			if(cnt[r2]<=size) v2[r2].push_back(mp(r1,i));
			else v1[r1].push_back(mp(r2,i));
		}
		else pos[i]=it->second;
	}
	DFS(1);
	for(int i=1; i<=Q; ++i) printf("%d\n",Ans[pos[i]]);//其实应该用long long的=v= 

	return 0;
}
