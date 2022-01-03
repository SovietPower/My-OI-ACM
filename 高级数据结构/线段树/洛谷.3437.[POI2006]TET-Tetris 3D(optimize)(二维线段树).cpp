/*
3624ms 91035KB
����һ��d*s�ķ��飬��Ҫ�����ƽ��������һ����ߵ�h' 
��������ƽ�������ֵΪh+h' 

���ڱ��⣬ά�����߶�h��all 
����ƽ���x��ά��һ���߶���t1��ÿ��t1�Ľڵ�ά����Ӧy��������߶���t2(h��all)
(ͬһά����Ҫά�������������߶���)
t1Ҫ�ñ�����û�ʵ�֣�t2��ͨ�ͱ�����û������� 
�ռ�O(n^2) ʱ��O(n*(logn)^2) 

������û�: 
����������(��ά�߶���)��˵������´�(PushDown)����Ϣ�ϴ�(PushUp)�ͺ���ʵ���� 
��ʱ�õ�������û� 
д��ͨ�߶���ʱ�����޸�������ǣ�����Ҫ��ʱ���·ű�ǲ����� 
�ǿɲ����Բ��Ա�ǽ����·ţ����Ǿ�����ʱ��ͳ�Ʊ�ǶԴ𰸵Ĺ��ף��Ӷ�ʡȥ����·Ź��̣�
������ӡ����Ϊ�������߶���ÿ���ڵ�ά��sum,all���ֱ��ʾ�ýڵ��������ĺͣ���ýڵ�������������䶼�еı��all 
����ʱ��һ·���¾����ڵ��sumֵ��ֱ����ǰ�ڵ�������ȫ��Ŀ�����串�ǣ����¸ýڵ��all��return (˳���޸ľ�ʡȥ��PushUp)
��ѯʱ ���෴��һ·ͳ�ƾ����ڵ��allֵ��ֱ����ǰ�ڵ�������ȫ��Ŀ�����串�ǣ��øýڵ��sum���´� 

ע:������θ߶�ֻ��Խ��Խ�ߣ�������Ϣ�ϴ�ʱ����Ҫ�õ����Ҷ��ӵ���Ϣ��ʹ�ñ�����û��Ͳ��������� 
���𰸲����ǵ����ģ���ô���´�ʱ�ͻ�������⣬��Ϊ����֪����Ǵ��ϵ�˳����˭��ǰ˭�ں� 
���ұ���Ҫȡ���ֵ������ֱ�Ӹ��� 
��̫����...
��ʼΪ0�Ĳ�����Ҫ���� 
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
//#define gc() getchar()
#define gc() (SS==TT &&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define lson rt<<1,l,m
#define rson rt<<1|1,m+1,r
const int N=1002*3,MAXIN=5e6;

int n,m;
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
	int maxh[N],all[N];
	void Modify(int rt,int l,int r,int L,int R,int v)
	{
		maxh[rt]=std::max(maxh[rt],v);
		if(L<=l && r<=R)
		{
			all[rt]=std::max(all[rt],v);
			return;
		}
		int m=l+r>>1;
		if(L<=m) Modify(lson,L,R,v);
		if(m<R) Modify(rson,L,R,v);
	}
	int Query(int rt,int l,int r,int L,int R)
	{
		if(L<=l && r<=R) return maxh[rt];
		int res=all[rt],m=l+r>>1;
		if(L<=m) res=std::max(res,Query(lson,L,R));
		if(m<R) res=std::max(res,Query(rson,L,R));
		return res;
	}
};
struct Seg_Tree2D
{
	Seg_Tree maxh[N],all[N];
	void Modify(int rt,int l,int r,int L,int R,int y1,int y2,int v)
	{
		maxh[rt].Modify(1,1,m,y1,y2,v);
		if(L<=l && r<=R)
		{
			all[rt].Modify(1,1,m,y1,y2,v);
			return;
		}
		int m=l+r>>1;
		if(L<=m) Modify(lson,L,R,y1,y2,v);
		if(m<R) Modify(rson,L,R,y1,y2,v);
	}
	int Query(int rt,int l,int r,int L,int R,int y1,int y2)
	{
		if(L<=l && r<=R) return maxh[rt].Query(1,1,m,y1,y2);
		int res=all[rt].Query(1,1,m,y1,y2),m=l+r>>1;
		if(L<=m) res=std::max(res,Query(lson,L,R,y1,y2));//����(lson,L,m)![L,m]�ǲ�ѯ���� 
		if(m<R) res=std::max(res,Query(rson,L,R,y1,y2));
		return res;
	}
}t;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("3437.in","r",stdin);
#endif

	n=read(),m=read();
	int q=read(),x,y,d,s,h,tmp,x2,y2;
	while(q--)
	{
		d=read(),s=read(),h=read(),x=read()+1,y=read()+1;
		x2=x+d-1, y2=y+s-1;
		tmp=t.Query(1,1,n,x,x2,y,y2);
		t.Modify(1,1,n,x,x2,y,y2,h+tmp);
	}
	printf("%d",t.Query(1,1,n,1,n,1,m));

	return 0;
}
