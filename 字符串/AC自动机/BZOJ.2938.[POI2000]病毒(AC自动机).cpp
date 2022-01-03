/*
1408kb	72ms
$Description$
给n个模式串，问是否存在长度无限的主串，使得任何一个模式串都没有在主串中出现。
$Solution$
先建AC自动机。
假设我们有了一个无限长的安全代码，然后在AC自动机上匹配应该发生什么？
应该是匹配到一个位置失败跳回去，之后要再匹配到这个位置(必须跳回当前链)再失败跳回去。跳回去就是通过fail指针。
Trie树上连上fail指针的边后（其实就是Build时改的son），如果能在这个有向图上找到环，就TAK。
或者，安全代码无限长的话前后要能拼起来，即前后缀相同(同样要跳回当前链)，且保证在这过程中不会匹配任何模式串。
前后缀相同就是通过fail指针跳回去(到当前链)。
建图（就是建AC自动机），DFS一遍就可以。注意如果fail[x]匹配，那么x也匹配。
注意访问过的点就没必要再访问了。
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
const int N=30005;

struct AC_Automaton
{
	int tot,son[N][2],q[N],fail[N];
	bool ed[N],vis[N],ins[N];
	char s[N];

	void Insert()
	{
		scanf("%s",s);
		int l=strlen(s),x=0;
		for(int i=0,v; i<l; ++i)
		{
			if(!son[x][v=s[i]-'0']) son[x][v]=++tot;
			x=son[x][v];
		}
		ed[x]=1;
	}
	void Build()
	{
		int h=0,t=0;
		if(son[0][0]) q[t++]=son[0][0];
		if(son[0][1]) q[t++]=son[0][1];
		while(h<t)
		{
			int x=q[h++];
			ed[x]|=ed[fail[x]];//WA:fail[x]一定比x更早结束路径 fail[x]和x又不一定在同一条路径→_→ 
			for(int i=0; i<2; ++i)
				if(son[x][i]) fail[son[x][i]]=son[fail[x]][i], q[t++]=son[x][i];
				else son[x][i]=son[fail[x]][i];
		}
	}
	void DFS(int x)
	{
		if(ins[x]) puts("TAK"),exit(0);//如果是在当前链上，那也没有终止节点 
		if(vis[x]||ed[x]) return;
		vis[x]=ins[x]=1;
		DFS(son[x][0]), DFS(son[x][1]);
		ins[x]=0;
	}
	void Query()	
	{
		Build(), DFS(0), puts("NIE");
	}
}AC;

int main()
{
	int n;
	for(scanf("%d",&n); n--; AC.Insert());
	AC.Query();
	return 0;
}
