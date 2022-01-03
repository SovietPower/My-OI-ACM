/*
299ms	6768kB
$Description$
��$n$����Ʒ��ÿ����ֵΪ$a_i$������Ҫ��ÿ����Ʒ�����ڵ�������Ʒ����Ϊһ�飬һ���ȨֵΪ������Ʒ��ֵ֮�ͣ�ÿ����Ʒ������ֻ����һ�飩��
�󻮷ֺ�������Ȩֵ-��СȨֵ����Сֵ��
$n\leq 10^5,\ \sum n\leq 10^6$��
$Solution$
���ֵ-��Сֵ������ö�٣�
����ֻ��$2n$�������Խ�$2n$���������򣬴�С����ö����Сֵ��
��$\min{\max}$��ʾ�����ֵ��Сʱ�����ֵ��ö����Сֵ����$i$��Ҫ��ʣ�µ����串��$1~n$��ʹ���ֵ��С������һ��$\min{\max}$��Ȼ�������$i$ɾ������������Ϊ���ֵ���䣩��
��򵥵���һ��$O(n)$DP�����Է�������һ��ÿ��ɾ��һ�����䣬�Ҵ������˳���޹أ����Ժϲ����䣩��DP���������߶���ά����
�߶���ÿ������ά���ĸ�ֵ��
$lmx$��������˵㵫�������Ҷ˵������$\min{\max}$��
$rmx$�������Ҷ˵㵫��������˵������$\min{\max}$��
$mx$�����Ҷ˵㶼������������$\min{\max}$��
$ans$���������Ҷ˵㣨���������䣩��$\min{\max}$��
�Ϳ��Ժϲ������ˣ���ʼ��������Ϊ$1$�����䣬�ϲ�����ʱҪ�õ�����Ϊ$2$�����䣩��
ɾ�������ʱ�����ֱ�ӽ����丳ֵΪ$INF$��һ������ȡ����
����һ�����ǣ����Ž������ֵ����Сֵ����һ�������ص�������n=1��2�������Կ���ֱ�Ӳ�ѯ������ɾ�����������������
PS: �����ʼ��ʱ�ó���Ϊ1,2������ٸ����ӣ�lmx,rmx�����ھ���-INF��ȡmax��Ӱ��𰸵�ȡֵ����mx���Ϸ�����INF������Ϊ1�����䲻����mx���£���
��С��������-2e9�������������Ϊ1e9������𰸹����п��ܱ�int����Ȼ���մ�int�ڣ���
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define mp std::make_pair
#define pr std::pair<int,int>
typedef long long LL;
const int N=1e5+5,INF=2e9+10;

int A[N],B[N];
pr Ref[N<<1];
struct Segment_Tree
{
	#define S N<<2
	int lmx[S],rmx[S],mx[S],ans[S];
	#undef S
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	inline void Update(int rt,int mid)//B:����Ϊ2������ B[mid]���Ǻϲ�ʱ�����ཻ�ε�ֵ��
	{
		int l=ls,r=rs;
		lmx[rt]=std::min(std::max(lmx[rs],ans[ls]),std::max(mx[rs],std::max(B[mid],lmx[ls])));
		rmx[rt]=std::min(std::max(rmx[ls],ans[rs]),std::max(mx[ls],std::max(B[mid],rmx[rs])));
		mx[rt]=std::min(std::max(rmx[ls],lmx[rs]),std::max(mx[ls],std::max(B[mid],mx[rs])));
		ans[rt]=std::min(std::max(ans[ls],ans[rs]),std::max(lmx[ls],std::max(B[mid],rmx[rs])));
	}
	void Build(int l,int r,int rt)
	{
		if(l==r)
		{
			lmx[rt]=-INF, rmx[rt]=-INF, mx[rt]=INF/*!*/, ans[rt]=A[l];
			return;
		}
		int m=l+r>>1;
		Build(lson), Build(rson), Update(rt,m);
	}
	void Modify(int l,int r,int rt,int p)
	{
		if(l==r)
		{
			ans[rt]=A[l];
			return;
		}
		int m=l+r>>1;
		p<=m ? Modify(lson,p) : Modify(rson,p);
		Update(rt,m);
	}
}T;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	for(int Ts=read(); Ts--; )
	{
		int n=read(),cnt=n+n-1;
		for(int i=1; i<=n; ++i) Ref[i]=mp(A[i]=read(),i);
		for(int i=1; i<n; ++i) Ref[i+n]=mp(B[i]=A[i]+A[i+1],i+n);
		std::sort(Ref+1,Ref+1+cnt);

		LL ans=1e14;
		T.Build(1,n,1);
		for(int i=1; i<=cnt && T.ans[1]!=INF; ++i)
		{
			ans=std::min(ans,1ll*T.ans[1]-Ref[i].first);
			int t=Ref[i].second;
			t<=n ? (A[t]=INF,T.Modify(1,n,1,t)) : (B[t-n]=INF,T.Modify(1,n,1,t-n));
		}
		printf("%lld\n",ans);
	}

	return 0;
}
/*
1 4
1000000000 1000000000 -1000000000 -1000000000
*/
