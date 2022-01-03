/*
1652kb	4352ms
���⼴��������С��$m$�������У�ѡ��$n$������ʹ��������Ϊ$0$�ķ�������
��$G(x)=[x������]$����ʵ���Ƕ�$G(x)$��$n$���������õ�����ʽ�ĵ�$0$�
���$n$��С������һ�δε�FWT����ʵ���ڵ�һ��FWT֮��ֱ�ӿ����ݾ����ˣ�����Ҫ�м�IFWTת��ȥ��
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define inv2 500000004
#define mod 1000000007
#define Add(x,y) (x+y>=mod?x+y-mod:x+y)
#define Sub(x,y) (x<y?x-y+mod:x-y)
typedef long long LL;
const int N=65540;

int not_P[N],P[N>>2];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void Init(int n)
{
	not_P[1]=1;
	for(int i=2,cnt=0; i<=n; ++i)
	{
		if(!not_P[i]) P[++cnt]=i;
		for(int j=1; j<=cnt&&i*P[j]<=n; ++j)
		{
			not_P[i*P[j]]=1;
			if(!(i%P[j])) break;
		}
	}
}
void FWT(int *a,int lim,int opt)
{
	for(int i=2; i<=lim; i<<=1)
		for(int j=0,mid=i>>1; j<lim; j+=i)
			for(int k=j,x,y; k<j+mid; ++k)
			{
				x=a[k],y=a[k+mid];
				a[k]=Add(x,y), a[k+mid]=Sub(x,y);
				if(opt==-1) a[k]=1ll*a[k]*inv2%mod, a[k+mid]=1ll*a[k+mid]*inv2%mod;
			}
}
void FP(int *x,int *t,int n,int k)
{
	for(; k; k>>=1)
	{
		if(k&1) for(int i=0; i<n; ++i) t[i]=1ll*t[i]*x[i]%mod;
		for(int i=0; i<n; ++i) x[i]=1ll*x[i]*x[i]%mod;
	}
}

int main()
{
	static int A[N],res[N];
	Init(50000);
	int n,m;
	while(~scanf("%d%d",&n,&m))
	{
		memset(A,0,sizeof A);
		for(int i=1; i<=m; ++i) A[i]=!not_P[i];
		int lim=1; while(lim<=m) lim<<=1;
		FWT(A,lim,1);
		for(int i=0; i<lim; ++i) res[i]=A[i];
		FP(A,res,lim,n-1), FWT(res,lim,-1);
		printf("%d\n",res[0]);
	}
	return 0;
}
