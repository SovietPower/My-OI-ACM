/*
$Description$
给定n棵"树"，"树"的节点可能"挂着"一个环，保证没有环相交，且与树只有一个公共点。
两人轮流从树上删边，删去一条边后，不与根相连的一部分会被移除。最后无法移动的人输。问谁能赢。
$Solution$
如果没有环，那就是典型的树上删边游戏 
考虑环，没有共用边且与树只有一个交点x，那这是一个从树上某点连出最后又连会这个点的简单环。
删除环上一边后会形成两条链 -> Mult-SG 
若环是一个奇环，那么删去一条边后剩下的两条链奇偶性相同，这个后继状态的异或和(SG值)一定不为1，所以环的SG值为1(后继SG值的mex) 
若环是一个偶环，那么删去一条边后剩下的两条链奇偶性相反，这个后继状态的异或和(SG值)一定不为0，所以环的SG值为0(mex) 
于是可以删去所有偶环，把奇环看做一条边，就成了树上删边游戏的模型了 

树上删边游戏结论：叶子节点的SG值为0；中间节点的SG值为其 所有子节点SG值+1 后的异或和 

注: 访问完节点后不要忘记出栈 
有长度为2的环!
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#define gc() getchar()
const int N=105,M=505;

int t,n,m,Enum,H[N],to[M<<1],nxt[M<<1],sg[N],top,sk[N],vis[N];
//vis=0:未访问过 vis=1:访问过且不是某个环上的点(不考虑树上点) vis=-1:访问过且是某个环上的点 
//对于vis[x]=-1的(环) 不能统计答案!
inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v){
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void DFS(int x,int f)
{
	sk[++top]=x, vis[x]=1, sg[x]=0;
	bool flag=0;
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]==f && !flag) flag=1;//第一次连向父节点 
		else{
			if(vis[to[i]]==1){//仅靠vis和传参的cnt解决不了环。。还是要用栈 
				int cnt=1,now=x;
				while(now!=to[i])
					++cnt, vis[now]=-1, now=sk[--top];
				if(cnt&1) sg[to[i]]^=1;//奇环 
			}
			else if(!vis[to[i]])
			{
				DFS(to[i],x);
				if(~vis[to[i]]) sg[x]^=(sg[to[i]]+1);//环上的不能更新 
			}
		}
	if(~vis[x]) --top;//非环上的 及时出栈 
}

int main()
{
	while(~scanf("%d",&t))//number of sub-trees
	{
		int res=0;
		while(t--)
		{
			memset(vis,0,sizeof vis),
			memset(H,0,sizeof H), Enum=top=0;
			n=read(),m=read();
			for(int u,v,i=1; i<=m; ++i) u=read(),v=read(),AddEdge(u,v);
			DFS(1,0), res^=sg[1];
		}
		puts(res?"Sally":"Harry");
	}
	return 0;
}/*
1 2 2 1 2 1 2
*/
