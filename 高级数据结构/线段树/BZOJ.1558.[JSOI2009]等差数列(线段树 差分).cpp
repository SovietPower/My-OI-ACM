/*
12460kb	2476ms
���ȿ��԰�ԭ����$A_i$ת���ɲ������$B_i$ȥ����
�������������һ���Ȳ�����$(l,r,a_0,d)$���Ϳ���ת��Ϊ$B_{l-1}$+=$a_0$��$B_r$-=$(r-l)*d+a_0$��$B_{l...r-1}$+=$d$��
���ڲ�ѯ���ƺ�ֻ��Ҫ������$b_i$�������θ�����
�����ǣ����磺
$A:\ 0\ 1\ 3\ 6\ 10\\B:\ \ \ 1\ 2\ 3\ 4$
����$3$������$4$�����ǿ����������֣�$\{0,1\},\{3,6\},\{10\}$������$\{0,1\},\{3\},\{6,10\}$�ȵȣ��õ������Ȳ����С�
Ϊʲô�᲻��$4$�أ�����������Ҳ��һ���Ȳ������⣬�������ѡ���˲�������е�$1,4$��Ҳ����ѡ$\{0,1\},\{6,10\}$���ֳ������Ȳ����У���$A_3=3$������$B_2=2$����$B_3=3$�أ�
������ʵ���ڣ������м��Ǹ���ֻ���������ҵȲ������е�һ����������ȵ�ʱ����԰������Ȳ���������������

> Ȼ�����Ϻö���ⶼû����˵����°���ֻ��������ƪ�������˼�ģ�[���](https://blog.csdn.net/XHRlyb/article/details/79439580)��[���](https://www.cnblogs.com/galaxies/p/bzoj1558.html)��[yyb��](http://www.cnblogs.com/cjyyb/p/8557066.html)��ʵҲ�ǰɣ����������ֻ��д����$s$�Ķ��壬һ�����"���Ҷ˵�ѡ��ѡ"��ʲô�Ľ��Ͷ�û�У���ȻҲ��ֻ���Ҳ�����⣩��
��Ȼֻ�Ǹ�����⿩������ʾ��һ����������������ֶ��ܺʹ����Ӧ�ϣ���ǰ���ֲ�����˵��ȥ��

Ȼ��С�����ڲ��Ĵ��ںϲ��ɴ�����ʱ�ǲ����ģ�Ҫ���ǵ�ֻ�Ƕ˵������ĸ���������⡣
���Կ������߶���ά������$L,R$��ʾ��ǰ�����$B_l,B_r$��$s_0,s_1,s_2,s_3$�ֱ��ʾ�����Ҷ˵㶼������������䣨������������е������ɵȲ����У�ʱ�Ĵ𰸣� ��˵����ڶ��Ҷ˵㲻�����������Ĵ𰸣��Ҷ˵����ڶ���˵㲻�����������Ĵ𰸣����Ҷ˵㶼�����������Ĵ𰸡�
����Щ�Ϳ��Ժϲ������ˣ�����Ϳ��Լ������ˡ�
ѯ�ʵĴ𰸣�����ѯ������ϲ����$s_3$��
��Ϊ���ڲ�ֺ������������ѯ��$[l,r]$�ǲ�ѯ$[l,r-1]$����Ҫע��߽����⡣
���Ӷ�$O(q\log n)$��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;

int A[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Node
{
	int L,R,s0,s1,s2,s3;//s0:(l,r) ���Ҷ������� s1:[l,r) s2:(l,r] s3:[l,r] 
	inline Node operator +(const Node &b)
	{
		Node c;
		c.L=L, c.R=b.R; int v=R==b.L;
		c.s0=std::min(s2+b.s1-v, std::min(s0+b.s1, s2+b.s0));
		c.s1=std::min(s3+b.s1-v, std::min(s3+b.s0, s1+b.s1));
		c.s2=std::min(s2+b.s3-v, std::min(s0+b.s3, s2+b.s2));
		c.s3=std::min(s3+b.s3-v, std::min(s1+b.s3, s3+b.s2));
		return c;
	}
};
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,rt<<1
	#define rson m+1,r,rt<<1|1
	#define S N<<2
	int tag[S];
	Node t[S];
	#undef S
	#define Upd(x,v) t[x].L+=v, t[x].R+=v, tag[x]+=v
	#define Update(rt) t[rt]=t[ls]+t[rs]
	inline void PushDown(int rt)
	{
		Upd(ls,tag[rt]), Upd(rs,tag[rt]), tag[rt]=0;
	}
	void Build(int l,int r,int rt)
	{
		if(l==r)
		{
			t[rt]=(Node){A[l],A[l],0,1,1,1};
			return;
		}
		int m=l+r>>1;
		Build(lson), Build(rson), Update(rt);
	}
	void Modify(int l,int r,int rt,int L,int R,int v)
	{
		if(L<=l && r<=R) {Upd(rt,v); return;}
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		if(L<=m) Modify(lson,L,R,v);
		if(m<R) Modify(rson,L,R,v);
		Update(rt);
	}
	void ModifyP(int l,int r,int rt,int p,int v)
	{
		if(l==r) {Upd(rt,v); return;}
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		p<=m ? ModifyP(lson,p,v) : ModifyP(rson,p,v);
		Update(rt);
	}
	Node Query(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) return t[rt];
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return Query(lson,L,R)+Query(rson,L,R);
			else return Query(lson,L,R);
		return Query(rson,L,R);
	}
}T;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline char GetOpt()
{
	register char c=gc();
	while(c!='A'&&c!='B') c=gc();
	return c;
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	if(n==1)
	{
		for(int Q=read(); Q--; )
			if(GetOpt()=='B') puts("1");
		return 0;
	}
	--n;
	for(int i=1; i<=n; ++i) A[i]=A[i+1]-A[i];
	T.Build(1,n,1);
	for(int Q=read(); Q--; )
		switch(GetOpt())
		{
			case 'A':
			{
				int l=read(),r=read(),a=read(),d=read();
				if(l<r) T.Modify(1,n,1,l,r-1,d);
				if(l>1) T.ModifyP(1,n,1,l-1,a);
				if(r<=n) T.ModifyP(1,n,1,r,(l-r)*d-a);//r!=n!
				break;
			}
			case 'B':
			{
				int l=read(),r=read();
				if(l!=r) printf("%d\n",T.Query(1,n,1,l,r-1).s3);
				else puts("1");
				break;
			}
		}
	return 0;
}
