//杜教筛：http://www.cnblogs.com/SovietPower/p/8350374.html 
//使用数组这个trick存的话 对于多组询问就要重新计算了 
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long LL;
const int N=5e6;

int mu[N+3],P[N+3],cnt;
LL sum2[15000],Max;
bool Not_P[N+3];

void Init()
{
	mu[1]=1;
	for(int i=2;i<Max;++i)
	{
		if(!Not_P[i]) P[++cnt]=i,mu[i]=-1;
		for(int j=1;j<=cnt&&i*P[j]<Max;++j)
		{
			Not_P[i*P[j]]=1;
			if(!(i%P[j])) {mu[i*P[j]]=0; break;}
			mu[i*P[j]]=-mu[i];
		}
	}
	for(int i=1;i<Max;++i) mu[i]+=mu[i-1];
}
const int EQU=-2333333;
LL Calc(LL n,LL mx)
{
	if(n<Max) return mu[n];
	if(sum2[mx/n]!=EQU) return sum2[mx/n];
	LL ans=1;
	for(LL nxt,i=2;i<=n;i=nxt+1)
		nxt=n/(n/i),ans-=(nxt-i+1)*Calc(n/i,mx);
	return sum2[mx/n]=ans;
}

int main()
{
	LL a,b;scanf("%lld%lld",&a,&b);
//	printf("%.3lf %.3lf\n",pow(a,0.667),pow(b,0.667));
	Max=pow(b,0.667), Init();
	std::fill(sum2,sum2+15000,EQU); LL ans1=Calc(b,b);
	std::fill(sum2,sum2+15000,EQU); LL ans2=Calc(a-1,a-1);
	printf("%lld",ans1-ans2);

	return 0;
}
