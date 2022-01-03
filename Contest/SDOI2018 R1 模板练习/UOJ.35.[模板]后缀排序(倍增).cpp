#include <cstdio>
#include <cstring>
#include <algorithm>
const int N=1e6+5;

int n,tm[N],sa[N],rk[N],sa2[N],ht[N];
char s[N];

void Get_SA()
{
	int *x=rk,*y=sa2,m=28;
	for(int i=0; i<=m; ++i) tm[i]=0;
	for(int i=1; i<=n; ++i) ++tm[x[i]=s[i]-'a'+1];
	for(int i=1; i<=m; ++i) tm[i]+=tm[i-1];
	for(int i=n; i; --i) sa[tm[x[i]]--]=i;
	for(int k=1,p=0; k<n; k<<=1,m=p,p=0)
	{
		for(int i=n-k+1; i<=n; ++i) y[++p]=i;
		for(int i=1; i<=n; ++i) if(sa[i]>k) y[++p]=sa[i]-k;

		for(int i=0; i<=m; ++i) tm[i]=0;
		for(int i=1; i<=n; ++i) ++tm[x[i]];
		for(int i=1; i<=m; ++i) tm[i]+=tm[i-1];
		for(int i=n; i; --i) sa[tm[x[y[i]]]--]=y[i];

		std::swap(x,y), p=x[sa[1]]=1;
		for(int i=2; i<=n; ++i)
			x[sa[i]]=y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k]?p:++p;
		if(p>=n) break;
	}
	for(int i=1; i<=n; ++i) rk[sa[i]]=i;
	ht[1]=0;
	for(int k=0,p,i=1; i<=n; ++i)
	{
		if(rk[i]==1) continue;
		if(k) --k;
		p=sa[rk[i]-1];//ht[i]>=ht[i-1]-1
		while(i+k<=n&&p+k<=n&&s[i+k]==s[p+k]) ++k;
		ht[rk[i]]=k;
	}
}

int main()
{
	scanf("%s",s+1), n=strlen(s+1), Get_SA();
	for(int i=1; i<=n; ++i) printf("%d ",sa[i]);putchar('\n');
	for(int i=2; i<=n; ++i) printf("%d ",ht[i]);

	return 0;
}
