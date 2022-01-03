/*
118ms	7212KiB
x*atk[i] - y*p[i] = hp[i]
对于每条龙可以求一个满足条件的x0，然后得到其通解x[i] = x0 + p[i]/gcd*k。
怎么合并所有龙的通解？可以直接写成 Ans ≡x0(mod p[i]/gcd)，用扩展中国剩余定理合并即可。
所有p[i]=1时要特判。(为啥呢...反正我知道它不对...)
所有p[i]=hp[i]时同余方程结果会是0，这显然不对。这种情况对于每条龙造成的伤害应该是p[i]的倍数(p[i]|x*atk[i])。算出击杀每条龙的最小的x求个lcm即可。
*/
#include <set>
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define Failed return (void)puts("-1")
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define set_It std::multiset<LL>::iterator
typedef long long LL;
const int N=1e5+7;

int n,m,rew[N]/*reward*/;
LL hp[N],p[N],a[N],md[N];//Ans = a[i] (mod md[i])
std::multiset<LL> st;//!
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline LL readll()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline LL Mult(LL a,LL b,LL p)
{
	LL tmp=a*b-(LL)((long double)a/p*b+1e-8)*p;
	return tmp<0?tmp+p:tmp;
}
LL Gcd(LL a,LL b){
	return b?Gcd(b,a%b):a;	
}
void Exgcd(LL a,LL b,LL &g,LL &x,LL &y)
{
	if(!b) g=a,x=1,y=0;
	else Exgcd(b,a%b,g,y,x),y-=a/b*x;
}
void Spec1()
{
	int ans=0; set_It it;
	for(int i=1; i<=n; ++i)
	{
		it=st.upper_bound(hp[i]);
		if(it!=st.begin()) --it;
		if(!(*it)) Failed;
		ans=std::max(ans,(int)((hp[i]+(*it)-1)/(*it)));//(int)ceil(1.0*hp[i]/(*it)));
		st.erase(it), st.insert(rew[i]);
	}
	printf("%d\n",ans);
}
//void Spec2()
//{
//	int ans=1; set_It it;
//	for(int i=1,need; i<=n; ++i)
//	{
//		it=st.upper_bound(hp[i]);
//		if(it!=st.begin()) --it;
//		if(!(*it)) Failed;
//		need=(hp[i]+(*it)-1)/(*it), ans=ans/Gcd(ans,need)*need;
//		st.erase(it), st.insert(rew[i]);
//	}
//	printf("%d\n",ans);
//}
void Solve()
{
	bool f1=1;//!
	for(int i=1; i<=n; ++i) if(p[i]!=1) {f1=0; break;}
	if(f1) {Spec1(); return;}
//	f1=1;//然而数据没有这种情况...还是要有的 
//	for(int i=1; i<=n; ++i) if(p[i]!=hp[i]) {f1=0; break;}
//	if(f1) {Spec2(); return;}

	set_It it; int cnt=0;
	for(int i=1; i<=n; ++i)
	{
		it=st.upper_bound(hp[i]);
		if(it!=st.begin()) --it;
		if(hp[i]&&!(*it)) Failed;

		int atk=*it;
		LL gcd,x0,y0,P;
		Exgcd(atk,p[i],gcd,x0,y0);
		if(hp[i]%gcd) Failed;
		P=p[i]/gcd, x0=(x0%P+P)%P;
		a[++cnt]=Mult(x0,hp[i]/gcd,P), md[cnt]=P;
		st.erase(it), st.insert(rew[i]);
	}

	LL A=a[1],M=md[1],g,x,y,t,Mod;
	for(int i=2; i<=cnt; ++i)
	{
		Exgcd(M,md[i],g,x,y);
		if((a[i]-A)%g) Failed;
		t=md[i]/g, x=Mult(x,(a[i]-A)/g,t), x=(x%t+t)%t;
		Mod=M*t, A+=Mult(x,M,Mod)/*直接x*M会炸?...*/, A%=Mod, M=Mod;
	}
	printf("%lld\n",A);
}

int main()
{
	freopen("dragon.in","r",stdin);
	freopen("dragon.out","w",stdout);

	for(int Case=read(); Case--; )
	{
		st.clear();
		n=read(), m=read();
		for(int i=1; i<=n; ++i) hp[i]=readll();
		for(int i=1; i<=n; ++i) p[i]=readll();
		for(int i=1; i<=n; ++i) rew[i]=read();
		for(int i=1; i<=m; ++i) st.insert(read());
		Solve();
	}
	return 0;
}
