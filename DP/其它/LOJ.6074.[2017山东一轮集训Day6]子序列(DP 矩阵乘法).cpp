/*
263ms	8760K
https://www.cnblogs.com/SovietPower/p/10620539.html
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define rg register
#define mod 1000000007
#define Mod(x) x>=mod&&(x-=mod)
#define Add(x,v) (x+=v)>=mod&&(x-=mod)
#define Add2(x,y) (x+y>=mod?x+y-mod:x+y)
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+7,M=10;
const LL LIM=6e18;

int s[N],f[N][M],g[N][M];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
void Pre(const int n)
{
	static int A[M][M],B[M][M],tag[M];
	for(int i=0; i<M; ++i) A[i][i]=B[i][i]=f[0][i]=1;
	g[0][M-1]=1;
	for(rg int i=1; i<=n; ++i)
	{
		rg int c=s[i];
		for(rg int j=0; j<M; ++j)
		{
			rg int tmp=f[i-1][j]<<1; Mod(tmp);
			f[i][j]=Add2(tmp,mod-A[c][j]);
			A[c][j]=f[i-1][j];
			tmp=B[j][c]<<1, Mod(tmp); rg int tmp2=B[j][c];
			g[i][j]=Add2(B[j][M-1],mod-B[j][c]);
			B[j][c]=Add2(tmp,mod-tag[j]), tag[j]=tmp2;
		}
	}
}

int main()
{
	int n=0;
	register char c; while(isalpha(c=gc())) s[++n]=c-'a';
	Pre(n);
	for(int q=read(); q--; )
	{
		int l=read()-1,r=read();
		LL ans=0;
		if(l) for(int i=0; i<M; ++i) ans+=1ll*f[r][i]*g[l][i], ans>=LIM&&(ans%=mod);
		else ans=f[r][M-1];
		printf("%lld\n",(ans-1)%mod);
	}

	return 0;
}
