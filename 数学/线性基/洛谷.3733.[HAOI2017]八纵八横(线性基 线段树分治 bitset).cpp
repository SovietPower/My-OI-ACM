/*
216ms	4.2MB
$Description$
����һ��ͼ�����ֲ�����
1. ����ĳ����$(u,v)$����Ȩ$w$��
2. ɾ���¼���ĵ�$k$���ߡ�
3. ���¼���ĵ�$k$���ߵı�Ȩ��Ϊ$x$��
ÿ�β����������ǰ���о���1�ŵ�Ļ�������ֵ�����ļ�ֵΪ���бߵ����ͣ����ظ��߹��������Ȩ�����Ρ�
$n\leq 500,\ q\leq 1000$��
$Solution$
�������˼·ͬ[BZOJ2115 Xor]����ͼ�����л������Ͳ������Ի�����һ�����Ի�������������ֵ��
��`bitset`�Ż�һ�£������ĸ��Ӷ���$O(\frac{qmL^2}{w})$�ġ��������$70$�֣���
��Ϊ�ʼ��ͼ����ͨ�ģ���������һ��$dis[i]$��ʾ$1$��$i$�����͡�ÿ�μӱ߻��γɻ������������Ի��в���һ��Ԫ�ء�
��Ϊ�г����������߶������ξͺ��ˡ��߶�����ÿ���ڵ㿪һ�����Ի���ͬһʱ��ֻ��Ҫ$\log$�����Ի��Ŀռ䡣
���Ӷ�$O(\frac{q\log qL^2}{w})$��
��˵��������İ�=-= ��������ô��������Щģ����ģ�����=-=
�߶�����`bitset`ֱ�Ӵ��α��ø�ջ����ռ�����=-=
����������з��߶������������ߵ���������LOJͳ�ƣ�����
*/
#include <cstdio>
#include <cctype>
#include <vector>
#include <bitset>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e3+5,M=N<<1;
typedef std::bitset<N> Bit;

int tot,lim,Enum,H[N],nxt[N],to[N],las[M];
std::bitset<N> len[N],dis[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline char GetOpt()
{
	register char c=gc(); while(c!='A'&&c!='C') c=gc();
	return gc();
}
void ReadBit(Bit &bit)
{
	static char s[N];
	scanf("%s",s+1); int l=strlen(s+1);
	/*bit.reset(),*/ lim=std::max(lim,l-1);
	for(int i=1; i<=l; ++i) bit[l-i]=s[i]-48;
}
inline void AE(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
	ReadBit(len[Enum]), len[Enum-1]=len[Enum];
}
void Print(const Bit &x)
{
	bool fg=0;
	for(int i=lim; ~i; --i)
		fg|=x[i]==1, fg&&putchar((x[i]==1)+48);
	if(!fg) putchar('0');
	putchar('\n');
}

struct Edge
{
	int u,v; Bit w;
	inline void Init() {u=read(),v=read(),ReadBit(w);}
}e[M];
struct Base
{
	Bit x[N];
	void Insert(Bit v)
	{
		for(int i=lim; ~i; --i)
			if(v[i]==1)
				if(x[i].none())  {x[i]=v; break;}
				else v^=x[i];
	}
	void Query()
	{
		Bit ans; ans.reset();
		for(int i=lim; ~i; --i)
			if(ans[i]==0&&x[i].any()) ans^=x[i];
		Print(ans);
	}
};
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define S N<<2
	int tot,top,sk[23],id[S];
	Base base[23];
	std::vector<int> vec[S];
	#undef S
	void Modify(int l,int r,int rt,int L,int R,int v)
	{
		if(L<=l && r<=R) {vec[rt].push_back(v); return;}
		int m=l+r>>1;
		if(L<=m) Modify(lson,L,R,v);
		if(m<R) Modify(rson,L,R,v);
	}
	void Solve(int l,int r,int rt)
	{
		const std::vector<int> &v=vec[rt];
		int now=id[rt]=top?sk[top--]:++tot;
		base[now]=base[id[rt>>1]];
		for(int i=0,lim=v.size(),p; i<lim; ++i)
			p=v[i], base[now].Insert(dis[e[p].u]^dis[e[p].v]^e[p].w);
		if(l==r) {base[now].Query(), sk[++top]=now; return;}
		int m=l+r>>1;
		Solve(lson), Solve(rson), sk[++top]=now;
	}
}T;

void DFS(int x)
{
	static int Index,dfn[N];
	static bool vis[N];
	dfn[x]=++Index, vis[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]]) dis[v]=dis[x]^len[i], DFS(v);
		else if(dfn[v]<=dfn[x]) e[++tot]=(Edge){x,v,len[i]}, T.vec[1].push_back(tot);//>=!
}

int main()
{
	static int id[N];
	int n=read(),m=read(),q=read()+1;
	while(m--) AE(read(),read());
	DFS(1);
	#define S 1,q,1
	char c; int tmp=::tot,tot=tmp;
	for(int i=2,k,t,cnt=0; i<=q; ++i)
		if((c=GetOpt())=='d') e[++tot].Init(), ++cnt, las[id[cnt]=tot]=i;
		else if(c=='a') k=id[read()], T.Modify(S,las[k],i-1,k), las[k]=0;
		else t=read(), k=id[t], T.Modify(S,las[k],i-1,k), las[k]=0,
			++tot, e[tot].u=e[k].u, e[tot].v=e[k].v, ReadBit(e[tot].w), las[id[t]=tot]=i;//lasҪ�Ķ�=-= 
	for(int i=tmp+1; i<=tot; ++i) if(las[i]) T.Modify(S,las[i],q,i);
	T.Solve(S);

	return 0;
}
