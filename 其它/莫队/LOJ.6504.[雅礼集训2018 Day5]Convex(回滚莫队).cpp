/*
6527ms	8292K
Ī�ӡ�����ֻ��Ҫά��ǰ����̾Ϳ����ˡ�
���Ǽ���һ������Ҫ�ҵ�����ǰ��ǰ����̣����鷳������$\log$��
�������ֻ��ɾ��ĳ���㣬ֻ��Ҫ����һ������ǰ����̼��ɡ�
�ûع�Ī�Ӿͺ��ǡ�
�����������¼����ʱ����˳���ÿ�����ǰ����̸Ļ������ɡ�

����Ҫ��б��=-=
`atan2(y,x)`�����ص�$(x,y)$��$x$��������ļнǡ�
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=150005;

int bel[N],L[N],R[N],A[N];
LL Now,Ans[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Quries
{
	int l,r,id;
	bool operator <(const Quries &x)const
	{
		return bel[l]==bel[x.l]?r>x.r:l<x.l;
	}
}q[N];
struct Vec
{
	int x,y; double k;
	Vec(int y=0,int x=0):x(x),y(y) {k=atan2(y,x);}//x,y�����˵���Сʱ=-= 
	LL operator *(const Vec &a)const {return 1ll*x*a.y-1ll*y*a.x;}
}p[N];
typedef Vec Point;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline bool cmp(int a,int b)
{
	return p[a].k<p[b].k;
}
void Add(int x)
{
	int l=L[x],r=R[x];
	R[l]=x, L[r]=x;
}
void Delete(int x)
{
	int l=L[x],r=R[x];
	Now+=p[l]*p[r]-p[l]*p[x]-p[x]*p[r], R[l]=r, L[r]=l;
}

int main()
{
	const int n=read(),Q=read(),size=sqrt(n);
	for(int i=1; i<=n; ++i) p[i]=Point(read(),read()),bel[i]=(i-1)/size+1,A[i]=i;
	std::sort(A+1,A+1+n,cmp);
	for(int i=1; i<=Q; ++i) q[i]=(Quries){read(),read(),i};
	std::sort(q+1,q+1+Q);
	for(int i=1,now=1; i<=bel[n]&&now<=Q; ++i)
	{
		if(bel[q[now].l]!=i) continue;
		int Ln=(i-1)*size+1,l=Ln,r=n,las=0,beg=0;
		Now=0;
		for(int j=1,pos; j<=n; ++j)
			if(A[j]>=Ln)
			{
				pos=A[j];
				if(las) Now+=p[las]*p[pos], L[pos]=las, R[las]=pos, las=pos;
				else beg=las=pos;
			}
		R[las]=beg, L[beg]=las, Now+=p[las]*p[beg];
		while(bel[q[now].l]==i)
		{
			while(r>q[now].r) Delete(r--);
			LL tmp=Now;
			while(l<q[now].l) Delete(l++);
			Ans[q[now++].id]=Now, Now=tmp;
			while(l>Ln) Add(--l);
		}
	}
	for(int i=1; i<=Q; printf("%lld\n",Ans[i++]));

	return 0;
}
