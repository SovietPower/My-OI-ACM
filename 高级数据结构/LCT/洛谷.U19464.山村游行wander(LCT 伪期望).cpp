/*
����: ɭ�֣���̬���ߡ�ɾ�ߣ�ѯ�ʴ�S��ʼ�ߵ�T������ʱ�䡣��λ: ÿ���˻������ѡһ��δ�߹��ı��ߣ��ߵ���·���ߣ����˻ء�����ֱ���յ�T����һ���ߡ���һ�����˻ض�����ʱ��1. 
��Ŀ�ص����ߵ�һ������һ����ȫ���꣬���������ֵ������ͼ�����Կ�����һ������: 
��S��ʼ������ߵ�ͨ��T�ı߻�S��һ����������S������i������Ϊ 2*p[i]*sz[i](������)��
��S->T��·���ϣ����ܻ�����ߵ�һ�������У�����ͬ��Ϊ 2*p[i]*sz[i]��
����������Ϊ Ans = ��(ö��S������i)2*p[i]*sz[i] + ��(ö��·���ϵ�����i)2*p[i]*sz[i].
��ô�������p[i]�Ƕ����أ�����1/2��������ͬ������һ��Ӱ��û�С�
���� Ans = ��(ö��S������i)sz[i] + ��(ö��·���ϵ�����)sz[i]. LCTά������sz[]�����ˡ�(С���ǻ��˵�)
����Ļ�������� ���Ĵ�С-sz_i[T]-1 ���� ��TΪ������������С(��T��·��ȷʵ����1�������Ѿ�����S��sz(1)��).
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1e5+5;

namespace LCT
{
	#define lson son[x][0]
	#define rson son[x][1]

	int fa[N],son[N][2],sz[N],sz_i[N],sk[N];
	bool tag[N];
	inline void Update(int x){
		sz[x]=sz[lson]+sz[rson]+sz_i[x]+1;
	}
	inline bool n_root(int x){
		return son[fa[x]][0]==x||son[fa[x]][1]==x;
	}
	inline void Rev(int x){
		std::swap(lson,rson), tag[x]^=1;
	}
	inline void PushDown(int x){
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
			Splay(x), sz_i[x]+=sz[rson]-sz[pre], rson=pre;//Update(x);
	}
	void Make_root(int x){
		Access(x), Splay(x), Rev(x);
	}
	void Split(int x,int y){
		Make_root(x), Access(y), Splay(y);
	}
	int Find_root(int x)
	{
		Access(x), Splay(x);
		while(lson) x=lson;
		return x;
	}
	bool pre_Link(int x,int y){
		Make_root(x);//Split(x,y); //��Find_root(y)
		return Find_root(y)==x;
	}
	void Link(int x,int y){
		sz_i[y]+=sz[x], fa[x]=y, Update(y);
	}
	bool pre_Cut(int x,int y){
		Make_root(x);
		return Find_root(y)==x&&fa[x]==y&&!rson;
	}
	void Cut(int x,int y){
		fa[x]=son[y][0]=0, Update(y);
	}
	int Query(int x,int y){//��pre_Link():Make_root(x), Access(y), Splay(y).
		return sz[son[y][0]];//return sz[y]-sz_i[y]-1;
	}
}
inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int n=read(),q=read(),opt,x,y;
	while(q--)
	{
		opt=read(),x=read(),y=read();
		if(!opt){
			if(LCT::pre_Link(x,y)) puts("ILLEGAL");
			else LCT::Link(x,y), puts("OK");
		}
		else if(opt==1){
			if(!LCT::pre_Cut(x,y)) puts("ILLEGAL");
			else LCT::Cut(x,y),puts("OK");
		}
		else if(LCT::pre_Link(x,y)) printf("%d.0000\n",LCT::Query(x,y));
		else puts("ILLEGAL");
	}
	return 0;
}
