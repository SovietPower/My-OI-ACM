//∂≈ΩÃ…∏£∫http://www.cnblogs.com/SovietPower/p/8350374.html 
#include<map>
#include<cstdio>
typedef long long LL;
const int N=5e6;

int mu[N+3],P[N+3],cnt;
bool Not_P[N+3];
std::map<LL,LL> sum;
//std::map<LL,LL>::iterator it;

void Init()
{
	mu[1]=1;
	for(int i=2;i<N;++i)
	{
		if(!Not_P[i]) P[++cnt]=i,mu[i]=-1;
		for(int j=1;j<=cnt&&i*P[j]<N;++j)
		{
			Not_P[i*P[j]]=1;
			if(!(i%P[j])) {mu[i*P[j]]=0; break;}
			mu[i*P[j]]=-mu[i];
		}
	}
	for(int i=2;i<N;++i) mu[i]+=mu[i-1];
}
LL Calc(LL n)
{
	if(n<N) return mu[n];
//	if((it=sum.find(n))!=sum.end()) return it->second;
	if(sum.count(n)) return sum[n];
	LL ans=1;
	for(LL nxt,i=2;i<=n;i=nxt+1)
		nxt=n/(n/i),ans-=(nxt-i+1)*Calc(n/i);
	return sum[n]=ans;
}

int main()
{
	Init();
	LL a,b;scanf("%lld%lld",&a,&b);
	printf("%lld",Calc(b)-Calc(a-1));

	return 0;
}
