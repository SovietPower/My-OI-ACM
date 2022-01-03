#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define pr std::pair<int,int>
#define mp std::make_pair
const int N=1e5+7;

int n,m,cnt,P[N],fac[N],sum;
pr A[3000005];
bool not_P[N];

int gcd(int x,int y){
	return y?gcd(y,x%y):x;
}
void Pre(int n)
{
	for(int i=2; i<=n; ++i)
	{
		if(!not_P[i]) P[++cnt]=i;
		for(int j=1; j<=cnt&&i*P[j]<=n; ++j)
		{
			not_P[i*P[j]]=1;
			if(!(i%P[j])) break;
		}
	}
	for(int i=2; i<=n; ++i)
		if(!not_P[i]) fac[i]=i;
		else{
			for(int j=2; j<=i; ++j)
				if(!(i%j)) {fac[i]=j; break;}
		}
}

int main()
{
	scanf("%d%d",&n,&m);// printf("%d\n",m);
	if(m<n-1) return puts("Impossible"),0;
	Pre(n);
	for(int i=2; i<=n && sum<m; ++i) A[++sum]=mp(1,i);
	for(int x=1; x<=cnt && sum<m; ++x)
	{
		int i=P[x];
		for(int j=i+1; j<=n && sum<m; )
		{
			int k=std::min(j+fac[i]-1,n+1);//n+1!
			for(int l=j; l<k && sum<m; ++l) A[++sum]=mp(i,l);
			j=k+1;
		}
	}
	for(int i=4; i<=n && sum<m; ++i)
	{
		if(!not_P[i]) continue;
		for(int j=i+1; j<=n && sum<m; )
		{
			int k=std::min(j+fac[i]-1,n+1);
			for(int l=j; l<k && sum<m; ++l)
				if(gcd(i,l)==1) A[++sum]=mp(i,l);
			j=k+1;
		}
	}
	if(sum<m) puts("Impossible");
	else
	{
		puts("Possible");
		for(int i=1; i<=m; ++i)
			printf("%d %d\n",A[i].first,A[i].second);
	}

	return 0;
}
