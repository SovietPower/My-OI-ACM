/*
836kb	164ms
操作序列的顺序显然是无关的，所以只需按特定顺序求出一个长度为$l$的操作序列，它对答案的贡献为$l!$。
我们从小到大枚举所有选择。若当前为第$i$个，如果有一段长度为$2^i$不是+1+1这样递增的，那么需要把它分为两段长度为$2^{i-1}$的然后交换(在此之前满足所有长度更小的如$2^{i-1}$递增)。
如果有两段长度为$2^i$的非每次加1的递增段，会有四种情况，如$3,8,\cdots,7,4$(也可能无解:$8,3,\cdots,7,4$)，即把这两段分成四段长度为$2^{i-1}$的，然后枚举四种情况(只会有两种可行方案吧)交换，如果可行下一层DFS。
如果多于两段，不可能有解。
如果没有，那不能交换，下一层。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=(1<<12)+3;

int n,A[N],fac[15],bit[15];
long long Ans;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
bool Check(int p,int k)
{
	for(int i=p; i<p+k-1; ++i)
		if(A[i]+1!=A[i+1]) return 0;
	return 1;
}
void Swap(int p1,int p2,int k)
{
	for(int i=0; i<k; ++i)
		std::swap(A[p1+i],A[p2+i]);
}
void DFS(int p,int cnt)
{
	if(p>n) Ans+=fac[cnt];
	else
	{
		int p1=0,p2=0;
		for(int i=1; i<=bit[n]; i+=bit[p])
			if(!Check(i,bit[p])){
				if(!p1) p1=i;
				else if(!p2) p2=i;
				else return;
			}
		if(!p1&&!p2) DFS(p+1,cnt);
		else if(p1&&!p2)
			Swap(p1,p1+bit[p-1],bit[p-1]), DFS(p+1,cnt+1), Swap(p1,p1+bit[p-1],bit[p-1]);
		else
		{
			for(int i=0; i<=1; ++i)
				for(int j=0; j<=1; ++j)
				{
					Swap(p1+i*bit[p-1],p2+j*bit[p-1],bit[p-1]);
					if(Check(p1,bit[p])&&Check(p2,bit[p]))//两个位置！
					{
						DFS(p+1,cnt+1);
						Swap(p1+i*bit[p-1],p2+j*bit[p-1],bit[p-1]);
						break;
					}
					Swap(p1+i*bit[p-1],p2+j*bit[p-1],bit[p-1]);
				}
		}
	}
}

int main()
{
	fac[0]=fac[1]=1;
	for(int i=2; i<=12; ++i) fac[i]=fac[i-1]*i;
	for(int i=0; i<=12; ++i) bit[i]=1<<i;
	n=read();
	for(int i=1; i<=bit[n]; ++i) A[i]=read();
	DFS(1,0);
	printf("%lld",Ans);

	return 0;
}
