/*
13904K 532ms
��� ��״ �Ӷκ�������������������a1,a2,a3,a4,a5 
һ�������˵㶼ȡ����a4,a5,a1,a2���Ǿ����������ĺͼ�ȥ��ѡ�ģ������Լ����ܺͼ���С�����Ӷκ� 
���������˵㲻��ȡ����a1,a2,a3������Ҫ��¼��������Ӷκ� 
�߶�������maxs[l,r]Ϊ[l,r]����������Ӷκͣ�mins[l,r]ͬ�� 
�����ϸ���ʱ�����������������ҽڵ�ƴ�ɣ�Ҳ������ֻ������Ҹ��£�Ҳ�������ζ��У�������������/�Ҷ˵� 
���Ի���Ҫ��¼����������˵��maxsl,minsl�����������Ҷ˵��maxsr,minsr 
��PushUp��ת�ƾͺܺ�д�ˡ���PushUp 

��Ҫ��������Ӷκͣ����ܰ������е㣬Ҫ���У�
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
//#define gc() getchar()
#define gc() (SS==TT &&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define lson node[rt].ls
#define rson node[rt].rs
const int N=2e5+5,MAXIN=5e6;

int n;
char IN[MAXIN],*SS=IN,*TT=IN;
inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
struct Seg_Tree
{
	int tot;
	struct Node
	{
		int l,r,ls,rs,sum,maxs,mins,maxsl,maxsr,minsl,minsr;
		void Set(int v)
		{
			sum=maxs=mins=maxsl=maxsr=minsl=minsr=v;
		}
	}node[N<<1];
	inline void PushUp(int rt)
	{
		node[rt].sum=node[lson].sum+node[rson].sum;
		node[rt].maxs=std::max(std::max(node[lson].maxs,node[rson].maxs),node[lson].maxsr+node[rson].maxsl);
		node[rt].mins=std::min(std::min(node[lson].mins,node[rson].mins),node[lson].minsr+node[rson].minsl);
		node[rt].maxsl=std::max(node[lson].maxsl,node[lson].sum+node[rson].maxsl);
		node[rt].minsl=std::min(node[lson].minsl,node[lson].sum+node[rson].minsl);
		node[rt].maxsr=std::max(node[rson].maxsr,node[rson].sum+node[lson].maxsr);
		node[rt].minsr=std::min(node[rson].minsr,node[rson].sum+node[lson].minsr);
	}
	void Build(int l,int r)
	{
		int p=tot++;
		node[p].l=l, node[p].r=r;
		if(l==r)
		{
			node[p].ls=node[p].rs=-1;
			node[p].Set(read());
//			node[p].sum=node[p].maxs=node[p].mins=node[p].maxsl=node[p].minsl=node[p].maxsr=node[p].minsr=read();
			return;
		}
		int m=l+r>>1;
		node[p].ls=tot, Build(l,m);
		node[p].rs=tot, Build(m+1,r);
		PushUp(p);
	}
	void Modify(int rt,int pos,int v)
	{
		if(node[rt].l==node[rt].r){node[rt].Set(v); return;}
		int m=node[rt].l+node[rt].r>>1;
		if(pos<=m) Modify(lson,pos,v);
		else Modify(rson,pos,v);
		PushUp(rt);
	}
//	int Query_Max(int rt,int L,int R)
//	{
//		if(L<=node[rt].l && node[rt].r<=R) return node[rt].maxs;
//		int m=node[rt].l+node[rt].r>>1;
//		if(L<=m)
//			if(m<R) return std::max(Query_Max(lson,L,R),Query_Max(rson,L,R));
//			else Query_Max(lson,L,R);
//		return Query_Max(rson,L,R);
//	}
//	int Query_Min(int rt,int L,int R)
//	{
//		if(L<=node[rt].l && node[rt].r<=R) return node[rt].mins;
//		int m=node[rt].l+node[rt].r>>1;
//		if(L<=m)
//			if(m<R) return std::min(Query_Min(lson,L,R),Query_Min(rson,L,R));
//			else Query_Min(lson,L,R);
//		return Query_Min(rson,L,R);
//	}
}t;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("2750.in","r",stdin);
#endif

	n=read();
	t.Build(1,n);
	int m=read(),p,v;
	while(m--)
		p=read(),v=read(),t.Modify(0,p,v),
		printf("%d\n",t.node[0].sum==t.node[0].maxs? t.node[0].sum-t.node[0].mins : std::max(t.node[0].maxs,t.node[0].sum-t.node[0].mins));//ȫ��������Ҫ��ȥһ����Сֵ 
//		printf("%d\n",std::max(t.Query_Max(0,1,n),t.node[0].sum-t.Query_Min(0,1,n)));
//	printf("Max:%d Min:%d sum:%d\n",t.Query_Max(0,1,n),t.Query_Min(0,1,n),t.node[0].sum);

	return 0;
}
