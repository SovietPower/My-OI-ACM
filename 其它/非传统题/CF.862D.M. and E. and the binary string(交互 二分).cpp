/*
$Description$
有一个长为$n$的二进制串，保证$01$都存在。你可以询问不超过$15$次，每次询问你给出一个长为$n$的二进制串，交互库会返回你的串和目标串的不同位的数目。求任意一个$0$和$1$的位置。
$n\leq 1000$。
$Solution$
通过$0...$和$1...$就可以判断出第一个数是什么。然后二分，对每个区间判断是否全为$0/1$，就可以找到另一个了。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=1005;

int n;
char s[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int Query()
{
	putchar('?'), puts(s); fflush(stdout);
	return read();
//	int t; scanf("%d",&t); return t;
}
inline void Fill(int l,int r,const char c)
{
	for(int i=l; i<=r; ++i) s[i]=c;
}
int Solve(const char q,const char c)
{
	for(int i=1; i<=n; ++i) s[i]=c;
	int l=2,r=n,mid,bef=Query(),tmp;
	while(l<r)
	{
		Fill(l,mid=l+r>>1,q), tmp=Query(), Fill(l,mid,c);
		if(std::abs(bef-tmp)==mid-l+1 && bef>tmp) return l;//注意等于区间长度时差值可能是不变的 
		if(std::abs(bef-tmp)<mid-l+1) r=mid;
		else l=mid+1;
	}
	return l;
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) s[i]='0'; s[0]=' ', s[n+1]='\0';
	int t0=Query(); s[1]='1'; int t1=Query();
	int ans0, ans1;
	if(t0<t1) ans0=1, ans1=Solve('1','0');
	else ans1=1, ans0=Solve('0','1');
	printf("! %d %d\n",ans0,ans1);// fflush(stdout);

	return 0;
}
