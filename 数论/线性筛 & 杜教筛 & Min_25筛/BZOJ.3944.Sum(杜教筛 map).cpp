//phi[]要longlong！
#include <map>
#include <cstdio>
#include <algorithm>
typedef long long LL;
const int N=6e6;//多预处理会快很多。

int cnt,P[N>>3],mu[N];
LL phi[N];
bool Not_p[N];
std::map<int,LL> mp[2];
std::map<int,LL>::iterator it;

void Make_Table()
{
	mu[1]=phi[1]=1;
	for(int i=2; i<N; ++i)
	{
		if(!Not_p[i]) P[++cnt]=i, mu[i]=-1, phi[i]=i-1;
		for(int j=1; j<=cnt&&i*P[j]<N; ++j)
		{
			Not_p[i*P[j]]=1;
			if(i%P[j]) mu[i*P[j]]=-mu[i], phi[i*P[j]]=phi[i]*(P[j]-1);
			else {mu[i*P[j]]=0, phi[i*P[j]]=phi[i]*P[j]; break;}
		}
	}
	for(int i=2; i<N; ++i) mu[i]+=mu[i-1],phi[i]+=phi[i-1];
}
LL Calc_p(LL n)//这的n为什么必须要开longlong(2147483647)？
{
	if(n<N) return phi[n];
	if((it=mp[0].find(n))!=mp[0].end()) return it->second;
	LL res=n*(n+1)>>1;
//	if(n&1) res=(n+1)/2*n;
//	else res=n/2*(n+1);
	for(LL nxt,i=2; i<=n; i=nxt+1)//nxt+1!可能爆int?
		nxt=n/(n/i), res-=Calc_p(n/i)*(nxt-i+1);
	return mp[0][n]=res;
}
LL Calc_m(int n)
{
	if(n<N) return mu[n];
	if((it=mp[1].find(n))!=mp[1].end()) return it->second;
	LL res=1;
	for(LL nxt,i=2; i<=n; i=nxt+1)
		nxt=n/(n/i), res-=Calc_m(n/i)*(nxt-i+1);
	return mp[1][n]=res;
}

int main()
{
	Make_Table();
	int T,n; scanf("%d",&T);
	while(T--)
		scanf("%d",&n),printf("%lld %lld\n",Calc_p(n),Calc_m(n));
	return 0;
}
