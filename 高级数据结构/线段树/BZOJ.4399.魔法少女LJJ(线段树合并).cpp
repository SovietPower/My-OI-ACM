/*
162076kb	6560ms
$Description$
$m$��$7$�ֲ������½�ȨֵΪ$x$�ĵ㣻�ϲ�����������ͨ�飻ѯ����ͨ���С���������е��Ȩֵ������$k$СȨֵ����ĳ��ͨ�����е��ֵ��$x$ȡ$\min$��$\max$��
$m\leq4\times10^5$��
$Solution$
ע��$c\leq7$��_��
Ȼ��������Ȩֵ�߶���+�߶����ϲ��ˡ�
����ȡ$\max/\min$��������ֱ�������޸���ճ�����Χ��ֵ��Ȼ����µ���Ӧλ���Ͼ����ˣ������$v$ȡ$\max$����$\lt v$����ȫɾ����ͳ��һ�¸���$num$��Ȼ����$v$������$num$��$v$���ɣ���
ֵ��ܴ�ֱ��ά������˻���ը��ֻ��ȡ������
��û�������ɢ��һ�¡�
���Ӷ�$O(m\log V)$��
ע���߶����ϲ�`Merge`��ʱ��Ҫд`Update/PushUp`...���Ҿ�Ȼ�ǵ�һ����ʶ��������⣩
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=4e5+5;

int cnt,fa[N],ref[N],root[N];
double Log[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Quries{
	int opt,x,y;
}q[N];
struct Segment_Tree
{
	#define ls son[x][0]
	#define rs son[x][1]
	#define lson ls,l,m
	#define rson rs,m+1,r
	#define S N*19
	int tot,sz[S],son[S][2];
	double mul[S];
	#undef S
	#define Update(x) sz[x]=sz[ls]+sz[rs], mul[x]=mul[ls]+mul[rs]
	void Insert(int &x,int l,int r,int p,double v)
	{
		sz[x=++tot]=1, mul[tot]=v;
		if(l==r) return;
		int m=l+r>>1;
		p<=m ? Insert(lson,p,v) : Insert(rson,p,v);
	}
	int Merge(int x,int y)
	{
		if(!x||!y) return x|y;
		ls=Merge(ls,son[y][0]), rs=Merge(rs,son[y][1]);
		sz[x]+=sz[y], mul[x]+=mul[y]; return x;//��ҪдUpdate(x)��
	}
	int FindPre(int &x,int l,int r,int R)
	{
		if(!x) return 0;
		if(r<=R)
		{
			int tmp=sz[x]; x=0;
			return tmp;
		}
		int m=l+r>>1,res=FindPre(lson,R)+(m<R?FindPre(rson,R):0);
		Update(x); return res;
	}
	int FindSuf(int &x,int l,int r,int L)
	{
		if(!x) return 0;
		if(L<=l)
		{
			int tmp=sz[x]; x=0;
			return tmp;
		}
		int m=l+r>>1,res=FindSuf(rson,L)+(L<=m?FindSuf(lson,L):0);
		Update(x); return res;
	}
	void Modify(int &x,int l,int r,int p,int num,double v)
	{
		if(!x) x=++tot;
		sz[x]+=num, mul[x]+=v;
		if(l==r) return;
		int m=l+r>>1;
		p<=m ? Modify(lson,p,num,v) : Modify(rson,p,num,v);
	}
	int Kth(int x,int l,int r,int k)
	{
		if(l==r) return ref[l];
		int m=l+r>>1;
		return sz[ls]<k?Kth(rson,k-sz[ls]):Kth(lson,k);
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
int Getfa(int x)
{
	return x==fa[x]?x:fa[x]=Getfa(fa[x]);
}
inline int Find(int x)
{
	int l=1,r=cnt,mid;
	while(l<r)
		if(ref[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}

int main()
{
	const int m=read();
	int cnt=0;
	for(int i=1,opt; i<=m; ++i)
	{
		q[i].opt=opt=read(), q[i].x=read();
		if(opt!=1 && opt!=7) q[i].y=read();
		if(opt==1||opt==3||opt==4) ref[++cnt]=opt==1?q[i].x:q[i].y;
	}
	std::sort(ref+1,ref+1+cnt);
	for(int tmp=cnt,i=(cnt=1,2); i<=tmp; ++i) if(ref[i]!=ref[i-1]) ref[++cnt]=ref[i];
	::cnt=cnt;
	for(int i=1; i<=cnt; ++i) Log[i]=log(ref[i]);

	for(int i=1,tot=0; i<=m; ++i)
		switch(q[i].opt)
		{
			case 1:
			{
				++tot, fa[tot]=tot; int p=Find(q[i].x);
				T.Insert(root[tot],1,cnt,p,Log[p]); break;
			}
			case 2:
			{
				int r1=Getfa(q[i].x), r2=Getfa(q[i].y);
				if(r1!=r2) root[r1]=T.Merge(root[r1],root[r2]), fa[r2]=r1;
				break;
			}
			case 3:
			{
				int rt=Getfa(q[i].x), p=Find(q[i].y), num=T.FindPre(root[rt],1,cnt,p);
				T.Modify(root[rt],1,cnt,p,num,Log[p]*num); break;
			}
			case 4:
			{
				int rt=Getfa(q[i].x), p=Find(q[i].y), num=T.FindSuf(root[rt],1,cnt,p);
				T.Modify(root[rt],1,cnt,p,num,Log[p]*num); break;
			}
			case 5: printf("%d\n",T.Kth(root[Getfa(q[i].x)],1,cnt,q[i].y)); break;
			case 6: puts(T.mul[root[Getfa(q[i].x)]]>T.mul[root[Getfa(q[i].y)]]?"1":"0"); break;
			case 7: printf("%d\n",T.sz[root[Getfa(q[i].x)]]); break;
		}

	return 0;
}
