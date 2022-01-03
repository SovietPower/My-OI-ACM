/*
3272ms	68628K / 69284kb	8496ms
����ѯ�ʶ����������ߵ����·��
$f[i][j]$��ʾ��$i$�ߵ�$j$������Ҫ���ٲ�����ʾ����ֻ��$O(n^2\log n)$��= =~~���Ǹо��ܿ���$70$�֡�~~

ע�⵽��$i$��������$j$���ܵ���ĵ㶼��һ��һ�εġ����Բ�����$f[i][j]$��ʾ����$i$��������$j$���ܵ��������ߵ���ʲô����ô$f[i][j+1]=\min\limits_{k=f[i][j]}^{i-1}L[k]$��
�������ǻ�û�п��������ߵ���������Է���һ��·�����ֻ��������һ�Ρ�
��ô��һ�¾ͺ��ǡ������Ϳ���$O(n^2)$����

ע�⵽��һ����ʵ�ʿ��Ա�����$f[i][j]$��ʾ����$i$��������$2^j$��������Ե��ġ����ǻ�Ҫ���ǵ�һ�������ߵ���������Բ���ֱ��������ʾ��$i\sim n$��Щ����$2^j$��������Ե��ġ�
��$Calc(i,p)$��ʾ����$i$�ֱ��ߵ�$p\sim i$���е��ܹ���Ҫ�߶�Զ����ѯ��$[l,r]$���$Calc(i,l)-Calc(i,r+1)$��
��ô��ά��һ��$sum[i][j]$��ʾ����$i$�������ֱ��ߵ�$f[i][j]\sim i$�ܹ���Ҫ�߶�Զ����ô$sum[i][j]=sum[i][j-1]+sum[f[i][j-1]][j-1]+(f[i][j]-f[i][j-1])\times2^{j-1}$��

����$Calc$��ʱ�򣬹���������һ���Ĵ�������ֱ����$i$��������һ���ߵ�$L[i]$������$L[i]$��ߵĲ��ֶ��п�����Ҫ$i$�����ߣ����������÷���$f$�Ķ��壬ͬʱ�����Ѿ�����һ��Ҳ���Կ�����������һ����
ע��ά��һ������$tot$��ʾ֮ǰһ�������˶��پ��롣

����[��ϯ��������]���Ҳ�д��qwq ~~��~~��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define BIT 18
#define gc() getchar()
#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=3e5+5;

int L[N],f[BIT+1][N];
LL sum[BIT+1][N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
int Gcd(int a,int b)
{
	return b?Gcd(b,a%b):a;
}
LL Calc(int l,int p,const int bit)
{
	if(L[p]<=l) return p-l;
	LL ans=p-L[p],tot=1; p=L[p];
	for(int i=bit; ~i; --i)
		if(f[i][p]>=l) ans+=sum[i][p]+(p-f[i][p])*tot, tot+=1<<i, p=f[i][p];
	return ans+(p-l)*(tot+1);//(r-l)*tot+r-l
}

int main()
{
	const int n=read(); int bit=23;
	while(1<<bit>n) --bit;
	for(int i=2; i<=n; ++i) L[i]=read();
	f[0][n]=L[n];
	for(int i=n-1; i; --i) f[0][i]=std::min(f[0][i+1],L[i]), sum[0][i]=i-f[0][i];
	for(int j=1; j<=bit; ++j)
	{
		LL t=1ll<<j-1;
		for(int i=1; i<=n; ++i)
			f[j][i]=f[j-1][f[j-1][i]], sum[j][i]=sum[j-1][i]+sum[j-1][f[j-1][i]]+(f[j-1][i]-f[j][i])*t;
	}
	for(int Q=read(); Q--; )
	{
		int l=read(),r=read(),x=read(),b=r-l+1;
		LL a=Calc(l,x,bit)-Calc(r+1,x,bit); int g=Gcd(b,a%b);
		printf("%lld/%d\n",a/g,b/g);
	}

	return 0;
}
