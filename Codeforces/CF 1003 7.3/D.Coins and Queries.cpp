#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=2e5+5, INF=0x7fffffff;

int n,Q,A[N],tot[999],num[999];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int Count(int x){
	for(int i=0; i<31; ++i) if(x&(1<<i)) return i;
}
int Query()
{//写的好像麻烦了 当时非常zz 
	memcpy(num,tot,sizeof tot);
	int B=read(),ans=0;
	for(int i=30; ~i; --i)
	{
		if(!(B&(1<<i))) continue;
		if(num[i]) ++ans;
		else
		{
			int need=1<<i;
			for(int j=i-1; ~j&&need; --j)
			{
				if(!num[j]) continue;
				int v=std::min(num[j],need>>j);//need/(1<<j);//not ceil!
				ans+=v, need-=v*(1<<j), num[j]-=v;
			}
			if(need) return -1;
		}
	}
	return ans;
}

int main()
{
	n=read(), Q=read();
	for(int i=1; i<=n; ++i) ++tot[Count(read())];
	while(Q--) printf("%d\n",Query());

	return 0;
}
