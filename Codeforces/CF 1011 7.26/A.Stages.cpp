#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1005;

int n,K,A[N];
char s[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	n=read(), K=read(); scanf("%s",s+1);
	for(int i=1; i<=n; ++i) A[i]=s[i]-'a'+1;
	std::sort(A+1,A+1+n);
	int res=0, num=0;
	for(int i=1,now=-1; i<=n&&num<K; ++i)
		if(A[i]>now+1) ++num, res+=A[i], now=A[i];
	if(num>=K) printf("%d\n",res);
	else puts("-1");

	return 0;
}
