/*
6096K	704MS
$Description$
求两个字符串长度不小于k的公共子串对数。
$Solution$
求出ht[]后先减去k，这样对于两个后缀A',B'，它们之间的贡献为min{ht(A)}(A'到B'ht[]的最小值)。
维护一个栈，栈中ht从底到顶递减。
如果当前是求B中后缀i和前边A中子串的答案，那么记录之前的∑(ht(A))，这就是前边A对i的贡献。
然后更新这个栈，若ht[i]>ht[top]，入栈即可 但不对B计算答案；
若ht[i]<=ht[top]，因为公共子串是min{ht()}，i入栈后要对所有ht[top-1]>=ht[i]的top-1改成ht[i]，并且i出栈(期间减去当前多算的答案ht[top]-ht[top-1])，直到ht[top-1]<ht[top] 
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int N=2e5+10;

int n,sa[N],ht[N],rk[N],sa2[N],tm[N],sk[N],val[N],bel[N];
char s[N];

void Get_SA()
{
	int *x=rk,*y=sa2,m=260;
	for(int i=0; i<=m; ++i) tm[i]=0;
	for(int i=1; i<=n; ++i) ++tm[x[i]=s[i]+1];
	for(int i=1; i<=m; ++i) tm[i]+=tm[i-1];
	for(int i=n; i; --i)  sa[tm[x[i]]--]=i;
	for(int p=0,k=1; k<n; k<<=1,m=p,p=0)
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
	int k;
	while(scanf("%d",&k),k)
	{
		scanf("%s",s+1); int l=strlen(s+1);
		s[l+1]=1, scanf("%s",s+2+l), n=strlen(s+1);
		Get_SA();
		for(int i=2/*1*/; i<=n; ++i)
		{
			ht[i]-=k-1, bel[i]=sa[i]>l;
			if(ht[i]<0) ht[i]=0;
		}
		LL res=0,tmp;
		val[0]=-1, ht[n+1]=0;
		for(int top,t=0; t<=1; ++t)
		{
			tmp=0, top=0;
			for(int i=2/*1*/; i<=n; ++i)//ht[1]就是补充字符 计算不计算都行 
			{//必须要算上第n个字符  
				if(bel[i]!=t) res+=tmp;
				sk[++top]=bel[i]==t;
				val[top]=ht[i+1];//在这加上i+1与i产生的贡献 
				tmp+=(LL)sk[top]*val[top];
				while(val[top-1]>=val[top])
				{
					--top;
					tmp-=(LL)(val[top]-val[top+1])*sk[top];//减去之前多余的贡献 
					val[top]=val[top+1], sk[top]+=sk[top+1];
				}
			}
		}
		printf("%lld\n",res);
	}
	return 0;
}
