/*
868kb	36ms
������ݷ�Χ�������Ǳ���һЩ�Ѹ�����Ϣ��������������ֱ����$f[i][j][k][0/1]$��ʾ��ǰΪ��$i$����$i$����Ľ��˷�ľ����$i$������Ϊ$j$��$i$��$i$����һ������$k$����ľ����$0/1$��ʾ��$i$�Ƿ��˷�ľ����
���ֶ���$i$��������ĵ�$v$��$v$��û����ľ������ν����Ҫ���������˶��١�����DP��$i$��$i$ֻ����$f[i]...[0/1]$�н�С��һ����Ϊ��$i$�Ĵ𰸼��ɡ�
ת�ƾ��Ǳ���������Щ���ɡ����Ӷ�$O(n^2k^2)$��
��Ȼ����ô�����ؼ�¼�����ˣ�����ת��$f[i]$��ʱ��ֱ��DFSһ��������ǿ��$i$ѡ��������$f[i][j]$��ʾ$i$��������$j$����ľ������С���ۡ�������Ȼ���ӶȻ���$O(n^2k^2)$����ֻ��Ҫ��ά��DP���顣
����DP�굱ǰ��$i$���Ǳ���ǿ��ѡ$i$��DPֵ����ѡ$i$��Ҳû���󰡣�����������ת�Ƶ�ʱ�򣬾�����νȡ��ȡ�ˡ�
Ϊ�˷��㣬������$f$��ʾ����ף��뵽���ڵ�����ٻ����ٴ��ۣ�����
�о������е���...
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=105,INF=2e9;

int K,w[N],dep[N],sz[N],H[N],nxt[N],f[N][55],g[N][55];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int u,int v)
{
	nxt[v]=H[u], H[u]=v;
}
void DP(int x,int dep_anc)
{
	f[x][0]=dep_anc*w[x];
	for(int v=H[x]; v; v=nxt[v])
	{
		DP(v,dep_anc);
		for(int i=std::min(sz[x],K); ~i; --i)
			for(int j=0; j<=std::min(sz[v],i); ++j)
				f[x][i]=std::max(f[x][i],f[x][i-j]+f[v][j]);
	}
	for(int i=1; i<=K; ++i) f[x][i]=std::max(f[x][i],g[x][i]);//g[x][0]=0 (meaningless)
}
void DFS(int x)
{
	sz[x]=1;
	for(int v=H[x]; v; v=nxt[v]) dep[v]+=dep[x], DFS(v), sz[x]+=sz[v];
	memset(f,0,sizeof f);
	for(int v=H[x]; v; v=nxt[v])
	{
		DP(v,dep[x]);
		for(int i=std::min(sz[x],K); ~i; --i)
			for(int j=0; j<=std::min(sz[v],i); ++j)
				g[x][i]=std::max(g[x][i],g[x][i-j]+f[v][j]);
	}
	if(x) for(int i=K,v=dep[x]*w[x]; i; --i) g[x][i]=g[x][i-1]+v;//�ڴ�֮ǰδ����x����Ȼ0���������룩
//	g[x][0]=0;
}

int main()
{
	int n=read(); K=read();
	for(int i=1; i<=n; ++i) w[i]=read(),AE(read(),i),dep[i]=read();
	DFS(0);
	int ans=0,tmp=0;
	for(int i=0; i<=K; ++i) tmp=std::max(tmp,g[0][i]);
	for(int i=1; i<=n; ++i) ans+=dep[i]*w[i];
	printf("%d\n",ans-tmp);

	return 0;
}
