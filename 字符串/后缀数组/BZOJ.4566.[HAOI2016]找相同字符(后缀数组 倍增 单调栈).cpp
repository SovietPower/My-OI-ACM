//13712kb	4076ms
//POJ3145简化版 
#include <cstdio>
#include <cstring>
#include <algorithm>
const int N=4e5+5;

int n,rk[N],sa[N],sa2[N],tm[N],ht[N],bel[N],sk[N],val[N];
char s[N];

void Get_SA()
{
	int *x=rk,*y=sa2,m=30;
	for(int i=0; i<=m; ++i) tm[i]=0;
	for(int i=1; i<=n; ++i) ++tm[x[i]=s[i]-'a'+2];
	for(int i=1; i<=m; ++i) tm[i]+=tm[i-1];
	for(int i=n; i; --i) sa[tm[x[i]]--]=i;
	for(int p=0,k=1; k<n; m=p,p=0,k<<=1)
	{
		for(int i=n-k+1; i<=n; ++i) y[++p]=i;
		for(int i=1; i<=n; ++i) if(sa[i]>k) y[++p]=sa[i]-k;
		for(int i=0; i<=m; ++i) tm[i]=0;
		for(int i=1; i<=n; ++i) ++tm[x[i]];
		for(int i=1; i<=m; ++i) tm[i]+=tm[i-1];
		for(int i=n; i; --i) sa[tm[x[y[i]]]--]=y[i];

		std::swap(x,y), p=x[sa[1]]=1;
		for(int i=2; i<=n; ++i)
			x[sa[i]]=y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+k]==y[sa[i]+k]?p:++p;
		if(p>=n) break;
	}
	for(int i=1; i<=n; ++i) rk[sa[i]]=i;
	ht[1]=0;
	for(int k=0,p,i=1; i<=n; ++i)
	{
		if(rk[i]==1) continue;
		if(k) --k;
		p=sa[rk[i]-1];
		while(i+k<=n&&p+k<=n&&s[i+k]==s[p+k]) ++k;
		ht[rk[i]]=k;
	}
}

int main()
{
	scanf("%s",s+1); int l=strlen(s+1);
	s[l+1]='a'-1, scanf("%s",s+2+l), n=strlen(s+1);
	Get_SA();
	for(int i=2; i<=n; ++i) bel[i]=sa[i]>l;
	long long res=0,tmp;
	val[0]=-1;
	for(int top,t=0; t<=1; ++t)
	{
		tmp=0, top=0;
		for(int i=2; i<=n; ++i)
		{
			if(bel[i]!=t) res+=tmp;
			sk[++top]=bel[i]==t, val[top]=ht[i+1];
			tmp+=(long long)sk[top]*val[top];
			while(val[top-1]>=val[top])//>=比>要快啊 
			{
				--top;
				tmp-=(long long)(val[top]-val[top+1])*sk[top];
				val[top]=val[top+1], sk[top]+=sk[top+1];
			}
		}
	}
	printf("%lld",res);

	return 0;
}