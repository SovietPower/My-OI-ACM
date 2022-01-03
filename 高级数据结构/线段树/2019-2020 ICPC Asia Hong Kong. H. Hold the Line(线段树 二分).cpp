/*
2292ms	116300KB
������ݷ�Χ�ж�����
������ǵ���fread��

$Description$
$n$��λ�ã����ÿ��λ����û������
$m$�β��������������֣�
1. ��һ��û������λ��$x$��һ����$v$��
2. ����$x$��ѯ��$[l,r]$����$x$�����С��������$\min_{v\in[l,r]}|x-v|$��
$n\leq 5\times10^5,\ m\leq 10^6$��

$Solution$
��򵥵����߶�����set��$O(m\log^2n)$+�������Թ����ˡ�
**Sol 1**
�������ߣ���ѯ�ʰ�$r$����ÿ������$r$λ�ò����ֵ���£�Ȼ������$r$Ϊ�Ҷ˵��ѯ�ʡ�

���ʱ��һ��ѯ��Ϊ$[L,R],x$��ѯ�ʱ��Ϊ$id$��
���Ѿ������ֵΪ$v_i$����Ӧ�Ĳ������Ϊ$i$������λ��Ϊ$pos_i\leq R$��
��$v_i$�ܸ���ѯ�ʵ��ҽ���$pos_i\geq L$��$i\lt id$��

��ѯ�ʲ�ɣ�������$v_i$����$v_i\leq x$��$pos_i\geq L$��$i\lt id$��������С��$v_i$����$v_i\geq x$��$pos_i\geq L$��$i\lt id$��
�Ե�һ��ѯ�ʣ�ֻ�迼��$[1,x]$�У���ҵ�����$pos_i\geq L$��$i\lt id$��$i$���ĸ�������������һ���߶�������ÿ���ڵ�$[l,r]$���ж�$l\leq v_i\leq r$ʱ�Ƿ��з���������$i$������оͼ��������Ҷ�����������ӣ����������û�о�return��
Ҳ������һ���߶���ά�����е�ǰ��$v_i$���ڵ�$[l,r]$��������$l\leq v_i\leq
r$��$i$��
Ȼ������ж�ĳ�ڵ��$v_i$���Ƿ����$i$ʹ$pos_i\geq L$��$i\lt id$��
ע�⵽�����ǰ�$pos$��С������²����ֵ�����Ժ�����ֵ$pos$һ������֮ǰ�ġ����ڵ����б�Ҫ�����ĵ㣬��Ҫô$pos$����Ҫô$i$��С�ĵ㡣���������ĳ�ڵ����$v_i$ʱ��$i$С�ڸýڵ�����һ��ֵ�Ĳ�����ţ��Ǹ�ֵ�Ϳ���ɾ����
���׷�������ÿ���ڵ㶼��һ���������У��Ӷ��׵���β�����$i$������$pos$������
����ÿ���ڵ�Ĳ�ѯ��ֻ��Ҫ���ֵ�һ��$pos\geq L$��ֵ��Ȼ���ж�����$i$�Ƿ���$i\lt id$�������һ��$i\lt id$��ֵ��Ȼ���ж��Ƿ���$pos\geq L$����
����ÿ�β�ѯ���Ӷ�$O(\log^2n)$��ÿ�β���ֵ���͸��¸��ڵ㵽��ֵ�������ϵĵ������У����Ӷ�$O(\log n)$��

���Ը��Ӷ�$O(n\log n+m\log^2n)$��
ע��ռ�Ҳ��$O(n\log n)$�ģ��տ�ʼҪ����������ÿ���ڵ������ĸ�����ǰ׺���㣩����һ���䵥�����еĿռ䡣

**Sol 2**
���ߵĻ����Էֿ顣ÿ������Ϊ�����$\sqrt n$������������ÿ�β���ʱ��������������ŵ���Ӧλ�ã�ʹÿ���������������
��ѯʱ���߽籩������������Ϊ�������򣬿��Զ��ֵ�һ��С�ڵ���$x$����$A[p]$��$A[p],A[p+1]$��Ϊ���ܴ𰸡�
���Ӷ�$O(m\sqrt n+m\sqrt n\log n)$����std�ܵĲ��졣��
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define pb emplace_back
typedef long long LL;
const int N=5e5+5,M=1e6+6,Q=1e7+1e6+5/*�������ٵĿռ䣬1e7����̫С*/;

