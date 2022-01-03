/*
672ms	24.97M

*/
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
#include <unordered_map>
#define seed 193
#define gc() getchar()
#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
typedef unsigned long long ull;
const int N=1e5+5,M=N<<1;

int H[N],nxt[N],L[N],R[N],A[M],mxdep[N];
ull pw[M],hs[M];
std::vector<int> vec[N];
std::unordered_map<ull,bool> vis[18];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int u,int v)
{
	nxt[v]=H[u], H[u]=v;
}
inline ull Hash(int l,int r)
{
	return hs[r]-pw[r-l+1]*hs[l-1];
}
void DFS1(int x)
{
	static int Index=0;
	A[L[x]=++Index]=97; int mx=0;
	for(int v=H[x]; v; v=nxt[v]) DFS1(v), mx=std::max(mx,mxdep[v]);
	A[R[x]=++Index]=131, mxdep[x]=mx+1;
}
bool DFS2(int x,int k,std::unordered_map<ull,bool> &vis)
{
	static int top,sk[N];
	sk[++top]=x, std::vector<int>().swap(vec[x]);
	if(top>k+1) vec[sk[top-k-1]].push_back(x);
	for(int v=H[x]; v; v=nxt[v])
		if(DFS2(v,k,vis)) return --top,1;
	--top;
	if(mxdep[x]<=k) return 0;
	int l=L[x],r; ull val=0;
	for(auto v:vec[x]) r=L[v]-1, val=val*pw[r-l+1]+Hash(l,r), l=R[v]+1;
	r=R[x], val=val*pw[r-l+1]+Hash(l,r);
	return vis.count(val)?1:(vis[val]=1,0);
}

int main()
{
	const int n=read(),n2=n<<1;
	for(int i=1; i<=n; ++i)
		for(int t=read(); t--; AE(i,read()));//reverse
	DFS1(1), pw[0]=1;
	for(int i=1; i<=n2; ++i) pw[i]=pw[i-1]*seed, hs[i]=hs[i-1]*seed+A[i];
	int l=1,r=n-1,mid,ans=0,t=0;
	while(l<=r) DFS2(1,mid=l+r>>1,vis[t++])?(ans=mid,l=mid+1):r=mid-1;
	printf("%d\n",ans);

	return 0;
}
