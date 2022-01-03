#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=105;

int n,have[4][3],sum[4][3],ref[2333];//x:0~3 S/L

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read(); char s[233];
	ref['S']=0, ref['L']=1, ref['M']=2;
	for(int l,i=1; i<=n; ++i)
	{
		scanf("%s",s+1), l=strlen(s+1);
		++have[l-1][ref[s[l]]];
	}
	for(int l,i=1; i<=n; ++i)
	{
		scanf("%s",s+1), l=strlen(s+1);
		++sum[l-1][ref[s[l]]];
	}
	int res=0;
	for(int i=0; i<=3; ++i)
	{
		int tmp=0;
		for(int j=0; j<=2; ++j) tmp+=std::abs(have[i][j]-sum[i][j]);
		res+=tmp>>1;
	}
	printf("%d",res);

	return 0;
}
