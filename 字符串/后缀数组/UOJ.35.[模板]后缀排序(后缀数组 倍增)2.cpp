//299ms	2560kb
#include <cstdio>
#include <cstring>
#include <algorithm>
const int N=1e5+5;

int n,sa[N],rk[N],sa2[N],tm[N],ht[N];
char s[N];

void Get_SA()
{
	int *x=rk,*y=sa2,m=200;
	for(int i=0; i<=m; ++i) tm[i]=0;
	for(int i=1; i<=n; ++i) ++tm[x[i]=s[i]-'a'+1];
	for(int i=1; i<=m; ++i) tm[i]+=tm[i-1];
	for(int i=n; i; --i) sa[tm[x[i]]--]=i;
	for(int p=0,k=1; k<n; k<<=1,m=p,p=0)
	{
		for(int i=n-k+1; i<=n; ++i) y[++p]=i;
		for(int i=1; i<=n; ++i) if(sa[i]>k) y[++p]=sa[i]-k;
		for(int i=0; i<=m; ++i) tm[i]=0;
		for(int i=1; i<=n; ++i) ++tm[x[i]];
		for(int i=1; i<=m; ++i) tm[i]+=tm[i-1];
		for(int i=n; i; --i) sa[tm[x[y[i]]]--]=y[i];

		std::swap(x,y), p=1, x[sa[1]]=1;
		for(int i=2; i<=n; ++i)
//			if(y[sa[i-1]]==y[sa[i]]&&((sa[i-1]+k<=n&&sa[i]+k<=n&&y[sa[i-1]+k]==y[sa[i]+k])||(sa[i-1]+k>n&&sa[i]+k>n))) x[sa[i]]=p;
//			if(y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+k]==y[sa[i]+k]) x[sa[i]]=p;
//			else x[sa[i]]=++p;
			x[sa[i]]=y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+k]==y[sa[i]+k]?p:++p;
		if(p>=n) break;
	}
}
void Calc_ht()
{
	for(int i=1; i<=n; ++i) rk[sa[i]]=i;
	ht[1]=0;
	for(int k=0,p,i=1; i<=n; ++i)//ht[rk[i]]>=ht[rk[i-1]]-1
	{
		if(rk[i]==1) continue;//ÅÅÃûÎª0µÄ ht[rk[i]]=ht[0]=0 
		if(k) --k;
		p=sa[rk[i]-1];
		while(i+k<=n&&p+k<=n&&s[i+k]==s[p+k]) ++k;
		ht[rk[i]]=k;
	}
}

int main()
{
	scanf("%s",s+1), n=strlen(s+1);
	Get_SA();
	for(int i=1; i<=n; ++i) printf("%d ",sa[i]);
	putchar('\n'), Calc_ht();
	for(int i=2; i<=n; ++i) printf("%d ",ht[i]);

	return 0;
}
