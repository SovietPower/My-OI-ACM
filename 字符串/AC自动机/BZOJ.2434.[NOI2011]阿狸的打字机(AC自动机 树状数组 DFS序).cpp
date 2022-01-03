/*
31000kb	484ms
首先不需要存储每个字符串，可以将所有输入的字符依次存进Trie树，对于每个'P',记录该串结束的位置在哪，以及当前节点对应的是第几个串(当前串即根节点当当前节点)；对于'B',只需向上跳一个节点。
然后构建Trie图。fail[]有一个重要意义是: 若fail[y]=x，那么y节点表示的串一定包含x节点表示的串。
于是暴力就可以自底向上查询y串中每个节点的fail[]是否直接或间接指向x 
注意到每个节点的fail[]是仅指向一个节点的，于是可以反向建图fail[x]->x，这样就形成了一个树，叫做fail树 
于是对于每个查询可以去求在x节点的子树中有多少个y串中的节点 
一个节点的子树在DFS序上一定是连续的一段，所以可以直接在fail树上求DFS序然后用树状数组维护 
可以直接在Trie树上DFS，刚访问到一个点整条路径+1，访问结束时-1，这样在求一个串的答案时当前树状数组的值一定是该串上的点所贡献的 
(注意原应是查x在fail树中的子树，所以用fail树得到的DFS序)
每次访问到一个节点 就可以得到以它为y的询问的答案 
对询问按y排序(就是在Trie树上的相对位置)，对每个节点可以存一个询问编号的区间，然后在Trie树上一遍DFS 
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define lb(x) (x)&-(x)
const int N=1e5+5,S=26;

int n,m,cnt,Enum,H[N],nxt[N],to[N],ql[N],qr[N]/*一个点连续的一段询问*/,Time,in[N],out[N],t[N<<1];
int que[N],fail[N],son[N][S],Son[N][S]/*copy一个求后缀数组之前的son*/,ed[N]/*串的结束位置*/,fa[N],lab[N]/*某位置结束的串的标号*/,Ans[N];
char s[N];
struct Ques
{
	int x,y,id;
	bool operator <(const Ques &a)const{
		return y<a.y;
	}
}q[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v){
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
}
void Get_Fail()
{
	int h=0,t=0;
	for(int i=0; i<S; ++i)
		if(son[0][i]) fail[son[0][i]]=0,que[t++]=son[0][i];
	while(h<t)
	{
		int x=que[h++];
		for(int i=0; i<S; ++i)
			if(son[x][i]) fail[son[x][i]]=son[fail[x]][i],que[t++]=son[x][i];
			else son[x][i]=son[fail[x]][i];
	}
}
void pre_DFS(int x)
{
	in[x]=++Time;
	for(int i=H[x]; i; i=nxt[i]) pre_DFS(to[i]);
	out[x]=++Time;
}
inline void Add(int p,int v){
	while(p<=Time) t[p]+=v,p+=lb(p);
}
inline int Query(int p){
	int res=0;
	while(p) res+=t[p],p-=lb(p);
	return res;
}
void DFS(int x)
{
	Add(in[x],1);
	if(lab[x])//当前节点是某串的结尾节点 
		for(int i=ql[lab[x]]; i<=qr[lab[x]]; ++i)
			Ans[q[i].id]=Query(out[ed[q[i].x]])-Query(in[ed[q[i].x]]-1);//减去x往上的值 
	for(int i=0; i<S; ++i)
		if(Son[x][i]) DFS(Son[x][i]);
	Add(in[x],-1);
}

int main()
{
	scanf("%s",s);
	for(int now=0,i=0,l=strlen(s),t; i<l; ++i)
	{
		if(s[i]>='a'&&s[i]<='z')
		{
			if(!son[now][t=s[i]-'a']) Son[now][t]=son[now][t]=++cnt, fa[cnt]=now;
			now=son[now][t];
		}
		else if(s[i]=='P') ed[++n]=now, lab[now]=n;
		else now=fa[now];
	}
	Get_Fail();
	for(int i=1; i<=cnt; ++i) AddEdge(fail[i],i);
	pre_DFS(0);

	m=read();
	for(int i=1; i<=m; ++i) q[i].x=read(),q[i].y=read(),q[i].id=i;
	std::sort(q+1,q+1+m);
	for(int i=1; i<=m; ++i)//得到对于每个点作为y时的询问 
	{
		ql[q[i].y]=i;
		while(i<m && q[i+1].y==q[i].y) ++i;
		qr[q[i].y]=i;
	}
	DFS(0);
	for(int i=1; i<=m; ++i) printf("%d\n",Ans[i]);

	return 0;
}
