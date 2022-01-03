/*
5028kb	1036ms
������˵�˳��û��Ӱ�죬��֮����ĳһ�߶ȷ��������йء������Ȱ���˰��߶�����
��߶�Ϊ$i$�ķ���$s_i$������ô����$\sum\frac{s_i(s_i-1)}{2}$����Ȼ����Ҫ��ÿһ�У��߶ȣ��ķ����������١�
Ȼ������뵽���֣�����ÿһ�еķ���������$mid$�Ƿ���С���Ȼ���Ǵ���ߵ���˵����߶Ȳ���������Ϳ����ˣ�Ҫ���߶���ά�������Ӷ�$O(n\log^2n)$��
���ǲ���Ҫ������ְ���ÿ���ҵ�$s_i$��С��λ�ã���$k$�������ȥ�����ˡ�
��ô��Ȼ����˴ӵ͵�������ÿ�θ���$s_i$��С�����䣬�Ϳ��Ա�֤��ȷ���ˡ�
�߶���ά��������$k$��λ���$[h-k+1,h]$������������˵���ܲ���һ������������ֵ���������˵㣬��Ҫ���ڸ�һ����ƽ�Ƶ�����������˵�ȥ��������֤$s_i$�ݼ����Դ˾��ҵ�$h-k+1$λ�ô������ε����Ҷ˵�$L,R$����һ��$R$�Ƿ�$<h$�ͺ��ˡ�������ͼ��������⣬��ʼʱ�Ϳ����������ģ�
���Ӷ�$O(n\log n)$��
��������״����д����Ȼ��ѯλ��������$\log$�ģ����ǳ���̫С��ûO2�߶����Ȳ�����
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
#define MAXIN 300000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;

pr A[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define S N<<2
	int mn[S],tag[S];
	#undef S
	#define Upd(rt,v) mn[rt]+=v,tag[rt]+=v
	#define Update(rt) mn[rt]=std::min(mn[ls],mn[rs])
	#define PushDown(rt) Upd(ls,tag[rt]), Upd(rs,tag[rt]), tag[rt]=0
	void Modify(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) {Upd(rt,1); return;}
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		if(L<=m) Modify(lson,L,R);
		if(m<R) Modify(rson,L,R);
		Update(rt);
	}
	int FindPos(int l,int r,int rt,int p)
	{
		while(l!=r)
		{
			if(tag[rt]) PushDown(rt);
			int m=l+r>>1;
			p<=m ? (r=m,rt=ls) : (l=m+1,rt=rs);
		}
		return mn[rt];
	}
	int FindL(int l,int r,int rt,int val)
	{
		while(l!=r)
		{
			if(tag[rt]) PushDown(rt);
			int m=l+r>>1;
			mn[ls]<=val ? (r=m,rt=ls) : (l=m+1,rt=rs);
		}
		return l;
	}
	int FindR(int l,int r,int rt,int val)
	{
		while(l!=r)
		{
			if(tag[rt]) PushDown(rt);
			int m=l+r>>1;
			mn[ls]<val ? (r=m,rt=ls) : (l=m+1,rt=rs);
		}
		return mn[rt]==val?l:l-1;
	}
	LL Calc(int l,int r,int rt)
	{
		if(l==r) return 1ll*mn[rt]*(mn[rt]-1)>>1;
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		return Calc(lson)+Calc(rson);
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

int main()
{
	#define S 1,lim,1
	const int n=read();
	for(int i=1,h; i<=n; ++i) h=read(),A[i]=std::make_pair(h,read());//h,k
	std::sort(A+1,A+1+n);
	int lim=A[n].first;
	for(int i=1; i<=n; ++i)
	{
		int h=A[i].first,k=A[i].second;
		int mn=T.FindPos(S,h-k+1),L=T.FindL(S,mn),R=std::min(h,T.FindR(S,mn));
		if(L!=h-k+1)//if(R<h)
		{
			T.Modify(S,L,L+k-h+R-1);
			if(R<h) T.Modify(S,R+1,h);
		}
		else T.Modify(S,L,L+k-1);
	}
	printf("%lld\n",T.Calc(S));

	return 0;
}
