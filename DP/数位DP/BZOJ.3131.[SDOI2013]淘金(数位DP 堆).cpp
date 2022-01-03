/*
12124kb	740ms
40pts:
行列是独立的！即同在第i行的元素一定都会加到f(i)行，它们对所有列位置的贡献同其它行一样是固定的，只是加的行不同而已。列同理。而且行列的贡献是相同的。
所以求出(一维下)有多少个数能转移到某个位置i。找出两两相乘(二维)最大的K个。-> 这40pts我也不会写啊QAQ 
其实是用堆 然后每个节点维护两个指针，拿一个就放两个？并不，这样在x==y时会有重。(其实也有办法 大概要判重之类？)
如果x是初始的s_x，则不断扩展 push(x,y+1)；如果x!=y，则push(x+1,y)(维护一个有序数对，感觉好6啊。。)
而且在x!=y时加两遍，因为行列是可以在反过来的！
(也可以先push进n个去再扩展吧。。)
100pts:
n很大无法直接算出某个位置的val[].
在n的范围内f(x)的种类只有不是很多种(大概不到20000?)，且因子只会有2.3.5.7，可以通过数位DP算出y=2^i*3^j*5^k*7^l时有多少个x的数位乘积=y(x<=n).
dp[len][0/1][i][j][k][l]表示当前是n的第len位，前面是否达到了上界，以及y的因子个数分别为i,j,k,l时的x个数。
最后统计所有y的val[]。
注意dp的细节: 可以有前导0，除了最高位都要计算前导0的贡献，即dp[now][0][0][0][0][0]++(不卡上界)；最高位初始化时是dp[now][1][0][0][0][0]=1(上界)。
(并没有直接写代码。。借鉴下xxy博客了)
另外这个取模是在取最多的情况下算出后取模！val[]运算过程中不能取模。(是这样吧)
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define mod (1000000007)
typedef long long LL;
const int N=1e5+7;

int K,cnt,f[11][5]/*多一位数影响的数值*/,A[20];
//LL n,val[N],dp[2][2][40][26][18][15];
LL n,val[N],dp[2][2][41][27][19][16];
struct Node
{
	int x,y; LL v;
	Node(int _x,int _y): x(_x),y(_y),v(val[x]*val[y]) {}
	bool operator <(const Node &a)const{
		return v<a.v;//val升序 
	}
};
std::priority_queue<Node> q;

inline bool cmp(const int &a,const int &b){
	return a>b;
}
inline void Pre()
{//0:2 1:3 2:5 3:7
	f[2][0]=1, f[4][0]=2, f[6][0]=1, f[8][0]=3,
	f[3][1]=1, f[6][1]=1, f[9][1]=2,
	f[5][2]=1, f[7][3]=1;
}
inline LL FP(LL x,int k)
{
	LL t=1;
	for(; k; k>>=1,x=x*x)
		if(k&1) t=t*x;
	return t;
}
void DP()
{//2:40 3:26 5:18 7:15
	Pre();
	LL t=n; int len=0;
	while(t) A[len++]=t%10,t/=10;//我一定是sb了。。下标从0开始还用A[0]做长度 
	std::reverse(A,A+len);
	int now=0,nxt=1;
	for(int p=0; p<len; ++p,std::swap(now,nxt))//神tm还拿l做变量。。
	{
		
		if(!p) dp[now][1][0][0][0][0]=1;
		else ++dp[now][0][0][0][0][0];
		memset(dp[nxt],0,sizeof dp[nxt]);
		for(int s=0; s<=1; ++s)
			for(int i=0; i<=40; ++i)
				for(int j=0; j<=26; ++j)
					for(int k=0; k<=18; ++k)
						for(int l=0; l<=15; ++l)
							if(dp[now][s][i][j][k][l])//怎么这么。。
								for(int w=1,lim=s?A[p]:9; w<=lim; ++w)//不能取模  //另外不计算0！
									dp[nxt][s&&w==lim][i+f[w][0]][j+f[w][1]][k+f[w][2]][l+f[w][3]]+=dp[now][s][i][j][k][l];
	}
	LL tmp2=1,sum;
	for(int i=0; i<=40; ++i)
	{
		LL tmp3=tmp2;
		for(int j=0; j<=26; ++j)
		{
			LL tmp5=tmp3;
			for(int k=0; k<=18; ++k)
			{
				LL tmp7=tmp5;
				for(int l=0; l<=15; ++l)
				{
					if(sum=(dp[now][0][i][j][k][l]+dp[now][1][i][j][k][l])%mod) val[++cnt]=sum;
					if((tmp7*=7)>n) break;
				}
				if((tmp5*=5)>n) break;
			}
			if((tmp3*=3)>n) break;
		}
		if((tmp2<<=1)>n) break;
	}
}

int main()
{
	scanf("%lld%d",&n,&K);
	DP();
	std::sort(val+1,val+1+cnt,cmp);
	LL res=0;
	q.push(Node(1,1));
	while(!q.empty())
	{
		Node rt=q.top(); q.pop();
		(res+=rt.v)%=mod;
		if(!--K) break;
		if(rt.x!=rt.y){
			(res+=rt.v)%=mod;
			if(!--K) break;
			q.push(Node(rt.x+1,rt.y));
		}
		if(rt.x==1) q.push(Node(rt.x,rt.y+1));
	}
	printf("%lld",res);

	return 0;
}