int A[M],sum[M],Ans[M],qid[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Quries
{
	int L,pos,val;
}q[M];
std::vector<int> vec[N];
struct Segment_Tree
{
	#define S M<<2	//ֵ��ΪM��
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	int now,res,qL,qid,pos[M],L[S],R[S],q[Q];
	#undef S
	void Build(int l,int r,int rt)
	{
		L[rt]=now, R[rt]=now-1;	//��ʼ���ýڵ�Ķ��׺Ͷ�β 
		now+=sum[r]-sum[l-1];	//����ýڵ�Ŀռ� 
		if(l==r)
		{
			pos[l]=rt;			//��һ��ÿ��ֵҶ�ڵ��λ�� 
			return;
		}
		int m=l+r>>1;
		Build(lson), Build(rson);
	}
	void Update(int p,int id,int val)
	{
		for(int rt=pos[val]; rt; rt>>=1)	//��¼Ҷ�ڵ�λ�ã��Ե�����for�Ϳ����� 
		{
			int h=L[rt], t=R[rt];
			while(h<=t && q[t]>id) --t;
			q[++t]=id, R[rt]=t;
		}
	}
	bool Check(int rt)
	{
		int l=L[rt],r=R[rt],mid;
		while(l<=r)
		{
			mid=l+r>>1;
			if(q[mid]<qid && ::q[q[mid]].pos>=qL) return 1;
			if(q[mid]<qid) l=mid+1;
			else r=mid-1;
		}
		return 0;
//		while(l<r)
//		{
//			mid=l+r+1>>1;
//			if(q[mid]<qid) l=mid;
//			else r=mid-1;
//		}
//		return q[l]<qid && ::q[q[l]].pos>=qL;
	}
	void QueryL(int l,int r,int rt,int qR)
	{
		if(res||L[rt]>R[rt]) return;	//! ������û�����ǵ�return 
		if(r<=qR)
		{
			if(!Check(rt)) return;	//���ҵ���Ӧ���䣬��Check����CheckһЩ�ǲ��ǻ�� 
			if(l==r) {res=l; return;}	//��Ȼ���Ϸ����䲻��DFS��Ҷ�ڵ� 
		}
		int m=l+r>>1;
		if(m<qR) QueryL(rson,qR);
		QueryL(lson,qR);
	}
	void QueryR(int l,int r,int rt,int qL)
	{
		if(res||L[rt]>R[rt]) return;	//! ������û�����ǵ�return 
		if(qL<=l)
		{
			if(!Check(rt)) return;
			if(l==r) {res=l; return;}
		}
		int m=l+r>>1;
		if(qL<=m) QueryR(lson,qL);
		QueryR(rson,qL);
	}
}T;

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
void Query(int id,int cnt)
{
	int L=q[id].L,val=q[id].val,ans=2e9;
	T.qL=L, T.qid=id;

	T.res=0, T.QueryL(1,cnt,1,val);
	if(T.res) ans=A[val]-A[T.res];
	T.res=0, T.QueryR(1,cnt,1,val);
	if(T.res) ans=std::min(ans,A[T.res]-A[val]);

	Ans[id]=ans==2e9?-1:ans;
}

int main()
{
	for(int Ts=read(); Ts--; )
	{
		int n=read(),m=read(),cnt=m;
		for(int i=1; i<=m; ++i)
		{
			if(!read()) q[i]=Quries{0,read(),read()};
			else q[i]=Quries{read(),read(),read()};
			A[i]=q[i].val;
		}
		std::sort(A+1,A+1+m), cnt=std::unique(A+1,A+1+m)-A-1;	//ֵ�ĸ���Ϊm����n�� 

		memset(sum,0,cnt+1<<2), memset(qid,0,n+1<<2);
		for(int i=1; i<=n; ++i) std::vector<int>().swap(vec[i]);

		for(int i=1; i<=m; ++i)
		{
			int v=std::lower_bound(A+1,A+1+cnt,q[i].val)-A;
			q[i].val=v;
			if(!q[i].L) qid[q[i].pos]=i, ++sum[v];
			else vec[q[i].pos].pb(i);
		}
		for(int i=1; i<=cnt; ++i) sum[i]+=sum[i-1];	//ע��n,m,cnt���壡

		#define S 1,cnt,1
		T.now=1, T.Build(S);

		for(int i=1; i<=n; ++i)	//ö��R 
		{
			if(qid[i]) T.Update(i,qid[i],q[qid[i]].val);
			for(auto v:vec[i]) Query(v,cnt);
		}
		
		for(int i=1; i<=m; ++i) q[i].L && printf("%d\n",Ans[i]);
	}

	return 0;
}
