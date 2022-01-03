/*
10496kb	888ms(Rank1!)
$Description$
��n����Ҫһ��һ��Բ�����飨���Ϊ$0\sim n-1$���������Բ������m��λ�ã����Ϊ$0\sim m-1$����ÿ������ai���ˣ�������Ҫ�������ڣ�li��(li+1)%m��(li+2)%m������ri������λ��Χ�ڡ�ÿ����λֻ�ܰ���һ���˾���������ÿ���˶���Ҫ������һ����λ���ж��Ƿ����������������λ���š�
$n\leq 10^5,\ m\leq 10^9$��
$Solution$
�ȿ���������Ŀ�൱�����Ƿ�����걸ƥ�䡣��ô��Hall������������һ������[L,R]����Ҫ����[li,ri]��ȫ��[L,R]�е�ai֮��sumС�ڵ�����λ��������R-L+1������ʵ�ò���Hall������Ȼ��
Ϊʲô�����Ӽ��أ���Ϊ���䲢���Ӽ��ȼۣ��������䲢����Ҫ��֤�ġ�
���ҿ��Է��֣�ֻ�е�RΪĳ��r[i]��LΪĳ��l[j]ʱ��[L,R]���б�Ҫ��֤��
�������ǽ����䰴r[]����ö��ÿ��r[i]��ΪR����������Ϊsum<=R-L+1��sum+L-1<=R������ǰ������λ�ã���L��[1,R]�����ǿ���ֱ�����߶���ά��ÿ��λ�õ�sum+L-1����ѯ���ֵ�Ϳ����ˡ�
ÿ��ö�ٵ�i����ʹL��[1,l[i]]ʱ+ai���������Ӿ����ˡ�
���ڻ�����Ϊ���Ϳ����ˡ�
�����и����⣬����m=5,([1,3],2),([3,2],3)����ֳ�����[1,3],[3,7],[6,8]��[3,2]ʵ���ǰ���[1,3]�ģ�����[1,3]���ֳ���[3,3]��[6,7]������a�Ͳ���ͼ����ˡ�
��Ϊr=l-1ʱ����Ϊm�������һ��[l,r]�븴�Ƴ�����[l+m,r+m]�ָ�����¶���������[r,l-1]�ڡ�
��Ϊ��Щ���䳤�ȶ�Ϊm������ֻ��Ҫ����һ���������伴�ɡ�
r[]����Ҫ��ɢ��������ע������ref[r]�Ƚϡ���
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=2e5+5;

int n,m,ref[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Opt
{
	int l,r,a;
	Opt() {}
	Opt(int l,int r,int a):l(l),r(r),a(a) {}
	bool operator <(const Opt &x)const{
		return r<x.r;
	}
}q[N];
struct Segment_Tree
{
	#define lson rt<<1
	#define rson rt<<1|1
	#define ToL l,m,rt<<1
	#define ToR m+1,r,rt<<1|1
	int mx[N<<2],tag[N<<2];

	#define Update(rt) mx[rt]=std::max(mx[lson],mx[rson])
//	#define Add(rt,v) mx[rt]+=v, tag[rt]+=v
//	#define PushDown(rt) Add(lson,tag[rt]), Add(rson,tag[rt]), tag[rt]=0
	inline void Add(int rt,int v){
		mx[rt]+=v, tag[rt]+=v;
	}
	void PushDown(int rt){
		Add(lson,tag[rt]), Add(rson,tag[rt]), tag[rt]=0;
	}
	void Build(int l,int r,int rt)
	{
		tag[rt]=0;
		if(l==r) mx[rt]=ref[l]-1;//ref!
		else Build(l,l+r>>1,lson), Build((l+r>>1)+1,r,rson), Update(rt);
	}
	void Modify(int l,int r,int rt,int L,int R,int v)
	{
		if(L<=l && r<=R) {Add(rt,v); return;}
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		if(L<=m) Modify(ToL,L,R,v);
		if(m<R) Modify(ToR,L,R,v);
		Update(rt);
	}
	int Query(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) return mx[rt];
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return std::max(Query(ToL,L,R),Query(ToR,L,R));
			else return Query(ToL,L,R);
		return Query(ToR,L,R);
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
	int Case=read();
	while(Case--)
	{
		n=read(),m=read(); int Q=0,t=0; long long sum=0;
		for(int i=1,l,r,a; i<=n; ++i)
		{
			ref[++t]=l=read(),r=read(),sum+=(a=read());
			if(l<=r) q[++Q]=Opt(l,r,a), q[++Q]=Opt(l+m,r+m,a), ref[++t]=l+m/*!*/;
			else q[++Q]=Opt(l,r+m,a);
		}
		if(sum>m) {puts("No"); continue;}
		std::sort(q+1,q+1+Q);
		std::sort(ref+1,ref+1+t); int cnt=1;
		for(int i=2; i<=t; ++i) if(ref[i]!=ref[i-1]) ref[++cnt]=ref[i];
		for(int i=1; i<=Q; ++i) q[i].l=Find(q[i].l,cnt);//, q[i].r=Find(q[i].r,cnt);
		n=cnt, T.Build(1,n,1);
		bool f=1;
		for(int i=1; i<=Q; ++i)
		{
			T.Modify(1,n,1,1,q[i].l,q[i].a);
			if(T.Query(1,n,1,1,q[i].l/*l��?��r������ɢ��...*/)>q[i].r) {f=0; break;}//ref[r]
		}
		puts(f?"Yes":"No");
	}
	return 0;
}
