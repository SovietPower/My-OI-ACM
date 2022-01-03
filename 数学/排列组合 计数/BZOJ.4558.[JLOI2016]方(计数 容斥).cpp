/*
39924kb	2744ms
https://www.cnblogs.com/SovietPower/p/10061508.html
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define mod 100000007
#define Legal(x,y) (x>=0&&x<=n&&y>=0&&y<=m)
typedef long long LL;
const int N=2005;

int n,m,t2,t3,t4;
struct Hash_Table
{
	#define Sz 10000000
	int Enum,H[Sz+2],nxt[N]; LL to[N];
	inline void Insert(int x,int y)
	{
		LL v=1ll*x*1000001+y; x=v%Sz;
		to[++Enum]=v, nxt[Enum]=H[x], H[x]=Enum;
	}
	inline bool Count(int x,int y)
	{
		LL v=1ll*x*1000001+y;
		for(int x=v%Sz,i=H[x]; i; i=nxt[i])
			if(to[i]==v) return 1;
		return 0;
	}
}hs;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline LL Calc(int h,int l,int r)
{
	int t=std::min(h,l+r);
	if(!t) return 0;
	LL res=1ll*t*(t+3);
	if(t>l) res-=1ll*(t-l)*(t-l+1);
	if(t>r) res-=1ll*(t-r)*(t-r+1);
	return (res>>1)%mod;
}
int Calc1(int x,int y)
{
	int u=x,d=n-x,l=y,r=m-y;
	LL res=(Calc(u,l,r)+Calc(d,l,r)+Calc(l,u,d)+Calc(r,u,d))%mod;
	res=res-std::min(u,l)-std::min(u,r)-std::min(d,l)-std::min(d,r);
	return (res+mod)%mod;
}
void Calc2(int x1,int y1,int x2,int y2)
{
	if(!Legal(x1,y1)||!Legal(x2,y2)) return;
	int t=hs.Count(x1,y1)+hs.Count(x2,y2);
	++t2;
	if(t>=1) ++t3;//if更快啊。。
	if(t>=2) ++t3, ++t4;//就算是4个点，以i,j,k为顶点的正方形此时是算两个（i,j固定，k有两个）
//	++t2, t==1?(++t3):(t==2?(t3+=2,++t4):0);
}

int main()
{
	static int X[N],Y[N];
	n=read(),m=read(); int K=read();
	for(int i=1; i<=K; ++i) X[i]=read(),Y[i]=read(),hs.Insert(X[i],Y[i]);
	LL ans=0;
	for(int i=1,lim=std::min(n,m); i<=lim; ++i) ans+=1ll*(n-i+1)*(m-i+1)%mod*i%mod;
	for(int i=1; i<=K; ++i) ans-=Calc1(X[i],Y[i]);
	for(int i=1; i<=K; ++i)
	{
		int x1=X[i],y1=Y[i];
		for(int j=i+1; j<=K; ++j)
		{
			int x2=X[j], y2=Y[j], dx=x1-x2, dy=y1-y2;
			Calc2(x1+dy, y1-dx, x2+dy, y2-dx);//边 
			Calc2(x1-dy, y1+dx, x2-dy, y2+dx);
			if((std::abs(dx)+std::abs(dy))&1) continue;
			int dx2=dx-dy>>1, dy2=dx+dy>>1;//对角线 
			Calc2(x1-dx2, y1-dy2, x2+dx2, y2+dy2);
		}
	}
	ans=ans%mod+t2-t3/3+t4/6;
	printf("%lld\n",(ans%mod+mod)%mod);

	return 0;
}
