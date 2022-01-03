/*
17224kb	528ms
1.求A的最短子串，它不是B的子串。
子串是连续的，对B建SAM，枚举起点，在SAM上找到第一个无法匹配点即可。O(n)用SAM能做吗。。开始想错了。
2.求A的最短子串，它不是B的子序列。
子序列...直接建SAM没啥用。考虑A[i]和上一位A[i-1]，用f[i][j]表示到A[i]匹配到B[j]时连续的A的子串长度，如果A[i]==B[j]，则f[i][j]=max{f[i-1][k]+1}(k<j)。
是取max啊，因为B会尽可能匹配。枚举完B[n]后且max{f[i][k]}!=i(能在A[i]前接一位)才能用max{f[i][k]}+1更新答案。
3.求A的最短子序列，它不是B的子串。
子序列的话就是前面的会对后面的产生影响。因为是B的子串，所以我们还是在SAM上做。
令f[p]表示匹配当SAM上的p点时 A目前最短子序列的长度。对于每个A[i]，枚举点p，若p点A[i]的转移为0，那么可以用当前的f[p]更新答案；否则f[转移点]=min(f[转移点],f[p]+1)。
f[1]=0，其余为INF，只有从根节点开始走才是B的子串。
4.求A的最短子序列，它不是B的子序列。
令son[i][c]表示，当前为A[i]，其后离i最近的满足A[j]==c的j在哪。转移不变，f[j]=min(f[j],f[i]+1)。
也可以建序列自动机...序列自动机理论复杂度是O(n^2)的，因为每插入一个字符，之前没有该转移的点都要与其连边。
为了不是那么暴力地枚举所有点，可以对每个字符维护一个las[c']，即上次插入c'所在位置。插入c时枚举所有c'，从las[c']向上更新连边直到有转移。

注意4.的DP要倒序枚举，避免某位置被A[i]更新多次。感觉3.也需要，但实际不用，不知道为什么。。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
const int N=2007;

int n,m;
char A[N],B[N];
struct Suffix_Automaton
{
	#define S 4007
	int n,tot,las,fa[S],son[S][26],len[S];

	Suffix_Automaton() {tot=las=1;}
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
				fa[nq]=fa[q], fa[np]=fa[q]=nq;
				for(; son[p][c]==q; p=fa[p]) son[p][c]=nq;
			}
		}
	}
	void Build(char *s)
	{
		las=tot=1, n=strlen(s+1);
		for(int i=1; i<=n; ++i) Insert(s[i]-'a');
	}
}sam;

void Solve1()
{
	int ans=N;
	for(int i=1; i<=n; ++i)
		for(int j=i,p=1,now=1; j<=n; ++j)
			if(sam.son[p][A[j]-'a']) ++now, p=sam.son[p][A[j]-'a'];
			else {ans=std::min(ans,now); break;}
	printf("%d\n",ans==N?-1:ans);
}
void Solve2()
{
	static int f[N][N];
	int ans=N;
	for(int i=1; i<=n; ++i)
	{
		int bef=0,mx=0;
		for(int j=1; j<=m; ++j)
		{
			if(A[i]==B[j]) f[i][j]=bef+1;
			mx=std::max(mx,f[i][j]);
			bef=std::max(bef,f[i-1][j]);
		}
		if(mx!=i) ans=std::min(ans,mx+1);//, printf("%d %d\n",i,mx);
	}
	printf("%d\n",ans==N?-1:ans);
}
void Solve3()
{
	static int f[S];//2N!
	memset(f,0x3f,sizeof f);
	f[1]=0; int ans=N;
	for(int i=1; i<=n; ++i)
		for(int j=1,t,tot=sam.tot; j<=tot; ++j)
			if(!(t=sam.son[j][A[i]-'a'])) ans=std::min(ans,f[j]);
			else f[t]=std::min(f[t],f[j]+1);
	printf("%d\n",ans==N?-1:ans+1);
}
void Solve4()
{
	static int f[N],son[N][26],las[26];
	B[0]='a';
	for(int i=m; ~i; --i)
	{
		for(int j=0; j<26; ++j) son[i][j]=las[j];
		las[B[i]-'a']=i;
	}
	memset(f,0x3f,sizeof f);
	f[0]=0/*0与其它都有转移 以0为根节点*/; int ans=N;
	for(int i=1; i<=n; ++i)
		for(int j=m,t; ~j; --j)
			if(!(t=son[j][A[i]-'a'])) ans=std::min(ans,f[j]);
			else f[t]=std::min(f[t],f[j]+1);
	printf("%d\n",ans==N?-1:ans+1);
}

int main()
{
	scanf("%s%s",A+1,B+1), n=strlen(A+1), m=strlen(B+1);
	sam.Build(B);
	Solve1(), Solve2(), Solve3(), Solve4();

	return 0;
}
