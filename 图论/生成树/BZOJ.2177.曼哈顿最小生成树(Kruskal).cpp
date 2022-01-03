/*
http://blog.csdn.net/huzecong/article/details/8576908
����ÿ���㣬��Ψһ�п��������γ�MST��8�������ߣ�������˫�򵥱ߣ�����ÿ�����������4���ߣ�֤����blog�� 
��ô�ҵ�һ������������ĵ㣿
ֻ����y���Ҳ�45����������ಿ�ֿ���ͨ������任�ƶ�����һ���� 
�赱ǰ��P(x0,y0),��һ����һ��P1(x1,y1)������x1>x0 && y1-x1>y0-x0 
��ôdis(AB)= y1-y0+x1-x0 = x1+y1-(x0+y0)
������һ������dis(AB)��С�ĵ㼴 ������֮ǰ�����ĵ��� x1+y1��С�ĵ� 
�ȶ�x����then������ֻ��ѯĳ����׺�����Զ�y-x��ɢ������״�����ҵ���С��x+y 
*/
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
#define lb(x) (x&-x)
#define gc() getchar()
#define dis(i,j) (std::abs(p[i].x-p[j].x)+std::abs(p[i].y-p[j].y))
const int N=5e4+5;

int n,Enum,fa[N],A[N],ref[N];
struct Point
{
	int x,y,id;
	inline bool operator <(const Point &a)const {return x==a.x?y<a.y:x<a.x;}
}p[N];
struct Bit_Tree
{
	int val[N],pos[N];
	inline void Init() {memset(val,0x7f,sizeof val);}
	void Update(int p,int v,int vp)
	{
		for(;p;p-=lb(p))
			if(val[p]>v) val[p]=v,pos[p]=vp;
	}
	int Query(int p,int n)
	{
		int mn=1<<30,res=-1;
		for(;p<=n;p+=lb(p))
			if(mn>val[p]) mn=val[p],res=pos[p];
		return res;
	}
}t;
struct Edge
{
	int to,fr,val;
	inline bool operator <(const Edge &a)const {return val<a.val;}
}e[N<<2];

inline void AddEdge(int u,int v,int w)
{
	e[++Enum].to=v, e[Enum].fr=u, e[Enum].val=w;
}
inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
int Getf(int x)
{
	return x==fa[x]?x:fa[x]=Getf(fa[x]);
}
int MST()
{
	for(int dir=0;dir<4;++dir)//����任 
	{//Time1.���� 
		if(dir==1||dir==3)
			for(int i=1;i<=n;++i) std::swap(p[i].x,p[i].y);//T2.T4.����y=x�Գ� 
		else if(dir==2)
			for(int i=1;i<=n;++i) p[i].x=-p[i].x;//T3.����x=0�Գ� 
		std::sort(p+1,p+1+n);
		t.Init();
		for(int i=1;i<=n;++i) A[i]=ref[i]=p[i].y-p[i].x;
		std::sort(A+1,A+1+n);
		int m=1; ref[1]=A[1];
		for(int i=2;i<=n;++i)
			if(A[i]!=A[i-1]) ref[++m]=A[i];
		for(int pos,res,i=n;i;--i)
		{
			pos=std::lower_bound(ref+1,ref+1+m,p[i].y-p[i].x)-ref;
			if((res=t.Query(pos,m))!=-1) AddEdge(p[i].id,p[res].id,dis(i,res));
			t.Update(pos,p[i].x+p[i].y,i);
		}
	}
	std::sort(e+1,e+1+Enum);
	for(int i=1;i<=n;++i) fa[i]=i;
	int res=0;
	for(int r1,r2,i=1,k=0;i<=Enum;++i)
	{
		r1=Getf(e[i].fr),r2=Getf(e[i].to);
		if(r1!=r2)
		{
			res+=e[i].val, fa[r1]=r2;
			if(++k==n-1) break;
		}
	}
	return res;
}

int main()
{
	n=read();
	for(int i=1;i<=n;++i) p[i].x=read(),p[i].y=read(),p[i].id=i;
	printf("%d",MST());
	return 0;
}
