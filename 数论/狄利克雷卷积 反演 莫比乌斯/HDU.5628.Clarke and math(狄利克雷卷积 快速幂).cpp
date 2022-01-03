/*
http://www.cnblogs.com/SovietPower/p/8351671.html
刚开始要将ans初始化为单位元，即ans[2~n]=0,ans[1]=1,这样最初乘一个函数还是这个函数本身，即1 
初始化x为I,I(n)=1 
注:1.两个函数狄利克雷卷积是个函数 
2.加两个数取模不能直接用-=mod 
*/
#include<cstdio>
#include<cctype>
#include<cstring>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5,mod=1e9+7;

int n,k;
LL f[N],ans[N],tmp[N],x[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
#define Mod(x) x>=mod?x-=mod:0
void Dirichlet(LL *a,LL *b)//a*b
{
	memset(tmp,0,sizeof tmp);
	for(int i=1;i*i<=n;++i)
	{
		tmp[i*i]+=a[i]*b[i]%mod, Mod(tmp[i*i]);
		for(int j=i+1;i*j<=n;++j)//下边加上a[i]*b[j]和a[j]*b[i]，所以j从i+1开始即可 
			(tmp[i*j]+=a[i]*b[j]%mod+a[j]*b[i]%mod)%=mod;//注意这加两个数不能一步用Mod取模。。
	}
	memcpy(a,tmp,sizeof tmp);
}
void Solve()
{
	for(int i=1;i<=n;++i) x[i]=1,ans[i]=0;//x:I^0
	ans[1]=1;//ans:e
	for(;k;k>>=1,Dirichlet(x,x))
		if(k&1) Dirichlet(ans,x);
	Dirichlet(ans,f);
	for(int i=1;i<=n;++i) printf("%lld%c",ans[i],i==n?'\n':' ');//空格及换行符有要求 
}

int main()
{
	for(int t=read();t--;)
	{
		n=read(),k=read();
		for(int i=1;i<=n;++i) f[i]=read();
		Solve();
	}
	return 0;
}
