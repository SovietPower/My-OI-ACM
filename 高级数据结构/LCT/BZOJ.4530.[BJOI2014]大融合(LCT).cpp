/*
3264kb	1380ms
��������Ŀ��Ҫ��ȥ��һ���ߺ���������sz[]�ĳ˻���
LCTά������������Ϣ����ô������?
������s_i[x]����¼�������x�������ĺ�(���������)����ôsum[x]����ʱ����sum[lson]+sum[rson]+val[x]+s_i[x]��
������Ҫs_i[x]������ʲôʱ���Ӱ������
Splay()Ӱ���ֻ�ǽڵ��ڸ�����Splay�е����λ�ã�����������е���Ϣ����Ӱ�졣
Access()��Ҫ�����Ҷ��ӣ�������һ������Ӽ���һ��ʵ���ӣ���Ӧ���¼��ɣ����ֻ��Ҫά��sum֮�಻��ҪUpdate()(һ��һ��)��
Make_root()��Ӱ�졣��Ȼʹ��������̬�������˱仯������һ��������ֱ��������ȡ��Ϣ��
Split()����Ҫ����(���ǵ��ú���)��
Find_root()��Ӱ�졣 
Link()��y����һ������ӣ���ôsum[y],s_i[y]����x����һ��֮ǰҪ��y������(Access(y),Splay(y))������y���ϵĲ��ֲ�����¡�
Cut()��Ӱ�졣��Ȼ���˸����ӣ�����һ������������ֱ�ӻ�ȡ��Ϣ���´λ�ȡ��Ϣʱ����£�����Ӱ����ȷ�ԡ�
�����𰸾���x,y����s_i+1�ĳ˻�(�����·����ʵ�ľ���x->y�ˣ��ټ����Լ�)������(yΪ��ʱ)sz[x]*(sz[y]-sz[x]) 
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1e5+5;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
namespace LCT
{
	#define lson son[x][0]
	#define rson son[x][1]

	int fa[N],son[N][2],sz[N],sz_i[N],sk[N];
	bool tag[N];
	inline void Update(int x){
		sz[x]=sz[lson]+sz[rson]+1+sz_i[x];
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
			a=fa[x];
			if(n_root(a)) Rotate(son[a][1]==x^son[fa[a]][1]==a?x:a);
			Rotate(x);
		}
		Update(x);
	}
	void Access(int x){
		for(int pre=0; x; x=fa[pre=x])
		{
			Splay(x);
			sz_i[x]+=sz[rson], sz_i[x]-=sz[rson=pre];
//			Update(x);
		}
	}
	void Make_root(int x){
		Access(x), Splay(x), Rev(x);
	}
	void Split(int x,int  y){
		Make_root(x), Access(y), Splay(y);
	}
	void Link(int x,int y){
		Split(x,y), sz_i[fa[x]=y]+=sz[x], Update(y);//���£�
	}
	long long Query(int x,int y){
		Split(x,y); return 1ll*(sz_i[x]+1)*(sz_i[y]+1);//1ll*sz[x]*(sz[y]-sz[x]);
	}
}

int main()
{
	int n=read(),q=read(),x,y; char opt[3];
	for(int i=1; i<=n; ++i) LCT::sz[i]=1;
	while(q--)
	{
		scanf("%s",opt),x=read(),y=read();
		if(opt[0]=='A') LCT::Link(x,y);
		else printf("%lld\n",LCT::Query(x,y));
	}
	return 0;
}
