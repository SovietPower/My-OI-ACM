#include <cmath>
#include <queue>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define eps 0.1
typedef long long LL;
const int N=5e6+7;

int n,V,m;
LL sum1[N],sum2[N],sum3[N];//1~i/i~n选pos-1个的最小花费 
std::priority_queue<int> q1,q2;
struct Things
{
	int val,cost;
	bool operator <(const Things &x)const{
		return val<x.val;
	}
}t[N];
struct Segment_Tree
{
	#define lson rt<<1
	#define rson rt<<1|1
	LL mn[N<<2];
	#define Update(rt) mn[rt]=std::min(mn[lson],mn[rson])
	void Build(int l,int r,int rt)
	{
		if(l==r) mn[rt]=t[l].cost+sum3[l+1];//, printf("%d:%I64d\n",l,mn[rt]);
		else Build(l,l+r>>1,lson),Build((l+r>>1)+1,r,rson),Update(rt);
	}
	void Query(int l,int r,int rt,int i,LL val,int &pos)
	{
//		printf("Query:%d~%d mn:%I64d val:%I64d %d\n",l,r,mn[rt],val,pos);
		if(r<=i) return;
		if(l==r) {pos=l; return;}
		int m=l+r>>1;
		if(mn[rson]<=val) Query(m+1,r,rson,i,val,pos);
		else if(mn[lson]<=val) Query(l,m,lson,i,val,pos);
	}
}T;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline bool Check1(int p){
	return sum1[p-1]+sum2[p+1]+(LL)t[p].cost<=V;
}

int main()
{
	V=read(),n=read(),m=read();
	for(int i=1; i<=n; ++i) t[i].val=read(),t[i].cost=read();
	std::sort(t+1,t+1+n);

	int L=m>>1; if(m&1) ++L;
	LL now=0;
	for(int i=1; i<L; ++i) q1.push(t[i].cost), now+=t[i].cost;
	sum1[L-1]=now;
	int R=n-(m>>1);
	for(int i=L; i<=R; ++i)
	{
		if(!q1.empty() && t[i].cost<q1.top())
			now-=q1.top(), q1.pop(), q1.push(t[i].cost), now+=t[i].cost;
		sum1[i]=now;
	}

	now=0;
	for(int i=n,lim=R; i>lim; --i) q2.push(t[i].cost), now+=t[i].cost;
	sum2[R+1]=now;
	if(!q2.empty()) sum3[R+1]=now-q2.top();
	for(int i=R; i>=L; --i)
	{
		if(!q2.empty() && t[i].cost<q2.top())
			now-=q2.top(), q2.pop(), q2.push(t[i].cost), now+=t[i].cost;
		sum2[i]=now, sum3[i]=now-q2.top();
	}
//	for(int i=1; i<=n; ++i)
//		printf("%d:sum2:%I64d sum3:%I64d\n",i,sum2[i],sum3[i]);

	if(m&1)
	{
//		int l=L,r=R,mid,ans=L;//WA!
//		while(l<=r)
//		{
//			if(Check1(mid=l+r>>1)) ans=mid, l=mid+1;
//			else r=mid-1;
//		}
		int ans=L;
		for(int i=R; i>=L; --i) if(Check1(i)) {ans=i; break;}
		printf("%d\n",t[ans].val);
	}
	else
	{
		++R;
//		printf("\nL:%d R:%d\n",L,R);
		T.Build(L,R,1), t[0].val=-1e9;
		int ans=0, pos;
		for(int i=L; i<R; ++i)
		{
			if(sum1[i-1]+(LL)t[i].cost+sum2[i+1]>V) continue;
			pos=0, T.Query(L,R,1,i,V-sum1[i-1]-t[i].cost,pos);
//			printf("i:%d pos:%d\n",i,pos);
			ans=std::max(ans,(t[i].val+t[pos].val)>>1);
		}
		printf("%d\n",ans);
	}

	return 0;
}
