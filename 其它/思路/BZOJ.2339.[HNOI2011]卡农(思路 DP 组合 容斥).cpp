//4728kb	404ms
//www.cnblogs.com/SovietPower/p/9171435.html
#include <cstdio>
#include <algorithm>
#define P (100000007)
#define Mul(a,b) (1ll*(a)*(b)%P)
#define Sub(a,b) (a<b ? (a)-(b)+P : (a)-(b))//()!
const int N=1e6+5;

int n,m,f[N];

inline int FP(int x,int k)
{
	int t=1;
	for(; k; k>>=1, x=Mul(x,x))
		if(k&1) t=Mul(t,x);
	return t;
}

int main()
{
	scanf("%d%d",&n,&m);
	int pw2=FP(2,n)-1;//if(!pw2) pw2=P-1; else --pw2;

	f[0]=1, f[1]=0;
	for(int i=2,Alas=pw2; i<=m; ++i)
	{
		f[i]=(Alas-f[i-1]+P-1ll*f[i-2]*(i-1)%P*Sub(pw2,i-2)%P+P)%P;
		Alas=Mul(Alas, Sub(pw2+1,i));//别去用数组存A[]了。。
	}
	int inv=1;
	for(int i=2; i<=m; ++i) inv=Mul(inv,i);
	inv=FP(inv,P-2);
	printf("%lld",Mul(f[m],inv));

	return 0;
}
