/*
1638ms	4700KB
$Description$
Alice和Bob玩游戏。给定$n,f$，表示有$n$行，每行有三个棋子。Alice可以选择一行将其左边一个或两个棋子往右移动$d$步，Bob可以选择一行将其右边一个或两个棋子往左移动$d$步。
要求移动时一个棋子不能跨越另一个棋子，且$d$是质数或两个质数的乘积，且$d\neq f$。求谁能赢。
$n\leq10^5,\ 坐标绝对值\leq10^5$。
$Solution$
右移一个棋子就是缩小第二三两个棋子之间的距离，右移两个棋子就是缩小一二两个棋子之间的距离。设三个棋子位置为$a,b,c$，每一行实际就是两个棋子数为$c-b-1,b-a-1$的$nim$游戏。
如果能算出棋子数为$x$的游戏的$SG$函数，将$2n$个游戏的$sg$值全异或起来即可。考虑如何算，显然有$sg(x)=\mathbb{mex}_{d\in P}\{sg(x-d)\}$，但是复杂度是$n^2$的。
打个表发现，$sg$值最大不会超过$100$（我也不知道怎么能得出的）。我们开$100$个$bitset\ A[i]$，分别表示每个数字是否存在$sg$值为$i$的后继。再预处理$d\in P$的$bitset\ S$。这样从小到大求$sg(i)$时，就`for`一遍看它不存在哪个$sg$值的后继；然后$A[sg(i)]|=S<<i$即可（更新上能到$i$的位置）。
复杂度$O(\frac{n^2}{w})$。
*/
#include <cstdio>
#include <cctype>
#include <bitset>
#include <algorithm>
#define gc() getchar()
#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e5+1,M=102;

int sg[N];
std::bitset<N> S,A[M];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
void Init()
{
	static int P[N],mn[N];
	int cnt=0;
	for(int i=2; i<N; ++i)
	{
		if(!mn[i]) P[++cnt]=i;
		for(int j=1; j<=cnt&&i*P[j]<N; ++j)
		{
			mn[i*P[j]]=i;
			if(!(i%P[j])) break;
		}
	}
	for(int i=2; i<N; ++i) if(!mn[mn[i]]) S[i]=1;
}

int main()
{
	int n=read(); Init(), S[read()]=0;
	for(int i=0; i<N; ++i)
	{
		while(A[sg[i]][i]) ++sg[i];
		A[sg[i]]|=S<<i;
	}
	int ans=0;
	for(int a,b,c; n--; ) a=read(),b=read(),c=read(),ans^=sg[b-a-1]^sg[c-b-1]; 
	puts(ans?"Alice\nBob":"Bob\nAlice");

	return 0;
}
