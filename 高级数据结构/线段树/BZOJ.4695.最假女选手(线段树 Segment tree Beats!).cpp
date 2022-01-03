/*
94908kb	47472ms
����ȡmax��min��ά�����������ͨ�߶����޷�����ġ�
���ڲ�������ά��������Сֵmn����Сֵ����t���ϸ��Сֵse��
��mn>=xʱ������Ҫ�ı䣬return��se>x>mnʱ��sum=sum+(x-mn)*t����������max��ǣ�
��x>=se>mnʱ���������������ݹ�ֱ������������䣬ֱ������ǰ���������
������ͬ��ά�����ֵ�����ֵ�������δ�ֵ��
���Ӷ�$O(m\log^2n)$��������Ϊ$O(mlogn)$��
�������޸�(max,min)��̫�����ˡ���
���磺ȡmin��ʱ�򲻽��Ǹ����ֵ����СֵҲ���ܸģ���Ȼ�ˡ���Ȼ������������ˣ���
���ֵ����min���Ҳһ���ģ����ֵ�����˵�ǰmin��Ǻ�ģ���
����max���Ҳ���ܸģ�ע����ȡmin������ֱ�Ӹ�ֵ�����мӷ�Ӱ�������ǣ�ԭ�ȵ����ֵ����һ�����������ǵõ��ģ���
����min,max���ܻ�ʹ�������Ϊͬһ����(��һ�仰�����)�������Ҫ����Ȼ���sum,��Сֵ,�δ�ֵ��ʼ������
�������mnû�и�mxһ���Ϊv(��һ�����)�����ǿ���mn<v<=se����Ҫ�ô�Сֵȡ��min��
���г���̫�󡣡����ǰ�min,max���ȥ����ֱ���ڸ��ڵ���£������ʺϵ�ʱ���´���-> 47s->40s.
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=5e5+5,INF=2e9;

char IN[MAXIN],*SS=IN,*TT=IN;
inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

struct Segment_Tree
{
	#define S N<<2
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,rt<<1
	#define rson m+1,r,rt<<1|1
	int mn[S],smn[S],tmn[S],mx[S],smx[S],tmx[S],sz[S],add[S],tagmn[S],tagmx[S];
	LL sum[S];
	#undef S
	inline void Update(int rt)
	{
		int l=ls,r=rs; sum[rt]=sum[l]+sum[r];
		if(mn[l]<mn[r]) mn[rt]=mn[l],smn[rt]=std::min(smn[l],mn[r]),tmn[rt]=tmn[l];
		else if(mn[l]>mn[r]) mn[rt]=mn[r],smn[rt]=std::min(smn[r],mn[l]),tmn[rt]=tmn[r];
		else mn[rt]=mn[l],smn[rt]=std::min(smn[l],smn[r]),tmn[rt]=tmn[l]+tmn[r];

		if(mx[l]>mx[r]) mx[rt]=mx[l],smx[rt]=std::max(smx[l],mx[r]),tmx[rt]=tmx[l];
		else if(mx[l]<mx[r]) mx[rt]=mx[r],smx[rt]=std::max(smx[r],mx[l]),tmx[rt]=tmx[r];
		else mx[rt]=mx[l],smx[rt]=std::max(smx[l],smx[r]),tmx[rt]=tmx[l]+tmx[r];
	}
	inline void Add(int x,int v)
	{
		add[x]+=v, mn[x]+=v, mx[x]+=v, sum[x]+=1ll*v*sz[x];
		if(smn[x]!=INF) smn[x]+=v;
		if(smx[x]!=-INF) smx[x]+=v;
		if(tagmn[x]!=INF) tagmn[x]+=v;
		if(tagmx[x]!=-INF) tagmx[x]+=v;
	}
	inline void Min(int x,int v)
	{
		if(v<mx[x])
		{
			sum[x]-=1ll*tmx[x]*(mx[x]-v);
			mx[x]=v, mn[x]=std::min(mn[x],v);//!
			tagmn[x]=v/*! ����Ҫ�����ֵС�ſ��ܣ���һ���ᣩ����min���*/,
			tagmx[x]=std::min(tagmx[x],v);//!
			if(mn[x]==mx[x]) sum[x]=1ll*sz[x]*v, tmn[x]=tmx[x]=sz[x], smn[x]=INF, smx[x]=-INF;//!
			else smn[x]=std::min(smn[x],v);//!
		}
	}
	inline void Max(int x,int v)
	{
		if(v>mn[x])
		{
			sum[x]+=1ll*tmn[x]*(v-mn[x]);
			mn[x]=v, mx[x]=std::max(mx[x],v);
			tagmx[x]=v, tagmn[x]=std::max(tagmn[x],v);
			if(mn[x]==mx[x]) sum[x]=1ll*sz[x]*v, tmn[x]=tmx[x]=sz[x], smn[x]=INF, smx[x]=-INF;
			else smx[x]=std::max(smx[x],v);
		}
	}
	void PushDown(int rt)
	{
		if(add[rt]) Add(ls,add[rt]), Add(rs,add[rt]), add[rt]=0;
		if(tagmn[rt]!=INF) Min(ls,tagmn[rt]), Min(rs,tagmn[rt]), tagmn[rt]=INF;
		if(tagmx[rt]!=-INF) Max(ls,tagmx[rt]), Max(rs,tagmx[rt]), tagmx[rt]=-INF;
	}
	void Build(int l,int r,int rt)
	{
		sz[rt]=r-l+1, tagmn[rt]=INF, tagmx[rt]=-INF;
		if(l==r)
		{
			tmn[rt]=tmx[rt]=1;
			sum[rt]=mn[rt]=mx[rt]=read(), smn[rt]=INF, smx[rt]=-INF;
			return;
		}
		Build(l,l+r>>1,ls), Build((l+r>>1)+1,r,rs);
		Update(rt);
	}
	void Modify_Add(int l,int r,int rt,int L,int R,int v)
	{
		if(L<=l && r<=R) {Add(rt,v); return;}
		PushDown(rt);
		int m=l+r>>1;
		if(L<=m) Modify_Add(lson,L,R,v);
		if(m<R) Modify_Add(rson,L,R,v);
		Update(rt);
	}
	void Modify_Max(int l,int r,int rt,int L,int R,int v)
	{
		if(mn[rt]>=v) return;
		if(L<=l && r<=R && smn[rt]>v) {Max(rt,v); return;}
		PushDown(rt);
		int m=l+r>>1;
		if(L<=m) Modify_Max(lson,L,R,v);
		if(m<R) Modify_Max(rson,L,R,v);
		Update(rt);
	}
	void Modify_Min(int l,int r,int rt,int L,int R,int v)
	{
		if(mx[rt]<=v) return;
		if(L<=l && r<=R && smx[rt]<v) {Min(rt,v); return;}
		PushDown(rt);
		int m=l+r>>1;
		if(L<=m) Modify_Min(lson,L,R,v);
		if(m<R) Modify_Min(rson,L,R,v);
		Update(rt);
	}
	int Query_Max(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) return mx[rt];
		PushDown(rt);
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return std::max(Query_Max(lson,L,R),Query_Max(rson,L,R));
			else return Query_Max(lson,L,R);
		else return Query_Max(rson,L,R);
	}
	int Query_Min(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) return mn[rt];
		PushDown(rt);
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return std::min(Query_Min(lson,L,R),Query_Min(rson,L,R));
			else return Query_Min(lson,L,R);
		else return Query_Min(rson,L,R);
	}
	LL Query_Sum(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) return sum[rt];
		PushDown(rt);
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return Query_Sum(lson,L,R)+Query_Sum(rson,L,R);
			else return Query_Sum(lson,L,R);
		else return Query_Sum(rson,L,R);
	}
}T;

int main()
{
	#define S 1,n,1
	int n=read(); T.Build(S);
	for(int m=read(),opt,l,r; m--; )
	{
		opt=read(),l=read(),r=read();
		if(opt==1) T.Modify_Add(S,l,r,read());
		else if(opt==2) T.Modify_Max(S,l,r,read());
		else if(opt==3) T.Modify_Min(S,l,r,read());
		else if(opt==4) printf("%lld\n",T.Query_Sum(S,l,r));
		else if(opt==5) printf("%d\n",T.Query_Max(S,l,r));
		else printf("%d\n",T.Query_Min(S,l,r));
	}
	#undef S
	return 0;
}
