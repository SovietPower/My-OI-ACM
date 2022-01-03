/*
1228kb	28ms
若点数确定那么ans = (n-2)!/[(d1-1)!(d2-1)!...(dn-1)!] 
现在把那些不确定的点一起考虑(假设有m个)，它们在Prufer序列中总出现数就是left=n-2-(d1-1)-(d2-1)-...-(dn-1)
这left个数本身又有m^{left}种 
所以 ans = (n-2)!/[(d1-1)!(d2-1)!...(dn-1)!left!]*m^{left} 
显然需要高精度。为避免高精除需要对每个阶乘分解质因数(这个组合数算出来一定是整数，所以分解质因数和分子减掉分母的次数即可)
n!中含质因子p个数公式: f(n)=f(n/p)+n/p 
注意下无解的两种情况 
要乘的数很小 就容易了 
*/
#include <cstdio>
const int N=1005,Base=10000;

int n,dgr[N],up[N],down[N],cnt,P[N],ans[100005];
bool Not_P[N+3];

void Init()
{
	Not_P[1]=1;
	for(int i=2; i<N; ++i)
	{
		if(!Not_P[i]) P[++cnt]=i;
		for(int j=1; j<=cnt&&i*P[j]<N; ++j)
		{
			Not_P[i*P[j]]=1;
			if(!(i%P[j])) break;
		}
	}
}
void Divide(int x,int *a)
{
	for(int i=1; i<=cnt&&P[i]<=x; ++i)
		for(int tmp=x; tmp; tmp/=P[i]) a[i]+=tmp/P[i];
}
void Mult(int *a,int b)
{
	for(int i=1; i<=a[0]; ++i) a[i]*=b;
//		if(a[i]/Base) a[i+1]+=a[i]/Base, a[i]%=Base;//需要都乘完后再进位 
	for(int i=1; i<=a[0]; ++i)
		if(a[i]/Base) a[i+1]+=a[i]/Base, a[i]%=Base;
//		else break;//WA:显然不可以嘛 
	if(a[a[0]+1]) ++a[0];
}
void Print(int *a)
{
	printf("%d",a[a[0]]);
	for(int i=a[0]-1; i; --i) printf("%0*d",4,a[i]);
//	putchar('\n');
}

int main()
{
	scanf("%d",&n), Init();
	int tot=0,m=0;
	for(int i=1; i<=n; ++i)
	{
		scanf("%d",&dgr[i]);
		if(dgr[i]>1) tot+=dgr[i]-1, Divide(dgr[i]-1,down);
		else if(dgr[i]<0) ++m;
		else if(!dgr[i]) tot=N;
	}
	if(tot>n-2 || (tot==n-2&&!m)) {putchar('0'); return 0;}
	int left=n-2-tot;
	Divide(n-2,up), Divide(left,down);
	for(int i=1; i<=cnt; ++i) up[i]-=down[i];
//	for(int i=1; i<=cnt; ++i) printf("%d^%d\n",P[i],up[i]);
	ans[ans[0]=1]=1;
	for(int i=1; i<=cnt; ++i)
		while(up[i]--) Mult(ans,P[i]);
	for(int i=1; i<=left; ++i) Mult(ans,m);
	Print(ans);

	return 0;
}
