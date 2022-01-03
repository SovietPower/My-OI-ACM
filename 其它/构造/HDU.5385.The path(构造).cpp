/*
187MS	3328K
$Description$
����һ��$n$����$m$���ߵ�����ͼ��ÿ���ߵı�Ȩ��$[1,n]$֮�䡣
��$d[i]$Ϊ$1$��$i$�����·������Ҫ��ÿ����ȷ��һ����Ȩ��ʹ�ô���һ��$i\in[2,n]$������$d[1]\lt d[2]\lt...d[i]\gt d[i+1]\gt...d[n]$��
���������ÿ���ߵı�Ȩ�������뱣֤�н⡣
$n,m\leq10^5$��
$Solution$
$d[1]=0$������$d[i]=1$�ĵ�����Щ����Ҫô��$2$��Ҫô��$n$����һ�����ڱ�$1\to i$��
$d[i]=2,3...$�ĵ�ͬ��
���Ա��$1$�ܵ������е㣬Ȼ��ά������ָ��$l=2,r=n$����$l,r$��ѡһ����ǹ��ģ�����$d[i]=++now$��Ȼ�����ܵ��ĵ㣬���м��ƶ����ָ�뼴�ɡ�
��Ϊ��֤�н⣬����ÿ��������һ��ָ����ƶ���
�����ʱ���ڱ�$(i,j)$�����$|d[i]-d[j]|$���ɡ�
�����رߣ���Ҫ���$0$�ͺ��ˡ�
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;

int Enum,H[N],nxt[N],fr[N],to[N],dis[N];
bool vis[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int v,int u)//opposite
{
	to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], H[u]=Enum;
}

int main()
{
	for(int T=read(); T--; )
	{
		int n=read(),m=read();
		Enum=0, memset(H,0,n+1<<2), memset(vis,0,n+1);
		for(int i=1; i<=m; ++i) AE(read(),read());
		for(int i=H[1]; i; i=nxt[i]) vis[to[i]]=1;
		for(int l=2,r=n,now=1; l<=r; )
		{
			int x=vis[l]?l++:r--; dis[x]=now++;
			for(int i=H[x]; i; i=nxt[i]) vis[to[i]]=1;
		}
		for(int i=1; i<=m; ++i) printf("%d\n",fr[i]==to[i]?1:std::abs(dis[fr[i]]-dis[to[i]]));
	}

	return 0;
}
