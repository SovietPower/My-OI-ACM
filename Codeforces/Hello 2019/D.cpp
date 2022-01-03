#include <set>
#include <map>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define pc putchar
#define mod 1000000007
#define Mod(x) x>=mod&&(x-=mod)
typedef long long LL;
const int N=100005;//2e7+5;

int cnt,inv[N],f[N],fac2[N],inv2[N],tot[N];
LL fac[N];
std::vector<int> vec[N];

void Divide(LL x)
{
	cnt=0;
	for(int i=1; 1ll*i*i<=x; ++i)
		if(!(x%i))
		{
			fac[++cnt]=i;
			if(1ll*i*i!=x) fac[++cnt]=x/i;
		}
	std::sort(fac+1,fac+1+cnt);
	for(int i=1; i<=cnt; ++i) fac2[i]=fac[i]%mod;
}/*
1000000000000000 4000
999999999999945 10000
866421317361600 10000

*/

int main()
{
//	int mx=0; LL p;
//	printf("%I64d\n",(LL)1e15-999999999990000ll);
//	for(LL i=999999999999900ll; i<=(LL)1e15; ++i)
//		Divide(i), cnt>mx&&(p=i,mx=cnt);//, printf("c[%I64d]=%d\t",i,cnt);
//	printf("mx:%d p:%I64d\n",mx,p);
//	return 0;

	LL n; int K;
	scanf("%I64d%d",&n,&K);
	Divide(n); inv[1]=1;
	printf("cnt:%d\n",cnt);
	for(int i=2; i<=cnt; ++i) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
//	for(int i=2; i<=1000; ++i) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;

	for(int i=1; i<=cnt; ++i)
	{
		for(int j=1; j<=i; ++j) !(fac[i]%fac[j])&&(vec[i].push_back(j),0);
		inv2[i]=inv[tot[i]=vec[i].size()];
	}

	f[cnt]=1;
	for(int k=1; k<=K; ++k)
	{
		for(int i=1,v; i<=cnt; ++i)
			if((v=f[i]))
			{
				f[i]=0;
				for(int j=tot[i]-1,val=1ll*inv2[i]*v%mod; ~j; --j)
					f[vec[i][j]]+=val, Mod(f[vec[i][j]]);
//				int c=0; f[i]=0;
//				for(int j=1; j<=i; ++j) c+=!(fac[i]%fac[j]);
//				for(int j=1,iv=inv[c]; j<=i; ++j)
//					if(!(fac[i]%fac[j]))
//						f[j]+=1ll*iv*v%mod, Mod(f[j]);
			}
//		for(int i=1; i<=cnt; ++i) printf("f[%d]=%d\n",i,f[i]);
//		LL ans=0;
//		for(int i=1; i<=cnt; ++i) ans+=1ll*f[i]*fac2[i]%mod;
//		printf("k:%d ans:%I64d\n",k,ans%mod);
	}
	LL ans=0;
	for(int i=1; i<=cnt; ++i) ans+=1ll*f[i]*fac2[i]%mod;
	printf("%I64d\n",ans%mod);
//	int a,b;
//	while(~scanf("%d%d",&a,&b)) printf("%d/%d=%I64d\n",a,b,1ll*a*inv[b]%mod);
	

	return 0;
}
