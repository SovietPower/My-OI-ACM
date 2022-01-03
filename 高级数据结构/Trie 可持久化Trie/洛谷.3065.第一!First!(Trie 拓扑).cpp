/*
给出n个字符串，问重定义英文字符的顺序(即字典序)，有哪些单词可能排在第一 

一个单词想要排在第一，首先是没有其它字符串是它的前缀。那么建一棵Trie树 
其次，它字符的优先级要比和它有着相同前缀的要高。
也就是说，对于同一个父节点下，这个儿子的优先级要比其它兄弟要高 
那么我们就连一条边，表示优先级高低。最后拓扑，如果有环，则不行 
判断一个字符串只需在Trie树上边走边加边即可。如果它有子串，显然不行。 

发现对于拓扑理解有问题...
对于本题一对(u,v)只能建一条边，因为是大小关系 
最后入队过的某个元素一定不会在入队 

小数组尤其是要经常memset的一定不要开大！

c_str()是Borland封装的String类中的一个函数，它返回当前字符串的首字符地址，类型为constchar* 
*/
#include<cstdio>
#include<cstring>
#include<iostream>
const int N=3e5+5,M=3e4+5,S=27;

int n,tot,dgr[S],son[N][S],q[S],Enum,H[S],to[S*S],nxt[S*S];
bool vis[N],mrk[M],lnk[S][S];
std::string str[M];
char tmp[10005];

inline void AddEdge(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
}
//void Insert(char *s)
void Insert(std::string s)//faster
//直接用全局的tmp略快一点 
{
//	int l=strlen(s),id,u=0;
	int l=s.size(),id,u=0;
	for(int i=0;i<l;++i)
	{
		id=s[i]-'a';
		if(!son[u][id]) son[u][id]=++tot;
		u=son[u][id];
	}
	vis[u]=1;
}
//bool Solve(std::string s)
bool Solve(int p)//faster
{
	int l=str[p].size(),id,u=0;
	for(int i=0;i<l;++i)
	{
		if(vis[u]) return 0;
		id=str[p][i]-'a';
		for(int j=0;j<26;++j)
			if(son[u][j] && id!=j && !lnk[id][j])
				++dgr[j], lnk[id][j]=1, AddEdge(id,j);
		u=son[u][id];
	}
	return 1;
}
bool TopoSort()
{
	int h=0,t=0,x;
	for(int i=0;i<26;++i)
		if(!dgr[i]) q[t++]=i;
	while(h<t)
	{
		x=q[h++];
		for(int i=H[x];i;i=nxt[i])
			if(!--dgr[to[i]]) q[t++]=to[i];
	}
	for(int i=0;i<26;++i)
		if(dgr[i]) return 0;
	return 1;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("3065.in","r",stdin);
//	freopen("3065.out","w",stdout);
#endif

	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%s",tmp), str[i]=tmp, Insert(str[i]);
	int res=0;
	for(int i=1;i<=n;++i)
	{
		Enum=0;
		memset(H,0,sizeof H);
		memset(lnk,0,sizeof lnk);
		memset(dgr,0,sizeof dgr);
		if(!Solve(i)) continue;
		if(TopoSort()) mrk[i]=1,++res;
	}
	printf("%d\n",res);
	for(int i=1;i<=n;++i)
		if(mrk[i]) printf("%s\n",str[i].c_str());

	return 0;
}
