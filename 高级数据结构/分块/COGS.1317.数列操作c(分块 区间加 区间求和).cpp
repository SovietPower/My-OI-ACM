#include<cmath>
#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;
const int N=1e5+5;
#define LL long long

int n,belong[N],size;
LL A[N],sum[N],tag[N];

inline LL read()
{
	LL now=0,f=1;register char c=getchar();
	for(;!isdigit(c);c=getchar())
	  if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=getchar());
	return now*f;
}

void Add(int l,int r,LL v)
{
	for(int i=l;i<=min(r,belong[l]*size);++i)
		A[i]+=v, sum[belong[i]]+=v;
	if(belong[l]!=belong[r])
		for(int i=(belong[r]-1)*size+1;i<=r;++i)
			A[i]+=v, sum[belong[i]]+=v;
	for(int i=belong[l]+1;i<belong[r];++i)
		tag[i]+=v;
}
LL Query(int l,int r)
{
	LL res=0;
	for(int i=l;i<=min(r,belong[l]*size);++i)
		res+=A[i]+tag[belong[i]];
	if(belong[l]!=belong[r])
		for(int i=(belong[r]-1)*size+1;i<=r;++i)
			res+=A[i]+tag[belong[i]];
	for(int i=belong[l]+1;i<belong[r];++i)
		res+=sum[i]+tag[i]*size;
	return res;
}

int main()
{
	freopen("shuliec.in","r",stdin);
	freopen("shuliec.out","w",stdout);

	n=read();size=sqrt(n);
	for(int i=1;i<=n;++i)
		belong[i]=(i-1)/size+1, A[i]=read(), sum[belong[i]]+=A[i];
	int m=read(),l,r;LL v;char opt[6];
	while(m--)
	{
		scanf("%s",opt);l=read(),r=read();
		if(opt[0]=='A')
			v=read(), Add(l,r,v);
		else
			printf("%lld\n",Query(l,r));
	}
	
	return 0;
}
