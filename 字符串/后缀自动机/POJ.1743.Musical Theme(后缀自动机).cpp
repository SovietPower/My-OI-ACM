/*
29504K	594MS
主要目标：求长度至少为5的 重复出现过的不重叠子序列。（其余见之前写的）
一个节点出现位置终点的集合(right)为其所有儿子节点right集合的并。而且这个点所代表的串一定在其子节点代表的串中出现过。
于是从底向上更新，我们可以得到每个点代表的串中 位置最靠左的右端点L和最靠右的右端点R。
如果R[i]-L[i]>=len[i]，说明这个点代表的最长串重复出现且不重叠，可以用len[i]更新ans。实际上min(R[i]-L[i],len[i])即为每个点合法的答案。（后者写不写都对啊。。是因为最终答案的关系？）
清空son[]、tm[]啊！
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=4e4+5,MAX=88;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
struct Suffix_Automaton
{
	int n,a[N],tot,las,fa[N],son[N][180],len[N],L[N],R[N],tm[N],A[N];

	void Insert(int c)
	{
		int np=++tot,p=las; len[las=np]=len[p]+1;
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
		memset(tm,0,sizeof tm), memset(son,0,sizeof son);//!!!

		for(int i=1; i<=n; ++i) a[i]=read();
		--n;
		for(int i=1; i<=n; ++i) a[i]=a[i+1]-a[i]+MAX;

		tot=las=1, len[1]=0;
		for(int i=1; i<=n; ++i) Insert(a[i]);
		for(int i=1; i<=tot; ++i) ++tm[len[i]];
		for(int i=1; i<=n; ++i) tm[i]+=tm[i-1];
		for(int i=1; i<=tot; ++i) A[tm[len[i]]--]=i;
	}
	void Query()
	{
		memset(R,0,sizeof R), memset(L,0x3f,sizeof L);
		for(int i=1,p=1; i<=n; ++i)
			p=son[p][a[i]], L[p]=R[p]=i;//a[]与A[]。。。
		for(int i=tot,x=A[i]; i; x=A[--i])
			L[fa[x]]=std::min(L[fa[x]],L[x]), R[fa[x]]=std::max(R[fa[x]],R[x]);
		int ans=0;
		for(int i=1; i<=tot; ++i)
			ans=std::max(ans,std::min(R[i]-L[i],len[i]));
		printf("%d\n",ans<4?0:ans+1);
	}
}sam;

int main()
{
	while(sam.n=read(),sam.n) sam.Build(), sam.Query();
	return 0;
}
