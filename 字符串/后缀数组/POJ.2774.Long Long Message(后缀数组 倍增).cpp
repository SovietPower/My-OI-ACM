/*
3772K	516MS
$Description$
求两个字符串最长公共子串 
$Solution$
任何一个子串一定是某个后缀的前缀 
可以将两个字符串拼在一起，中间用一个从未出现过的字符隔开，这样ht[]的最大值就是答案？
不一定，最大的ht[]可能是由同一个字符串得到的，判一下属于哪个字符串即可 
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
const int N=2e5+10;

int n,l,sa[N],rk[N],ht[N],sa2[N],tm[N];
char s[N];

void Get_SA()
{
	int *x=rk,*y=sa2,m=30;
	for(int i=1; i<=n; ++i) ++tm[x[i]=s[i]-'a'+1];
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
	scanf("%s",s+1), l=strlen(s+1);
	s[l+1]='z'+1;
	scanf("%s",s+2+l), n=strlen(s+1);
	Get_SA();
	int res=0;
	for(int i=2; i<=n; ++i)
		if((sa[i]<=l)^(sa[i-1]<=l)) res=std::max(res,ht[i]);
	printf("%d",res);

	return 0;
}
