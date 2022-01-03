#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
#define gc() getchar()
#define mp std::make_pair
#define pr std::pair<int,int>
#define mod 998244353
typedef long long LL;
const int N=1003;

int n,m,A[N][N],inv[N*N],f[N*N],ref[N*N],num[N*N]:
LL sumx[N*N],sumy[N*N],sx2[N*N],sy2[N*N];
pr pos[N*N];
std::vector<pr> v[N*N];
bool vis[N*N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int Find(int x,int r)
{
	int l=1,mid;
	while(l<r)
		if(ref[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}

int main()
{
	n=read(), m=read(); int lim=n*m;
	inv[1]=1;
	for(int i=2; i<=lim; ++i) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	int t=0;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j) ref[++t]=A[i][j]=read();
	std::sort(ref+1,ref+1+t); int cnt=1;
	for(int i=2; i<=t; ++i) if(ref[i]!=ref[i-1]) ref[++cnt]=ref[i];
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j)
		{
			A[i][j]=Find(A[i][j],cnt); int tmp=A[i][j];
			++num[tmp], pos[tmp]=mp(i,j);
			v[tmp].push_back(mp(i,j));
			sx2+=1ll*i*i%mod
		}
	int r=read(),c=read();
	LL sum=0; int sum=num[1];
	for(int i=2,l=A[r][c]; i<l; ++i)
	{
		
		f[i]=
		sum+=num[i];
	}
	printf("%d\n",f[A[r][c]-1]);

	return 0;
}
