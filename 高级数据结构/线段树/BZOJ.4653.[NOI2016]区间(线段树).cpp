/*
42136kb	8316ms
���Ƕ��֡���ô���ǿ��԰����䳤�ȴ�С����ö��ÿ�����䣬��ÿ��������Եõ�һ���������䳤�ȷ�Χ��
����Ҫ���Ƿ����һ���㱻��Щ���串������$m$�Ρ���������߶�������ӡ���maxά�����������߶����϶��֣���
����������$\log$�ġ�
���ǲ����֣�������ö��ÿ�����䡣������ö�ٱ���һ���Ƿ��е㱻����$m$�ξͺ��ˡ�
���Ӷ�$O(n\log n)$��
��̬����ֵ���߶���MLE 95�ְ�����
���⶯̬����������޸ģ��´���ǵ�ʱ��Ҫ������û�ж��ӣ�û��Ҫ�½��ڵ㣩��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=5e5+5;

int ref[N<<1];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Interval
{
	int l,r,len;
	Interval() {}
	Interval(int l,int r):l(l),r(r) {len=r-l;}
	bool operator <(const Interval &x)const
	{
		return len<x.len;
	}
}A[N];
struct Segment_Tree
{
	#define S N<<3
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson ls,l,m
	#define rson rs,m+1,r
	int tot,mx[S],tag[S];
	#undef S

	#define Update(x) mx[x]=std::max(mx[ls],mx[rs])
	#define Upd(x,v) tag[x]+=v,mx[x]+=v
	inline void PushDown(int rt)
	{
		Upd(ls,tag[rt]), Upd(rs,tag[rt]), tag[rt]=0;
	}
	void Modify(int rt,int l,int r,int L,int R,int val)
	{
		if(L<=l && r<=R) {Upd(rt,val); return;}
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		if(L<=m) Modify(lson,L,R,val);
		if(m<R) Modify(rson,L,R,val);
		Update(rt);
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int Find(int x,int r)
{
	int l=1,mid;
	while(l<r)
		if(ref[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}

int main()
{
	#define S 1,1,cnt

	int n=read(),m=read(),t=0;
	for(int i=1; i<=n; ++i) ref[++t]=read(),A[i]=Interval(ref[t-1],ref[++t]=read());
	std::sort(A+1,A+1+n);

	std::sort(ref+1,ref+1+t); int cnt=1;
	for(int i=2; i<=t; ++i) if(ref[i]!=ref[i-1]) ref[++cnt]=ref[i];
	for(int i=1; i<=n; ++i) A[i].l=Find(A[i].l,cnt), A[i].r=Find(A[i].r,cnt);

	int ans=2e9;
	for(int l=1,r=1; r<=n; ++r)
	{
		while(T.mx[1]<m && r<=n) T.Modify(S,A[r].l,A[r].r,1), ++r;
		--r;
		if(T.mx[1]>=m)
		{
			while(T.mx[1]>=m) T.Modify(S,A[l].l,A[l].r,-1), ++l;
			ans=std::min(ans,A[r].len-A[l-1].len);
		}
		else break;
	}
	printf("%d\n",ans==2e9?-1:ans);

	return 0;
}
