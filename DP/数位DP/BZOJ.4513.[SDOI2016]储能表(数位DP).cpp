/*
828kb	1532ms
看部分分，如果$k=0$，就是求$\sum_{i=0}^n\sum_{j=0}^mi\ \mathbb{xor}\ j$。这个数据范围考虑数位DP。（其实统计一下$\leq n$和$\leq m$中每位为$1$的数有多少个就行了...）
如果做过[字节跳动冬令营网络赛 D.The Easiest One]（没做过也行），就可以想到枚举每一位的时候，同时枚举$x,y$这一位选啥，处理一下贡献就行了。
对于$k$的限制，同样对$k$二进制分解，转移时判一下如果当前$<k$时`continue`就行了...
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
typedef long long LL;
const int N=66,INF=1e9+7;

int P,bitx[N],bity[N],bitk[N];
LL pw[N];
pr f[N][8];
bool vis[N][8];

inline LL read()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
pr DFS(int x,int s)//pair(和，方案数)
{//0:==k 1:>k
	if(x==-1) return mp(0,1);
	if(vis[x][s]) return f[x][s];
	int upx=s&1?bitx[x]:1, upy=s&2?bity[x]:1, sk=s&4;
	LL f1=0,f2=0;
	for(int i=0; i<=upx; ++i)
		for(int j=0; j<=upy; ++j)
		{
			int val=(i^j)-bitk[x];
			if(!sk && val<0) continue;
			pr v=DFS(x-1,(s&1&&i==upx)|((s&2&&j==upy)<<1)|((sk||val>0)<<2));
			if(val) f1+=val*pw[x]*v.second%P;
			f1+=v.first, f2+=v.second;
		}
	return vis[x][s]=1,f[x][s]=mp((f1%P+P)%P,f2%P);
}
void Calc(LL x,LL y,LL k)
{
	memset(vis,0,sizeof vis);
	memset(bitx,0,sizeof bitx);
	memset(bity,0,sizeof bity);
	memset(bitk,0,sizeof bitk);
	int t1=0,t2=0,t3=0;
	for(; x; x>>=1) bitx[t1++]=x&1;
	for(; y; y>>=1) bity[t2++]=y&1;
	for(; k; k>>=1) bitk[t3++]=k&1;
	printf("%d\n",DFS(std::max(t1,std::max(t2,t3))-1,3).first);
}

int main()
{
	freopen("table.in","r",stdin);
	freopen("table.out","w",stdout);

	for(int T=read(); T--; )
	{
		LL n=read()-1,m=read()-1,K=read(); int P=read(); ::P=P;
		for(int i=0; i<63; ++i) pw[i]=(1ll<<i)%P;
		Calc(n,m,K);
	}

	return 0;
}
