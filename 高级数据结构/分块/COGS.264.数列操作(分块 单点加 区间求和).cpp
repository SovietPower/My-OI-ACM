#include<cmath>
#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;
const int N=1e5+5;

int n,m,A[N],size,belong[N],sum[N]/*某块的总和*/,tag[N]/*某块的加标记*/;

inline int read()
{
	int now=0,f=1;register char c=getchar();
	for(;!isdigit(c);c=getchar())
	  if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=getchar());
	return now*f;
}

int Query(int l,int r)
{
	int res=0;
	for(int i=l;i<=min(r,belong[l]*size);++i)
		res+=A[i];
	if(belong[l]!=belong[r])
		for(int i=(belong[r]-1)*size+1;i<=r;++i)
			res+=A[i];
	for(int i=belong[l]+1;i<belong[r];++i)
		res+=sum[i];
	return res;
}

int main()
{
	freopen("shulie.in","r",stdin);
	freopen("shulie.out","w",stdout);

	n=read();size=sqrt(n);
	for(int i=1;i<=n;++i)
	{
		belong[i]=(i-1)/size+1;
		A[i]=read(), sum[belong[i]]+=A[i];
	}
	m=read();char opt[6];int a,b;
	while(m--)
	{
		scanf("%s",opt);a=read(),b=read();
		if(opt[0]=='A')
			A[a]+=b, sum[belong[a]]+=b;
		else
			printf("%d\n",Query(a,b));
	}

	return 0;
}
