/*
2.关于同余方程ax ≡b(mod p)，可以用Exgcd做，但注意到p为质数，y一定有逆元 
首先a%p=0时 仅当b=0时有解；然后有x ≡b*a^-1(mod p)，a,p互质，可用快速幂求a的逆元，*b的得到x 
但是扩欧还是比快速幂快的 
还是longlong..
*/
#include<cmath>
#include<cstdio>
#include<cctype>
#include<cstring>
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int MAXIN=1<<17,N=1e5,mod=5e6;
char IN[MAXIN],*SS=IN,*TT=IN;
struct HASH
{
	int Enum,H[mod+3],nxt[N],to[N],val[N];
	void Init() {memset(H,0,sizeof H), Enum=0;}
	inline void AddEdge(int u,int v)
	{
		int x=u%mod;
		for(int i=H[x];i;i=nxt[i])
			if(val[i]==u) {to[i]=v; return;}
		to[++Enum]=v, val[Enum]=u, nxt[Enum]=H[x], H[x]=Enum;
	}
	int Query(int u)
	{
		int x=u%mod;
		for(int i=H[x];i;i=nxt[i])
			if(val[i]==u) return to[i];
		return -1;
	}
}hs;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
int Fast_Pow(LL a,int k,int p)
{
	LL t=1;
	for(;k;k>>=1,a=a*a%p)
		if(k&1) t=t*a%p;
	return t;
}
int gcd(int a,int b)
{
	return b?gcd(b,a%b):a;
}
void Exgcd(int a,int b,int &x,int &y)
{
	if(!b) {x=1,y=0; return;}
	Exgcd(b,a%b,x,y);
	int t=x; x=y,y=t-a/b*y;
}
void Solve2(int a,int b,int p)//calc ax=b(mod p)->ax-py=b
{
	int g=gcd(a,p);
	if(b%g) {puts("Orz, I cannot find x!"); return;}
	int x,y;
	Exgcd(a,p,x,y);//calc ax+by=gcd(a,b) or a/=g,b/=g,ax+by=1
	x=1LL*x*(b/g)%p;//ax*c/gcd+by*c/gcd=c*gcd/gcd=c
	p/=g;
	printf("%d\n",(x%p+p)%p);//x=x_0+k*p/g
}
void BSGS(int a,int b,int p)//a^x ≡b(mod p)
{
	if(gcd(a,p)!=1) {puts("Orz, I cannot find x!"); return;}
	hs.Init();
	int m=ceil(sqrt(p-1));
	LL t=b%p,AM;
	for(int j=0;j<=m;++j) hs.AddEdge(t,j),t=t*a%p;
	AM=Fast_Pow(a,m,p),t=AM;
	for(int v,i=1;i<=m;++i,t=t*AM%p)
		if((v=hs.Query(t))!=-1) {printf("%d\n",(1LL*i*m-v)%p); return;}
	puts("Orz, I cannot find x!");
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("2242.in","r",stdin);
#endif

	int t=read(),k=read(),a,b,p,x,y;
	while(t--)
	{
		a=read(),b=read(),p=read();
		if(k==1) printf("%d\n",Fast_Pow(a,b,p));
		else if(k==2) Solve2(a,b,p);
		else BSGS(a,b,p);
	}
	return 0;
}
