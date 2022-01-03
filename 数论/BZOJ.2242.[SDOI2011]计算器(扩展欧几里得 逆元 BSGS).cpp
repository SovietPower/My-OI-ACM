/*
2.关于同余方程ax ≡b(mod p)，可以用Exgcd做，但注意到p为质数，y一定有逆元 
首先a%p=0时 仅当b=0时有解；然后有x ≡b*a^-1(mod p)，a,p互质，可用快速幂求a的逆元，*b的得到x 
但是扩欧还是比快速幂快的 
还是longlong..
*/
#include<map>
#include<cmath>
#include<cstdio>
#include<cctype>
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int MAXIN=1<<17;
std::map<LL,int> ref;
char IN[MAXIN],*SS=IN,*TT=IN;

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
//------扩欧解同余方程 
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
//------
//------利用逆元解同余方程 
//void Solve2(int a,int b,int p)//ax=b(mod p)->x=b*a^-1(mod p)
//{
//	if(!(a%p)) {puts(b?"Orz, I cannot find x!":"0"); return;}
//	int inv=Fast_Pow(a,p-2,p);
//	printf("%d\n",1LL*b*inv%p);
//}
//------
void BSGS(int a,int b,int p)//a^x ≡b(mod p)
{
	if(gcd(a,p)!=1) {puts("Orz, I cannot find x!"); return;}
	ref.clear();
	int m=ceil(sqrt(p-1));
	LL t=b%p,AM;
	for(int j=0;j<=m;++j) ref[t]=j,t=t*a%p;
	AM=Fast_Pow(a,m,p),t=AM;
	for(int i=1;i<=m;++i,t=t*AM%p)
		if(ref[t]) {printf("%d\n",(1LL*i*m-ref[t])%p); return;}
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
