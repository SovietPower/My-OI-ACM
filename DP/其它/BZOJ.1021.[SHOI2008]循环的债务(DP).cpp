/*
28276kb	676ms
不同面额的钞票是可以分开考虑的。
↑其实并不很明白具体(证明?)，反正是可以像背包一样去做。
f[x][i][j]表示用前x种面额钞票满足 A有i元 B有j元 (C有sum-i-j)所需交换的最少数量(=(abs(ΔA)+abs(ΔB)+abs(ΔA+ΔB))/2)。
(i,j是在本来就有的钞票的基础上的，因为初始得是f[0][sa][sb]=0，这样转移后的价格是根据差值变的)
转移时枚举i,j，再枚举最终A有a张x面值钞票，B有b张x面值钞票 (据此可以算出要交换的钞票数)。
复杂度。。看起来很大但是可能因为很多非法状态，所以跑的不慢。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int val[7]={1,5,10,20,50,100},INF=0x3f3f3f3f;

int n,have[3][7],num[7],f[7][1002][1002];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	int x1=read(),x2=read(),x3=read(),sa=0,sb=0,sc=0;
	for(int j=5; ~j; --j)
		num[j]+=(have[0][j]=read()), sa+=have[0][j]*val[j];
	for(int j=5; ~j; --j)
		num[j]+=(have[1][j]=read()), sb+=have[1][j]*val[j];
	for(int j=5; ~j; --j)
		num[j]+=(have[2][j]=read()), sc+=have[2][j]*val[j];
	int sum=sa+sb+sc;
	int ea=sa-x1+x3,eb=sb+x1-x2,ec=sum-ea-eb;
	memset(f,0x3f,sizeof f);
	f[0][sa][sb]=0;
	for(int x=0; x<6; ++x)
	{
		for(int i=0; i<=sum; ++i)
			for(int k,j=0; i+j<=sum; ++j)
			{
				if(f[x][i][j]>=INF) continue;
				k=sum-i-j;
				int nowa,nowb,deltaA,deltaB;
				for(int a=0; a<=num[x]; ++a)
				{
					deltaA=a-have[0][x], nowa=i+deltaA*val[x];
					if(nowa<0) continue;//给出太多的x钞票不行 
					for(int b=0; a+b<=num[x]; ++b)
					{
						deltaB=b-have[1][x], nowb=j+deltaB*val[x];
						if(nowb<0 || sum-nowa-nowb<0) continue;
						f[x+1][nowa][nowb]=std::min(f[x+1][nowa][nowb],f[x][i][j]+((std::abs(deltaA)+std::abs(deltaB)+std::abs(deltaA+deltaB))>>1));
					}
				}
			}
	}
	if(f[6][ea][eb]<INF) printf("%d",f[6][ea][eb]);
	else puts("impossible");

	return 0;
}
