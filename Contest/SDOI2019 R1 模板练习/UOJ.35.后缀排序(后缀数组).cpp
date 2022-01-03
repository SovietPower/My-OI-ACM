//297ms	15228kb
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e6+5;

struct Suffix_Array
{
	int rk[N],sa[N],sa2[N],tm[N],ht[N];
	char s[N];
	void Build(char *s,int n,int m)
	{
		int *x=rk,*y=sa2;
		for(int i=0; i<=m; ++i) tm[i]=0;
		for(int i=1; i<=n; ++i) ++tm[x[i]=s[i]-'a'+1];
		for(int i=1; i<=m; ++i) tm[i]+=tm[i-1];
		for(int i=n; i; --i) sa[tm[x[i]]--]=i;
		for(int k=1,p=0; k<n; k<<=1,m=p,p=0)
		{
			for(int i=n-k+1; i<=n; ++i) y[++p]=i;
			for(int i=1; i<=n; ++i) if(sa[i]>k) y[++p]=sa[i]-k;

			for(int i=1; i<=m; ++i) tm[i]=0;
			for(int i=1; i<=n; ++i) ++tm[x[i]];
			for(int i=1; i<=m; ++i) tm[i]+=tm[i-1];
			for(int i=n; i; --i) sa[tm[x[y[i]]]--]=y[i];

			std::swap(x,y), x[sa[1]]=p=1;
			for(int i=2; i<=n; ++i)
				x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])?p:++p;
			if(p>=n) break;
		}
		for(int i=1; i<=n; ++i) rk[sa[i]]=i;
		ht[1]=0;
		for(int i=1,k=0; i<=n; ++i)
		{
			if(rk[i]==1) continue;
			if(k) --k;
			int p=sa[rk[i]-1];
			while(i+k<=n && p+k<=n && s[i+k]==s[p+k]) ++k;
			ht[rk[i]]=k;
		}
	}
	void Solve()
	{
		scanf("%s",s+1); int n=strlen(s+1);
		Build(s,n,27);
		for(int i=1; i<=n; ++i) printf("%d ",sa[i]); puts("");
		for(int i=2; i<=n; ++i) printf("%d ",ht[i]); puts("");
	}
}sa;

int main()
{
	sa.Solve();
	return 0;
}
