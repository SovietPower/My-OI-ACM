/*
280ms	8000KB
$Description$
����һ�����У����ֲ�����һ���޸�һ�����ֵ�����Ǹ�һ������$[l,r]$�����ܷ�ֻ�޸�һ����ʹ������gcdΪ$x$��
$Solution$
�뵽��ά������gcd�ͺܼ��ˡ�
���������ѯ������������ֻ����һ�������gcd������x���ٵݹ���������䡣
��Ϊ�����ݹ�����ݹ鵽����Ҷ�ӣ����Ը��Ӷ�OK��
�����߶���ά��gcd...����1��log�ģ��������Ϊ����
��շת�ദһ��
������ֻ�/2
��ð�˳����gcd
ȫ���ʹ�ȥ��gcd
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=5e5+5;

int read();
struct Segment_Tree
{
	#define S N<<2
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	int g[S];
	#undef S

	#define Update(rt) g[rt]=Gcd(g[ls],g[rs])
	int Gcd(int x,int y)
	{
		return y?Gcd(y,x%y):x;
	}
	void Build(int l,int r,int rt)
	{
		if(l==r) {g[rt]=read(); return;}
		int m=l+r>>1; Build(lson), Build(rson);
		Update(rt);
	}
	void Modify(int l,int r,int rt,int p,int v)
	{
		if(l==r) {g[rt]=v; return;}
		int m=l+r>>1;
		if(p<=m) Modify(lson,p,v);
		else Modify(rson,p,v);
		Update(rt);
	}
	bool Query(int l,int r,int rt,int L,int R,int x,int &K)
	{
		if(!(g[rt]%x)) return 1;
		if(l==r) return --K>0;
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return Query(lson,L,R,x,K)&&Query(rson,L,R,x,K);
			else return Query(lson,L,R,x,K);
		return Query(rson,L,R,x,K);
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	#define S 1,n,1
	int n=read();
	T.Build(S);
	for(int Q=read(),l,r,tmp; Q--; )
		if(read()==1) l=read(),r=read(),puts(T.Query(S,l,r,read(),tmp=2)?"YES":"NO");
		else l=read(),T.Modify(S,l,read());

	return 0;
}
