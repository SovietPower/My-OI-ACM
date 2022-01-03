/*
$Description$
一对新人请n-1对夫妻吃饭，人们坐在一张桌子的两侧，每一对互为夫妻关系的人必须坐在桌子的两侧。而且有些人两两之间会存在“通奸”关系，通奸关系不仅在男女之间，同性之间也有。新娘对面不可以座有通奸关系的人。判断是否存在可行的排座方案，存在的话输出和新娘同一排的人。
$Solution$
每对夫妇只能有一个坐在新娘这一边，这正符合2-SAT初始状态 
若以0表示新娘，以1表示新郎 
那么对于有关系的u,v(i'表示在新娘一侧)，应该连边u->v',v->u'，而不是用i'表示新娘对面(新郎一侧)，而连边u'->v,v'->u 
因为如果新郎与v有关系，就会连边1(u')->v'，这成了同在新郎一侧了；但若新娘与v有关系，连边0(u)->v'(同在新娘一侧)是符合连边规则的 
有矛盾的情况是有关系的两人同在新娘对面，所以2-SAT求出的可行解是新娘对面的 
新娘与新郎要坐在两侧，连边0->1，表示不能选0，一定选1，这样选出来的解就是新娘对面了 
每对夫妇就是对立的，也不分性别。。所以随便一个表示i，另一个就表示i' 
输出方案时只要输出与新娘染色相同的就可以了 
是bel[i]还是i不要混 注意与新郎新娘标号统一 
总是有点想不明白。。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=5005,M=1e5+5;

int n,m,Enum,H[N],nxt[M],to[M],sk[N],top,cnt,bel[N],low[N],dfn[N],id;
int num,head[N],snxt[N],sto[N],conf[N],dgr[N]/*indgree*/,col[N],q[N];//conflict
bool ins[N];

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
inline void AddEdge2(int u,int v){
	++dgr[v], sto[++num]=v, snxt[num]=head[u], head[u]=num;
}
void Tarjan(int x)
{
	dfn[x]=low[x]=++id, sk[++top]=x, ins[x]=1;
	for(int v,i=H[x]; i; i=nxt[i])
		if(!dfn[v=to[i]]) Tarjan(v), low[x]=std::min(low[x],low[v]);
		else if(ins[v]) low[x]=std::min(low[x],dfn[v]);
	if(low[x]==dfn[x])
	{
		++cnt;
		do{
			bel[sk[top]]=cnt, ins[sk[top--]]=0;
		}while(x!=sk[top+1]);
	}
}
bool Topo()
{
	for(int i=0; i<n<<1; i+=2)
		if(bel[i]==bel[i^1]) return 0;
		else conf[bel[i]]=bel[i^1],conf[bel[i^1]]=bel[i];
	num=0, memset(head,0,sizeof head),
	memset(col,0,sizeof col), memset(dgr,0,sizeof dgr);
	for(int x=0; x<n<<1; ++x)
		for(int i=H[x]; i; i=nxt[i])
			if(bel[x]!=bel[to[i]]) AddEdge2(bel[to[i]],bel[x]);
	int h=0,t=0;
	for(int i=1; i<=cnt; ++i)
		if(!dgr[i]) q[t++]=i;
	while(h<t)
	{
		int x=q[h++];
		if(!col[x]) col[x]=1,col[conf[x]]=2;
		for(int i=head[x]; i; i=snxt[i])
			if(!--dgr[sto[i]]) q[t++]=sto[i];
	}
	return 1;
}

int main()
{
	while(n=read(),m=read(),n&&m)
	{
		id=top=cnt=Enum=0, memset(H,0,sizeof H);
		memset(dfn,0,sizeof dfn);
		char c,d; int a,b,s,t;
		while(m--)
		{
			scanf("%d%c %d%c",&a,&c,&b,&d);
//			s= c=='h'?a<<1:a<<1|1;//WA：这表示的man是2a，但是新郎也是man 是2a+1=1 
			s= c=='w'?a<<1:a<<1|1;
			t= d=='w'?b<<1:b<<1|1;
			AddEdge(s,t^1), AddEdge(t,s^1);
		}
		AddEdge(0,1);
		for(int i=0; i<n<<1; ++i)
			if(!dfn[i]) Tarjan(i);
		if(Topo())
		{
			for(int i=1; i<n; ++i)
				if(col[bel[i<<1]]==1) printf("%dh ",i);
				else printf("%dw ",i);
			putchar('\n');
		}
		else puts("bad luck");
	}
	return 0;
}
