//35332 kb	7608 ms
//http://www.cnblogs.com/SovietPower/p/8710976.html
//跟Kelin dalao学一波卡常。怎么还是很慢QAQ 
//phi[]要longlong！
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int N=2e6;

int cnt,Max,P[N>>3];
LL phi[N],mu[N],sum[20005][2];
bool Not_p[N],vis[20005];

void Make_Table()
{
	mu[1]=phi[1]=1;
	for(int i=2; i<N; ++i)
	{
		if(!Not_p[i]) P[++cnt]=i, mu[i]=-1, phi[i]=i-1;
		for(int j=1,x; j<=cnt&&(x=i*P[j])<N; ++j)
		{
			Not_p[x]=1;
			if(i%P[j]) mu[x]=-mu[i], phi[x]=phi[i]*(P[j]-1);
			else {mu[x]=0, phi[x]=phi[i]*P[j]; break;}
		}
	}
	for(int i=2; i<N; ++i) mu[i]+=mu[i-1],phi[i]+=phi[i-1];
}
inline LL Get_phi(int n){
	return n<N?phi[n]:sum[Max/n][0];
}
inline LL Get_mu(int n){
	return n<N?mu[n]:sum[Max/n][1];
}
void Calc(int n)
{
	if(n<N) return;
	if(vis[Max/n]) return;
	int t=Max/n;
	vis[t]=1, sum[t][0]=((LL)n+1)*n>>1, sum[t][1]=1;//这只在前面转longlong不行！+1必须也longlong。
	for(LL nxt,i=2; i<=n; i=nxt+1){
		nxt=n/(n/i), Calc(n/i);
		sum[t][0]-=Get_phi(n/i)*(nxt-i+1), sum[t][1]-=Get_mu(n/i)*(nxt-i+1);
	}
}

int main()
{
	Make_Table();
	int T; scanf("%d",&T);
	while(T--){
		memset(vis,0,sizeof vis);
		scanf("%d",&Max);
		if(Max<N) printf("%lld %lld\n",phi[Max],mu[Max]);//mu[]如果是int就不要用%lld。
		else Calc(Max),printf("%lld %lld\n",sum[1][0],sum[1][1]);
	}
	return 0;
}
