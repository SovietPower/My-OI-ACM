//http://www.cnblogs.com/SovietPower/p/8449147.html
#include <cstdio>
#include <cctype>
#define gc() getchar()
typedef long long LL;
const int N=13;

LL n,L,R,B[N],m[N];

inline LL read()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
//void Exgcd(LL a,LL b,LL &x,LL &y)
//{
//	if(!b) x=1,y=0;
//	else {
//		Exgcd(b,a%b,x,y);
//		LL t=x; x=y, y=t-a/b*y;
//	}
//}
void Exgcd(LL a,LL b,LL &x,LL &y)
{
	if(!b) x=1, y=0;
	else Exgcd(b,a%b,y,x), y-=a/b*x;
}
void CRT()
{
	LL M=1,res=0,x,y,Mi,ans=0,Min=0;
	for(int i=1; i<=n; ++i) M*=m[i];
	for(int i=1; i<=n; ++i)
	{
		Mi=M/m[i], Exgcd(Mi,m[i],x,y);
		x=(x%m[i]+m[i])%m[i];
//		if(!x) x=m[i];
		res+=B[i]*Mi*x;
	}
	res%=M;
	if(!res) res=M;
	if(res<=R) ans=(R-res)/M+1;//[res,R]中解的个数 //res就是最小正整数解了，>R显然[L,R]无解(L,R>0)
	if(res<=L) ans-=(L-res)/M+1;//[res,L](res<=L)中解的个数  注意这里=L也要计算(减掉)，因为下一行要特判边界L的解 
	if(!((L-res)%M)) ++ans;//边界L的解
	if(ans)
		if(L<=res) Min=res;//Min=res-(res-L)/M*M;//res就已是最小的解 
		else /*if(res<L)*/ Min=res+((L-res-1)/M+1)*M;//ans是解的个数不是要运算的数!
	printf("%lld\n%lld",ans,Min);
}

int main()
{
	n=read(),L=read(),R=read();
	for(int i=1; i<=n; ++i) m[i]=read(),B[i]=read();
	CRT();
	return 0;
}
