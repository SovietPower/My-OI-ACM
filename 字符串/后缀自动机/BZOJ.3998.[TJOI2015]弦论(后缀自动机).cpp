/*
126308kb	5512ms
$Description$
给定字符串S，求其第K小子串。(若T=0，不同位置的相同子串算1个；否则算作多个)
$Solution$
建SAM，处理出对于每个节点，它和它的所有后继包含的子串数量sz[](其后有多少子串)(自叶子向根枚举转移更新即可)，然后在SAM上走。
每次优先看字典序小的边(设会到达v)，若sz[v]<K，则K-=sz[v]，枚举下一条边；否则K-=A[v]，输出这个转移，然后p=v。(是A[v]！是匹配了v节点)
如果T=0，更新时sz[p]的初值为1，A[p]=1；如果T=1，那么更新时sz[p]的初值为|right[p]|，A[p]=|right[p]|。
right的求法：按原串在SAM上走一遍，更新经过点的right，然后自parent树底向上合并给fa的right就可以了。

感觉理解有个误区。。虽然一个节点是会代表多个串，但是。。你从一个状态走来并不是说匹配了这个点代表的所有串。所以就sz[]=1 or |right|。以后再匹配上别的点自然会加。
重新想了下好像没错。。→_→
每个状态s代表的所有串在原串中的出现次数和每次出现的右端点相同。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
const int N=1e6+3;

struct Suffix_Automaton
{
	int T,K,L,las,tot,fa[N],son[N][26],len[N],sz[N],right[N],A[N],tm[N];
	char s[N>>1];
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
		scanf("%s",s), las=tot=1, L=strlen(s);
		for(int i=0; i<L; ++i) Insert(s[i]-'a');
		for(int i=1; i<=tot; ++i) ++tm[len[i]];
		for(int i=1; i<=L; ++i) tm[i]+=tm[i-1];
		for(int i=1; i<=tot; ++i) A[tm[len[i]]--]=i;
	}
	void Query()
	{
		scanf("%d%d",&T,&K);
		if(!T) for(int i=1; i<=tot; ++i) sz[i]=right[i]=1;
		else{
			for(int p=1,i=0; i<L; ++i) ++right[p=son[p][s[i]-'a']];
			for(int i=tot,x=A[i]; i; x=A[--i]) right[fa[x]]+=right[x];//x not i!
			for(int i=1; i<=tot; ++i) sz[i]=right[i];
		}
//		sz[0]=sz[1]=0;
		for(int i=tot,x=A[i]; i; x=A[--i])
			for(int j=0; j<26; ++j) sz[x]+=sz[son[x][j]];
//		sz[1]=0;
		if(K>sz[1]) {printf("-1"); return;}//其实并没有这种情况，要不输出-1就10分了233 
		int p=1;
		while(K>0)
		{
			for(int i=0; i<26; ++i)
				if(son[p][i])//...
					if(sz[son[p][i]]<K) K-=sz[son[p][i]];
					else{
						putchar(i+'a'), K-=right[p=son[p][i]];
						break;
					}
		}
	}
}sam;

int main()
{
	sam.Build(), sam.Query();
	return 0;
}
