/*
466ms	113MB
假设我们知道一个节点表示的子串的和sum，表示的串的个数cnt，那么它会给向数字x转移的节点p贡献 sum*10+c*cnt 的和。
按拓扑序正序来就行了。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define mod (1000000007)
const int N=2e6+5;

struct Suffix_Automaton
{
	int tot,las,fa[N],son[N][10],len[N],A[N],tm[N],cnt[N],sum[N];
	char s[N>>1];

	Suffix_Automaton() {tot=las=1;}
	void Insert(int c)
	{
		int np=++tot,p=las; len[las=np]=len[p]+1;
		for(; p&&!son[p][c]; p=fa[p]) son[p][c]=np;
		if(!p) fa[np]=1;
		else
		{
			int q=son[p][c];
			if(len[q]==len[p]+1) fa[np]=q;
			else
			{
				int nq=++tot; len[nq]=len[p]+1;
				memcpy(son[nq],son[q],sizeof son[q]);
				fa[nq]=fa[q], fa[q]=fa[np]=nq;
				for(; son[p][c]==q; p=fa[p]) son[p][c]=nq;
			}
		}
	}
	void Build()
	{
		scanf("%s",s), las=1;
		for(int i=0,l=strlen(s); i<l; ++i) Insert(s[i]-'0');
	}
	void Solve()
	{
		for(int i=1; i<=tot; ++i) ++tm[len[i]];
		for(int i=1; i<=tot; ++i) tm[i]+=tm[i-1];
		for(int i=1; i<=tot; ++i) A[tm[len[i]]--]=i;
		cnt[1]=1;
		for(int i=1,x=A[1]; i<=tot; x=A[++i])
		{
			for(int v,c=0; c<10; ++c)
				if(v=son[x][c])
					cnt[v]+=cnt[x], cnt[v]>=mod&&(cnt[v]-=mod),
					sum[v]+=(1ll*sum[x]*10+1ll*cnt[x]*c)%mod, sum[v]>=mod&&(sum[v]-=mod);
		}
		long long ans=0;
		for(int i=2; i<=tot; ++i) ans+=sum[i];
		printf("%lld\n",ans%mod);
	}
}sam;

int main()
{
	int n; scanf("%d",&n);
	while(n--) sam.Build();
	sam.Solve();
	return 0;
}
