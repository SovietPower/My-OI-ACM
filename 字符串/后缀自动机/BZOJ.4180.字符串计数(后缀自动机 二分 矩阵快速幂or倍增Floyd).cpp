/*
10296kb	384ms
先考虑 假设S确定，使构造S操作次数最小的方案应是：对T建SAM，S在SAM上匹配，如果有S的转移就转移，否则操作数++，会到根节点继续匹配S。即每次操作一定是一次极大匹配。
简单证明：假设S="ABCD"，T有子串"A","AB","CD","BCD"，那么步数最小方案是选"AB"再接上"CD"，而不是提前断开选择"A"+"BCD"，因为后者只会使后面的子串变长，"CD"有可能继续接子串而"BCD"却不能。
那么对于本题，我们要使操作次数多，拼接的子串尽量短，应是选择最短的到达一个不能匹配某字符的位置，即!son[x][c]。那么下次便是从根沿son[root][c]再挑一个结束字符沿最短路径走。
而且字符集大小只有4。令f[i][j]表示从根节点沿字符i出边出发，到达某个没有字符j转移的节点的最短路径。
那么两次操作形成的S长度为l[i][k]=f[i][j]+f[j][k]，于是考虑二分操作次数m，求m次操作后可以得到的S最短的长度是否<=n。可以用矩阵快速幂/倍增Floyd加速转移。
f可以在SAM上求。令g[x][c]表示在x节点到达一个没有c转移的节点的最短距离，则g[x][c]=min{g[son[x]][c]+1}。
最后f[i][j]=g[son[1][i]][j]+1。
另外可以直接转化为图上问题。即设可转移边边权为0，不能转移的连回根节点对应转移点，边权为1。那么就是从根节点出发，走n步，求最大价值。还是缩下没用的边然后二分+倍增Floyd。
不是枚举子节点更新fa[x] 而是枚举son[x]更新x啊mdzz。
操作次数会达到longlong啊。
INF要设为2e18不是1e18，否则minlen==n时直接ans=mid,break不对。。（大概数据问题就这不对） 
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int N=2e5+7;
const LL INF=2e18;//!...

struct Suffix_Automaton
{
	int tot,las,fa[N],son[N][4],len[N],A[N],tm[N],g[N][4],f[4][4];
	LL n;//,g[N][4],f[4][4];
	char s[N>>1];
	struct Matrix
	{
		LL a[4][4];
		Matrix operator *(const Matrix &x)const
		{
			Matrix res;
			for(int i=0; i<4; ++i)
				for(int j=0; j<4; ++j)
				{
					LL tmp=INF;
					for(int k=0; k<4; ++k)
						tmp = std::min(tmp, a[i][k]+x.a[k][j]);
					res.a[i][j]=tmp;
				}
			return res;
		}
	}Base;
	Matrix FP(Matrix x,LL k)
	{
		Matrix t=x;
		for(--k; k; k>>=1, x=x*x)
			if(k&1) t=t*x;
		return t;
	}
	void Insert(int c)
	{
		int p=las,np=++tot; len[las=np]=len[p]+1;
		for(; p&&!son[p][c]; p=fa[p]) son[p][c]=np;
		if(!p) fa[np]=1;
		else
		{
			int q=son[p][c];
			if(len[q]==len[p]+1) fa[np]=q;
			else
			{
				int nq=++tot; len[nq]=len[p]+1;
				memcpy(son[nq],son[q],sizeof son[q]);
				fa[nq]=fa[q], fa[q]=fa[np]=nq;
				for(; son[p][c]==q; p=fa[p]) son[p][c]=nq;
			}
		}
	}
	void Build()
	{
		las=tot=1;
		scanf("%lld%s",&n,s+1); int l=strlen(s+1);
		for(int i=1; i<=l; ++i) Insert(s[i]-'A');
		for(int i=1; i<=tot; ++i) ++tm[len[i]];
		for(int i=1; i<=l; ++i) tm[i]+=tm[i-1];
		for(int i=1; i<=tot; ++i) A[tm[len[i]]--]=i;

		memset(g,0x3f,sizeof g);
		for(int i=1; i<=tot; ++i)
			for(int j=0; j<4; ++j)
				if(!son[i][j]) g[i][j]=0;
		for(int i=tot,x=A[i]; i; x=A[--i])
			for(int j=0,s; j<4; ++j)
				if(s=son[x][j])
					for(int k=0; k<2; ++k)
						g[x][k]=std::min(g[x][k],g[s][k]+1),
						g[x][k+2]=std::min(g[x][k+2],g[s][k+2]+1);//闲的...但还没都展开...
		for(int i=0; i<4; ++i)
			for(int j=0; j<4; ++j)
				Base.a[i][j]=g[son[1][i]][j]+1;
	}
	int Check(LL x)
	{
		Matrix res = FP(Base,x);
		int s=0;
		for(int i=0; i<4; ++i)
			for(int j=0; j<4; ++j)
				if(res.a[i][j]==n) s=1;
				else if(res.a[i][j]<n) return 2;
		return s;//最短长度=n已经最优了 <n则x次一定不够 
	}
	void Solve()
	{
		LL l=1,r=n,mid,ans=1,s;
		while(l<=r)
		{
			if((s=Check(mid=l+r>>1))==1) {ans=mid; break;}//ans=mid, r=mid-1;
			else if(!s) r=mid-1;
			else ans=l=mid+1;
		}
		printf("%lld\n",ans);
	}
}sam;

int main()
{
	sam.Build(), sam.Solve();
	return 0;
}
