/*
4140kb	744ms
环可以拆成链；对字符串排序能想到后缀数组。
完了。输出时忽略长度不足n的串，输出s[sa[i]+n-1]，即排名为i的字符串的末尾。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
const int N=2e5+5;

int n,tm[N],sa[N],rk[N],sa2[N];
char s[N];

void Get_SA()
{
	int m=130,*x=rk,*y=sa2;
	for(int i=0; i<=m; ++i) tm[i]=0;
	for(int i=1; i<=n; ++i) ++tm[x[i]=s[i]];
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

		std::swap(x,y), x[sa[1]]=p=1;
		for(int i=2; i<=n; ++i)
			x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])?p:++p;
		if(p>=n) break;
	}
}

int main()
{
	scanf("%s",s+1), n=strlen(s+1);
	for(int i=1; i<=n; ++i) s[i+n]=s[i];
	n<<=1;
	Get_SA();
	for(int i=1; i<=n; ++i)
		if(sa[i]<=(n>>1)) putchar(s[sa[i]+(n>>1)-1]);

	return 0;
}
