/*
249ms	21300KB
$Description$
给定一个$n$的排列$p_i$，求一个排列$q_i$，使得对于任意$1\leq i\leq n$，$q_{q_i}=p_i$。无解输出$-1$。
$1\leq n\leq10^6$。
$Solution$
对排列$q_i$我们建一张图，边为$i\to q_i$。显然这张图是由几个环构成。
发现对于$q_{q_i}$的图，原来$q_i$中的奇环它们还是类似的一个奇环，原来的偶环会分裂成两个大小相等的偶环。
所以对$p_i$建图，找出里面的环，是奇环就把相邻点间隔为$2$地插入到环里，是偶环就找到和它一样大的一个合并，找不到就无解。这样就可以得到$q_i$的图了。（每个偶环只能合并一次→_→）
复杂度$O(n)$。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 1000000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e6+5;

int nxt[N],q[N],tmp[N],tmp2[N],id[N];
bool vis[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

int main()
{
	const int n=read();
	for(int i=1; i<=n; ++i) nxt[i]=read();
	for(int s=1; s<=n; ++s)
		if(!vis[s])
		{
			int cnt=0,x=s;
			do
			{
				tmp[++cnt]=x, vis[x]=1, x=nxt[x];
			}while(x!=s);
			if(cnt&1)
			{
				for(int i=1,now=0; i<=cnt; ++i,(now+=2)>=cnt&&(now-=cnt)) tmp2[now]=tmp[i];
				for(int i=0; i<cnt; ++i) q[tmp2[i]]=tmp2[i+1];
				q[tmp2[cnt-1]]=tmp2[0];
			}
			else
			{
				if(!id[cnt]) id[cnt]=s;
				else
				{
					int y=id[cnt],x=y,t=0;
					do
					{
						tmp2[++t]=x, x=nxt[x];
					}while(x!=y);
					for(int t1=1,t2=1,las=tmp[1],i=t<<1; i; --i)
						las=q[las]=i&1?tmp[++t1]:tmp2[t2++];
					q[tmp2[t]]=tmp[1], id[t]=0;
				}
			}
		}
	for(int i=2; i<=n; i+=2) if(id[i]) return puts("-1"),0;
	for(int i=1; i<=n; ++i) printf("%d ",q[i]);

	return 0;
}
