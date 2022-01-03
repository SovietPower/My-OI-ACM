/*
19768kb	5976ms
$Description$
给出两个串$S,T$，求$T$在$S$中出现了多少次。出现是指。可以有$3$次（$3$个字符）不匹配（修改使其匹配）。
$Solution$
一个套路的做法是构造多项式，对每个字符c单独考虑，$f[i]=[S[i]可匹配c],g[i]=[T[i]==c]$。
然后$F=f*g$，可以得到每个位置往后长m的串中有多少个位置S,T都匹配了c。如果某个位置匹配字符数>=m-3，则以它为左端点的串可行。
FFT/NTT实现，常数好也许能过。
SA做法：枚举S的每个位置i，设当前匹配T匹配到j，得到两个串的ht数组后我们可以$O(1)$求出LCP(suf[i],suf[j])，直接j+=LCP就行了。
如果某个位置不匹配，可以至多用3次机会直接跳过去。所以实际枚举j的次数只有5。
复杂度$O(Tn\log n)$。
SAM做法：得到parent树后，直接在上面DFS，如果能匹配则走，不能匹配则用一次次数。走了m步则加上该点的贡献(出现过多少次)。
复杂度$O(T*Cn)$($C$为字符集大小)。
还有某种神奇的Hash做法。。好像复杂度比较优。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
const int N=2e5+7;

int MAP[233],sa[N],sa2[N],rk[N],tm[N],ht[N],lg2[N],mn[18][N];
char s[N];

void Get_SA(int n)
{
	int *x=rk,*y=sa2,m=5;
	for(int i=0; i<=m; ++i) tm[i]=0;
	for(int i=1; i<=n; ++i) ++tm[x[i]=MAP[s[i]]];
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

		std::swap(x,y), x[sa[1]]=p=1;
		for(int i=2; i<=n; ++i)
			x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])?p:++p;
		if(p>=n) break;
	}
	for(int i=1; i<=n; ++i) rk[sa[i]]=i;
	ht[1]=0;
	for(int i=1,k=0,p; i<=n; ++i)
	{
		if(rk[i]==1) continue;
		if(k) --k;
		p=sa[rk[i]-1];
		while(i+k<=n && p+k<=n && s[i+k]==s[p+k]) ++k;
		ht[rk[i]]=k;
	}
}
void Init_ST(int n)
{
	for(int i=1; i<=n; ++i) mn[0][i]=ht[i];
	for(int j=1; j<=lg2[n]; ++j)
		for(int i=1; i<=n; ++i)
			mn[j][i]=std::min(mn[j-1][i],mn[j-1][i+(1<<j-1)]);
}
inline int LCP(int l,int r)
{
	l=rk[l], r=rk[r]; if(l>r) std::swap(l,r);
	++l;
	int k=lg2[r-l+1];
	return std::min(mn[k][l],mn[k][r-(1<<k)+1]);
}

int main()
{
	MAP['A']=1, MAP['T']=2, MAP['C']=3, MAP['G']=4, MAP['Z']=5;
	lg2[1]=0;
	for(int i=2; i<=200005; ++i) lg2[i]=lg2[i>>1]+1;

	int T; scanf("%d",&T);
	while(T--)
	{
		int l,n;
		scanf("%s",s+1), s[l=strlen(s+1)+1]='Z';
		scanf("%s",s+l+1), n=strlen(s+1);
		Get_SA(n), Init_ST(n);
		int ans=0;
		for(int i=1,m=n-l,lim=l-m; i<=lim; ++i)
		{
			for(int j=1,t=0; t<=3; )
			{
				if(j>m) {++ans; break;}
				else if(s[i+j-1]!=s[l+j]) ++j, ++t;
				else j+=LCP(i+j-1,l+j);
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
