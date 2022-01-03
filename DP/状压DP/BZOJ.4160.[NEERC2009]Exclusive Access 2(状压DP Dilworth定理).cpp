/*
1112kb	728ms
$Description$
给定$n$个点$m$条边的无向图，边权为1，定向得到有向无环图，使得最长路最短。
$n\leq 15,\ m\leq 100$
$Solution$
DAG中，根据$Dilworth$定理，有 $最长反链=最小链覆盖$，也有 $最长链=最小反链划分数-1$（这个是最短的最长链？），即把所有点划分成最少的集合，使得集合内的点两两之间没有边。
直接状压。设$f[s]$表示$s$集合内的点是否满足两两之间没有边，$g[s]$表示最少可以将$s$划分为几个集合使得集合内两两没有边。
那么如果$f[s']=1\ (s'\in s)$，$g[s]=\min(g[s],\ g[s\ \text{xor}\ s']+1)$。
复杂度$O(m2^n+3^n)$。
~~这么做不需要考虑给边定向啊= =
另一个这样应用$Dilworth$定理的好像是导弹拦截问题？~~
所以这题猜个结论之后，不和BZOJ4145一样吗=v=
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define lb(x) (x&-x)
const int N=15,M=(1<<N)+1;

int g[M],id[233],ref[M];
bool mp[N][N],f[M];

int main()
{
	char s1[3],s2[3];
	memset(id,0xff,sizeof id);
	int n=0,m; scanf("%d",&m);
	for(int p1,p2; m--; )
	{
		scanf("%s%s",s1,s2);
		if(id[p1=s1[0]]==-1) id[p1]=n++;
		if(id[p2=s2[0]]==-1) id[p2]=n++;
		mp[id[p1]][id[p2]]=1, mp[id[p2]][id[p1]]=1;
	}
	int lim=(1<<n)-1;
	for(int i=0; i<n; ++i) ref[1<<i]=i;
	for(int s=0; s<=lim; ++s)
	{
		f[s]=1;
		for(int s1=s; s1&&f[s]; s1^=lb(s1))
			for(int s2=s,i=ref[lb(s1)]; s2; s2^=lb(s2))
				if(mp[i][ref[lb(s2)]]) {f[s]=0; break;}
	}
	g[0]=0;
	for(int s=1; s<=lim; ++s)
	{
		int tmp=1<<30;
		for(int ss=s; ss; ss=(ss-1)&s)
			if(f[ss]) tmp=std::min(tmp,g[s^ss]+1);
		g[s]=tmp;
	}
	printf("%d\n",g[lim]-2);

	return 0;
}
