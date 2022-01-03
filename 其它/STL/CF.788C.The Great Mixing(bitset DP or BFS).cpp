/*
31ms	5744KB
$Description$
有k种饮料，浓度Ai给出，求用最少的体积配成n/1000浓度的饮料。
$Solution$
根据题意有方程 (A1*x1+A2*x2+...+An*xn)/[(x1+x2+...+xn)*1000] = x/1000 
xi表示Ai选多少升(0<=xi).1000可以约掉.
这样带着带着选与不选不好考虑(我为什么会这么考虑。。太naive了) 
ai表示选了ai浓度1L，则(a1+a2+...+am) = m*n 
那么 ∑(ai-n) = 0 , -1000 <= ai-n <= 1000 
于是1.可以以0为起点BFS，把每个(ai-n)作为一条边，直到(用最少的步数)再走到0 
或是2.考虑DP，用f[i][sum]表示用iL是否得到sum 
于是朴素的DP：
for(i=1; i<=1000; ++i)//可以证明最多只需要1000L 
	for(sum=-1000; sum<=1000; ++sum)//需要对sum加个偏移量 
		for(j=1; j<=k; ++j)
			if(-1000<=sum-(a[j]-n)<=1000)
				f[i][sum]|=f[i-1][sum-(a[j]-n)]
这仍然是O(n^3)的 
可以把sum的一层循环用bitset压掉(f[i-1]左移a[j]位后再右移n位)。这个复杂度？O((n^3)/64)？
上面的证明(最多需要1kL): 假设要配x浓度，有a>x的浓度、b<x的浓度，有u(a-x)+v(b-x)=0 
u=x-b, v=a-x时，就可以配成x，此时u+v = a-b <= 1000 
ai只需考虑1000以内的即可 
被卡T了。。不得不加个特判 
*/
#include <cstdio>
#include <cctype>
#include <bitset>
#define gc() getchar()
const int N=1e6+5;

int n,k,cnt,A[N];
bool vis[1005];
std::bitset<2018> f[2];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read(),k=read();
	for(int tmp,i=1; i<=k; ++i)
		if((tmp=read())<=1000) A[++cnt]=tmp,vis[tmp]=1;
	f[1][1000]=1;
	if(cnt<1000)
		for(int now=1,las,i=1; i<=1000; ++i)
		{
			las=now, now^=1;
			f[now].reset();
			for(int j=1; j<=cnt; ++j)
				f[now]|=(f[las]<<A[j])>>n;
			if(f[now][1000]) {printf("%d",i); return 0;}
		}
	else
		for(int now=1,las,i=1; i<=1000; ++i)
		{
			las=now, now^=1;
			f[now].reset();
			for(int j=0; j<=1000; ++j)
				if(vis[j]) f[now]|=(f[las]<<j)>>n;
			if(f[now][1000]) {printf("%d",i); return 0;}
		}
	printf("-1");

	return 0;
}
