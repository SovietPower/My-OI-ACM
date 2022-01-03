#include <set>
#include <map>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
#define mod 1000000007
#define Add(x,v) (x+=v)>=mod&&(x-=mod)
typedef long long LL;
const int N=2e5+5;

int f[N][3];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	int n=read(),L=read(),R=read();
	int l=(L+2)/3*3,r=R/3*3;
	int v0=l<=r?(r-l)/3+1:0;
	int v1=v0?v0-(R%3==0)+(L%3==1):(L%3==1||R%3==1);
	int v2=R-L+1-v0-v1;
//	printf("l:%d r:%d v0:%d v1:%d v2:%d\n",l,r,v0,v1,v2);
	f[0][0]=1;
	for(int i=0; i<n; ++i)
	{
		for(int j=0,val; j<3; ++j)
			if((val=f[i][j]))
			{
				Add(f[i+1][j],1ll*val*v0%mod);
				Add(f[i+1][(j+1)%3],1ll*val*v1%mod);
				Add(f[i+1][(j+2)%3],1ll*val*v2%mod);
			}
//		for(int j=0; j<3; ++j) printf("f[%d][%d]=%d\n",i+1,j,f[i+1][j]);
	}
	printf("%d\n",f[n][0]);

	return 0;
}
