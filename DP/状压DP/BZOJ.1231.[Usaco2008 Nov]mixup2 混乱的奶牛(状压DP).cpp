/*
设f[s][i]表示当前集合为s，以第i头奶牛结尾的方案数 
则i是属于s中的，可以通过枚举不在s集合中且满足条件的j，用f[s][i]去更新f[s|(1<<j)][j]
(将牛一个个放入队伍)
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;
const int N=17;

int n,k,a[N];
long long f[(1<<N)+3][N];

inline int read()
{
	int now=0,f=1;register char c=getchar();
	for(;!isdigit(c);c=getchar())
	  if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=getchar());
	return now*f;
}

int main()
{
	n=read(),k=read();
	for(int i=0;i<n;++i)
		a[i]=read();
	for(int i=0;i<n;++i)//注意初始条件!
		f[1<<i][i]=1;//任意一头牛在队伍中自然是一种方案 
	for(int s=1;s<(1<<n);++s)
		for(int i=0;i<n;++i)
			if(s&(1<<i))
				for(int j=0;j<n;++j)
					if(!(s&(1<<j)) && abs(a[j]-a[i])>k)
						f[s|(1<<j)][j]+=f[s][i];
	long long res=0;
	for(int i=0;i<n;++i)
		res+=f[(1<<n)-1][i];
	printf("%lld",res);

	return 0;
}
