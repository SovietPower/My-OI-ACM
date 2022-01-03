/*
828kb	396ms
枚举对子，枚举每张牌，先出完它的刻子，剩下的出顺子。$O(n^3)$.
不是这样 -> 出完所有刻子，最后出顺子。(日常zz)
优先仨相同的，然后顺子，有一次且一定要用一次机会补顺子的空位，即把刻子换成对子。这样好像是$O(n^2)$.
不写$O(n^2)$的了，特判之类大概非常麻烦。。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#define gc() getchar()
const int N=407;

int n,m,tot,tmp[N],num[N],Ans[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
bool Check()
{
	for(int i=1; i<=n+2; ++i)//处理完前面的 才处理这张出刻子！
		if((num[i]%=3)>0) num[i+1]-=num[i], num[i+2]-=num[i], num[i]=0;//直接给减掉就行啊，判什么 
		else if(num[i]<0) return 0;
	return 1;
}

int main()
{
	n=read(),m=read(),tot=3*m+1;
	for(int i=1; i<=tot; ++i) ++tmp[read()];
	int cnt=0;
	for(int i=1; i<=n; ++i)
	{
		++tmp[i];
		for(int j=1; j<=n; ++j)
			if(tmp[j]>=2)
			{
				tmp[j]-=2, memcpy(num,tmp,sizeof num), tmp[j]+=2;
				if(Check()) {Ans[++cnt]=i; break;}
			}
		--tmp[i];
	}
	if(cnt) for(int i=1; i<=cnt; ++i) printf("%d ",Ans[i]);
	else puts("NO");

	return 0;
}
