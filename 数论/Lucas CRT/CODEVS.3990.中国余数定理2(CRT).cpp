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
	if(res<=R) ans=(R-res)/M+1;//[res,R]�н�ĸ��� //res������С���������ˣ�>R��Ȼ[L,R]�޽�(L,R>0)
	if(res<=L) ans-=(L-res)/M+1;//[res,L](res<=L)�н�ĸ���  ע������=LҲҪ����(����)����Ϊ��һ��Ҫ���б߽�L�Ľ� 
	if(!((L-res)%M)) ++ans;//�߽�L�Ľ�
	if(ans)
		if(L<=res) Min=res;//Min=res-(res-L)/M*M;//res��������С�Ľ� 
		else /*if(res<L)*/ Min=res+((L-res-1)/M+1)*M;//ans�ǽ�ĸ�������Ҫ�������!
	printf("%lld\n%lld",ans,Min);
}

int main()
{
	n=read(),L=read(),R=read();
	for(int i=1; i<=n; ++i) m[i]=read(),B[i]=read();
	CRT();
	return 0;
}
