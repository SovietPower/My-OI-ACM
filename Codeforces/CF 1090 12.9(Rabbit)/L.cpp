#include <set>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define pc putchar
#define gc() getchar()
typedef long long LL;
const int N=1e5;


inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	int tot=read(),n=read(),a=read(),b=read(),k=read();
	LL ans=1ll*n/(2*k)*(a+b);
	if(ans>=tot) return printf("%d\n",tot),0;
	n=n%(2*k);
	if(n<k) return printf("%I64d\n",ans),0;
//	printf("n:%d\n",n);
//	if(k&1)
	{
		if(a<=b)
		{
			ans+=a;
//			if((n-k+1)/2>=k-k/2) ans+=b-a;
			int res=k-k/2;
			if(n-k>=res) ans+=std::min(a,b-a);
		}
		else
		{
			ans+=b;
//			printf("%d %d\n",(n-k)/2,k-(k+1)/2);
//			if((n-k)/2>=k-(k+1)/2) ans+=a-b;
			if(n==2*k-1) ans+=a-b;
			else
			{
				int res=k-(k+1)/2;
				if(n-k>=res) ans+=std::min(a-b,b);
			}
		}
	}
	printf("%I64d\n",std::min(ans,(LL)tot));

	return 0;
}
