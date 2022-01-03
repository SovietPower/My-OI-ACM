/*
�Ƚ������������Ϳ��԰���С�����˳��ά����������ö�ٵ�һ��δ��ͨ�ı߾����ϣ�����ͨ��(�õ�ǰ�����)�滻��·������С�ıߣ�����һ��������
ÿ�ι�����ʱ���´𰸡��𰸾��ǵ�ǰ�߼�ȥ����������С�ߵ�Ȩֵ��
LCT��ά����С�ߵı�š�����С�߰����ϵı���vis[]��Ǽ��ɡ�
���찡.
(���Ⱪ�����������ö��һ���ֽ�㣬����֮������С������������֮ǰ�����������)
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define INF 10000007
const int N=5e4+5,M=2e5+5,S=N+M;

int n,m,_fa[N];
bool vis[M];
struct Edge
{
	int fr,to,val;
	Edge() {}
	Edge(int f,int t,int v): fr(f),to(t),val(v) {}
	bool operator <(const Edge &a)const {
		return val<a.val;
	}
}e[M];
namespace LCT
{
	#define lson son[x][0]
	#define rson son[x][1]

	int fa[S],son[S][2],sk[S],pos[S],val[S];
	bool tag[S];
	inline int Get(int x,int y){//ȡ��С�ı� 
		return val[x]<val[y]?x:y;
	}
	inline void Update(int x){
		pos[x]=Get(x,Get(pos[lson],pos[rson]));//�����Ҷ��ӵ���С��pos[]��
	}
	inline bool n_root(int x){
		return son[fa[x]][0]==x||son[fa[x]][1]==x;
	}
	inline void Rev(int x){
		std::swap(lson,rson), tag[x]^=1;
	}
	void PushDown(int x){
		if(tag[x]) Rev(lson),Rev(rson),tag[x]=0;
	}
	void Rotate(int x)
	{
		int a=fa[x],b=fa[a],l=son[a][1]==x,r=l^1;
		if(n_root(a)) son[b][son[b][1]==a]=x;
		if(son[x][r]) fa[son[x][r]]=a;
		fa[a]=x, fa[x]=b, son[a][l]=son[x][r], son[x][r]=a;
		Update(a);
	}
	void Splay(int x)
	{
		int t=1,a=x; sk[1]=x;
		while(n_root(a)) sk[++t]=a=fa[a];
		while(t) PushDown(sk[t--]);
		while(n_root(x))
		{
			if(n_root(a=fa[x])) Rotate(son[a][1]==x^son[fa[a]][1]==a?x:a);
			Rotate(x);
		}
		Update(x);
	}
	void Access(int x){
		for(int pre=0; x; x=fa[pre=x])
			Splay(x), rson=pre, Update(x);
	}
	void Make_root(int x){
		Access(x), Splay(x), Rev(x);
	}
	void Split(int x,int y){
		Make_root(x), Access(y), Splay(y);
	}
	void Link(int x){
		Make_root(e[x].to), fa[fa[e[x].to]=x+N]=e[x].fr;
	}
	void Cut(int x){
		Access(e[x-N].to), Splay(x), lson=rson=fa[lson]=fa[rson]/*=fa[x]*/=0;//fa[x]Ӧ�����ò����ɡ���ע�����˳�򣡺����lson,rson...
	}
}
using namespace LCT;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int Get_fa(int x){
	return x==_fa[x]?x:_fa[x]=Get_fa(_fa[x]);
}

int main()
{
	n=read(),m=read();
	val[0]=INF;//�սڵ㣡
	for(int i=1; i<=n; ++i) _fa[i]=i, val[i]=INF;//�����Լ���Ȩֵ����ΪINF����Ӱ���(��С��) 
	for(int u,v,w,i=1; i<=m; ++i) u=read(),v=read(),w=read(),e[i]=Edge(u,v,w);
	std::sort(e+1,e+1+m);
//	for(int i=1; i<=m; ++i) val[i+N]=e[i].val;
	int res=1e6;
	for(int p=1,x,y,k=1,i=1; i<=m; ++i)
	{
		val[i+N]=e[i].val, x=e[i].fr, y=e[i].to;
		if(k<n && Get_fa(x)!=Get_fa(y))
		{
			_fa[_fa[x]]=_fa[y];//·��ѹ���� 
			Link(i), vis[i]=1;
			if(++k>=n) res=e[i].val-e[p].val;
		}
		else if(x!=y)//��Ҫ�����ر� 
		{
			Split(x,y);
			vis[pos[y]-N]=0, vis[i]=1;//������Splay(y)������y����Ϣpos[y]������Ҫ����pos[y]��vis��Cut().
			while(!vis[p]) ++p;
			Cut(pos[y]), Link(i);
			if(k>=n) res=std::min(res,e[i].val-e[p].val);
		}
	}
	printf("%d",res);

	return 0;
}
