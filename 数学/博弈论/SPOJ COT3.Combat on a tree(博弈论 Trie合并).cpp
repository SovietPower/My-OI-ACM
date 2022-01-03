/*
0.11s	35M
$Description$
����һ��$n$���������ÿ�����Ǻ�ɫ���ɫ������������������ÿ�ο���ѡһ����ɫ�ĵ㣬���������ڵ�·���ϵ����е�Ⱦ�ڡ����ܲ��������䣬�������Ƿ���Ӯ������ܣ������һ��ѡ����Щ�ڵ���Ӯ��
$n\leq10^5$��
$Solution$
����Ҷ�ӽڵ㣬�����Ⱦɫ��$SG(x)=1$������$=0$��
���Ǵ���������ÿ��������$SG$ֵ����$SG(x)$��ʾ$x$������$SG$ֵ��$g(x)$��ʾ��$x$������������ܵõ��ĺ�̵�$SG$ֵ���ϣ�ֻ����$x$����������ô$SG(x)=\mathbb{mex}\{g(x)\}$��

������μ���$g(x)$����$sum[x]=sg(v_1)\ \mathbb{xor}\ sg(v_2)\ \mathbb{xor}...,\ v_i\in son[x]$��
��$x$�Ǻڵ㣬������β���ѡ��$v_i$�����е�ĳ���㣬��ô��������״̬���䣬$v_i$�����ĺ��״̬����$g(v_i)$�е�ĳ��������$g(x)=sum[x]\ \mathbb{xor}\ sg(v_i)\ \mathbb{xor}\ (g(v_i)�е�ĳ��ֵ)$��
��������ÿ��$g(v_i)$����$\mathbb{xor}$һ�������ϲ��������Ϳ��Եõ�$g(x)$�ˡ�
��$x$�ǰ׵㣬����һ��ѡ$x$�ĺ�̣�ѡ$x$��õ�״̬��$SG$ֵ����$sum[x]$��������$g(x)$���ٲ���һ��$sum[x]$���ɡ�

��Ҫ֧����$\mathbb{mex}$��������$01Trie$ά�����ϲ���ʱ���������ʽ�ϲ���$O(n\log^2n)$��Ҳ���������߶����ϲ�����$O(n\log n)$��

���ڵڶ��ʣ�����ѡ��һ���ڵ������$SG$ֵ�����׷��־��ǳ�ȥ�������ڵ�·���ϵĵ�����е��$SG$ֵ�����͡�
��$up[x]$��ʾ��ȥ$x$�����ڵ�·���ϵĵ��⣬���нڵ��$SG$ֵ���ͣ���ô$up[x]=up[fa[x]]^{\wedge}sum[fa[x]]^{\wedge}SG(x)$��ѡ��$x$��$x$�ĸ��������Ƕ����ģ������$SG$ֵ����$up[x]^{\wedge}sum[x]$��$up$Ҳ����ֱ��$DFS$��ʱ�򴫸��Σ���
�������$up[x]^{\wedge}sum[x]=0$��ѡ�������Ǳ�ʤ�ġ�

���$SG$ֵ�����ֵ��ɶ��...
ע��$Trie$Ҫ����Ҷ�ӵĵط���������`Merge`��ע�����߶����ϲ�һ������Ҷ�ӣ�������ô����д��...����
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define Bit 16
#define gc() getchar()
#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;

int Enum,H[N],nxt[N<<1],to[N<<1],root[N],sg[N],sum[N],up[N];
bool col[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Trie
{
	#define S N*20
	#define ls son[x][0]
	#define rs son[x][1]
	int tot,son[S][2],tag[S];
	bool full[S];
	#define Update(x) full[x]=full[ls]&&full[rs]
	inline void Upd(int x,int v,int dep)
	{
//		if(dep<0) return;
		if(v>>dep&1) std::swap(ls,rs);
		tag[x]^=v;
	}
	inline void PushDown(int x,int dep)
	{
		if(dep&&tag[x]) Upd(ls,tag[x],dep-1), Upd(rs,tag[x],dep-1), tag[x]=0;
	}
	void Insert(int &x,int v,int dep)
	{
		x=++tot;
		if(dep<0) {full[x]=1; return;}
		v>>dep&1 ? Insert(rs,v,dep-1) : Insert(ls,v,dep-1);
	}
	int Merge(int x,int y,int dep)
	{
		if(!x||!y) return x|y;
		if(dep<0) return x;
		PushDown(x,dep), PushDown(y,dep);
		ls=Merge(ls,son[y][0],dep-1), rs=Merge(rs,son[y][1],dep-1);
		Update(x); return x;
	}
	int Mex(int x,int dep)
	{
		if(!x||dep<0) return 0;
		PushDown(x,dep);
		return full[ls]?(1<<dep)+Mex(rs,dep-1):Mex(ls,dep-1);
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void DFS1(int x,int fa)
{
	if(!col[x]) T.Insert(root[x],0,Bit);
	int s=0;
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa)
			DFS1(v,x), s^=sg[v], T.Upd(root[v],sg[v],Bit), root[x]=T.Merge(root[x],root[v],Bit);
	if(s) T.Upd(root[x],s,Bit);
	sum[x]=s, sg[x]=T.Mex(root[x],Bit);
}
void DFS2(int x,int fa)
{
	up[x]=up[fa]^sum[fa]^sg[x];
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa) DFS2(v,x);
}

int main()
{
	const int n=read();
	for(int i=1; i<=n; ++i) col[i]=read();
	for(int i=1; i<n; ++i) AE(read(),read());
	DFS1(1,0), sum[0]=sg[1], DFS2(1,0);
	bool f=0;
	for(int x=1; x<=n; ++x) if(!col[x]&&!(sum[x]^up[x])) f=1, printf("%d\n",x);
	if(!f) puts("-1");

	return 0;
}
