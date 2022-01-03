/*
写了个数位DP的常规记忆化，非递推。。
区间合法即区间中有两个$3$或$6$，或有一个$0$或$9$。
如果按平时DFS的数位DP写法来写，记录前两个$3,6$、前一个$0,9$ 出现的位置$p30,p31,p$，以及当前枚举到哪个区间了即可。转移就枚举选$3,6$还是$0,9$还是其它数。
可以发现$p30,p31,p$的状态数是$O(n^3)$的，太大了，而数位DP的优化在于压缩状态记忆化，所以考虑压缩一下状态。
因为记录$p$是为了处理限制的，容易发现对限制区间排序后，设当前要判断的区间是$[l,r]$，若$p<l$可以给$p$一个统一的值$l-1$；否则令$p=下一个询问的l-1$。
这样状态数就少很多了。虽然不知道复杂度多少但跑得很快。
包含其它区间的大区间显然是没用的，可以删一下。
*/
#include <bits/stdc++.h>
#define gc() getchar()
#define mod 1000000007
typedef long long LL;
const int N=1e3+7;

int n,m,bit[N],pw[N];
struct Node
{
	int l,r;
	bool operator <(const Node &x)const
	{
		return r==x.r?l>x.l:r<x.r;
	}
}A[N],B[N];
struct Node2
{
	int b,p0,p1,p2;
	bool operator <(const Node2 &x)const
	{
		return b!=x.b?b<x.b:p0!=x.p0?p0<x.p0:p1!=x.p1?p1<x.p1:p2<x.p2;
	}
};
std::map<Node2,int> f;

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
bool OK(int p30,int p31,int p,int now)
{
	return (p>=A[now].l&&p<=A[now].r)||(p30>=A[now].l&&p31<=A[now].r);
}
int DFS(int bit,int p30,int p31,int p,int now)
{
	while(now<=m && OK(p30,p31,p,now)) ++now;
	p30=std::max(p30,A[now].l-1), p31=std::max(p31,A[now].l-1), p=std::max(p,A[now].l-1);
	if(p31>=A[now].l) p31=std::max(p31,A[now+1].l-1);
	Node2 tmp=(Node2){bit,p30,p31,p};
	if(f.count(tmp)) return f[tmp];
	if(now>m) return pw[n-bit+1];
	if(bit>n) return 0;
	if(A[now].r<bit) return 0;
	if(A[now].l>bit) return 1ll*pw[A[now].l-bit]*DFS(A[now].l,p30,p31,p,now)%mod;//
	LL res=0;
	res+=2ll*DFS(bit+1,p30,p31,bit,now);//0 9
	res+=2ll*DFS(bit+1,p31,bit,p,now);//3 6
	res+=6ll*DFS(bit+1,p30,p31,p,now);
	res%=mod, f[tmp]=res;
	return res;
}

int main()
{
	pw[0]=1;
	for(int i=1; i<N; ++i) pw[i]=1ll*pw[i-1]*10%mod;
	while(~scanf("%d%d",&n,&m))
	{
		for(int i=1,l; i<=m; ++i) l=read(),B[i]=(Node){l,read()};
		std::sort(B+1,B+1+m);
		int cnt=1; A[1]=B[1];
		for(int i=2; i<=m; ++i)
			if(A[cnt].l>=B[i].l && A[cnt].r<=B[i].r) ;
			else A[++cnt]=B[i];

		m=cnt, f.clear(), A[cnt+1].l=n;
		int res=DFS(1,0,0,0,1);
		printf("%d\n",res);
	}

	return 0;
}/*
1000 5
12 34
25 123
99 345
311 556
878 999

*/
