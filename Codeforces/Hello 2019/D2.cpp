#include <set>
#include <map>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define pc putchar
#define mod 1000000007
#define Mod(x) x>=mod&&(x-=mod)
typedef long long LL;
const int N=5000005;//2e7+5;

int cnt,inv[N];
LL fac[N];
std::vector<int> vec[N];
struct Matrix
{
	#define N 3000
	int n,A[N][N];
	#undef N
	inline void Clear()
	{
		for(int i=0; i<n; ++i) memset(A[i],0,n<<2);
	}
	Matrix operator *(const Matrix &a)const
	{
		Matrix res; res.Clear(), res.n=n;
		for(int i=0; i<n; ++i)
			for(int j=0,v; j<n; ++j)
				if((v=A[i][j]))
				{
					LL tmp=0;
					for(int k=0; k<n; ++k)
					{
						res.A[i][k]+=1ll*v*a.A[j][k]%mod;
						Mod(res.A[i][k]);
					}
				}
		return res;
	}
	void Print()
	{
		for(int i=0; i<n; ++i,putchar('\n'))
			for(int j=0; j<n; ++j) printf("%d ",A[i][j]);
		putchar('\n');
	}
}t;//,Ans;

void Divide(LL x)
{
	cnt=0;
	for(int i=1; 1ll*i*i<=x; ++i)
		if(!(x%i))
		{
			fac[++cnt]=i;
			if(1ll*i*i!=x) fac[++cnt]=x/i;
		}
	std::sort(fac+1,fac+1+cnt);
}
void FP(Matrix &t,Matrix x,int k)
{
	t=x; --k;
	for(; k; k>>=1,x=x*x)
		if(k&1) t=t*x;
}
/*
1000000000000000 10000
999999999999945 10000

*/

int main()
{
//	int mx=0; LL p;
//	printf("%I64d\n",(LL)1e15-999999999990000ll);
//	for(LL i=999999999999900ll; i<=(LL)1e15; ++i)
//		Divide(i), cnt>mx&&(p=i,mx=cnt);//, printf("c[%I64d]=%d\t",i,cnt);
//	printf("mx:%d p:%I64d\n",mx,p);
//	return 0;

	LL n; int K;
	scanf("%I64d%d",&n,&K);// --K;
	Divide(n); inv[1]=1;
//	printf("cnt:%d\n",cnt);
	for(int i=2; i<=cnt; ++i) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;

	for(int i=1; i<=cnt; ++i)
		for(int j=1; j<=i; ++j)
			!(fac[i]%fac[j])&&(vec[i].push_back(j),0);
	for(int i=1; i<=cnt; ++i)
	{
		for(int j=vec[i].size()-1,inv2=inv[j+1]; ~j; --j)
			t.A[vec[i][j]-1][i-1]=inv2;
	}
//	t.Print();
	t.n=cnt;//, Ans.n=cnt, Ans.A[cnt-1][0]=1;
//	for(int k=1; k<=K; ++k)
//		Ans=t*Ans, printf("\nk:%d\n",k), Ans.Print();

	FP(t,t,K);//, Ans=t*Ans;

	LL ans=0;
	for(int i=0; i<cnt; ++i)
		ans+=1ll*t.A[i][cnt-1]*(fac[i+1]%mod)%mod;
	printf("%I64d\n",ans%mod);

	return 0;
}
