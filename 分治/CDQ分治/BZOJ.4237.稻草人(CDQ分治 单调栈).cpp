/*
7368kb	3696ms
$Description$
ƽ������$n$������㣬���ж��ٸ����Σ����������½ǡ����Ͻ�Ϊ����㣬���ڲ��������߽磩û������㡣
$n\leq 2\times10^5$��
$Solution$
���Ƿ��Σ�����һά��
�����е㰴$y$����Ȼ������ƽ����x����һ������ƽ��ֳ����������֣����������²����Ĵ𰸣������Ͻ����ϰ벿�֣����½����°벿�֣���
Ȼ�����Ƕ����������ֵ�ֱ�$x$����
����ĵ������ǰ��$x,y$������С�ĵ��Ӱ�졣���Զ��ϰ벿��������Ҫά��$y_j$�ȵ�ǰС������$x_j$�������õ���ջ��
���°벿�ֵĵ�Ҳ�ụ��Ӱ�죬���Ƿ��ֿ��е��$y$�ݼ������Ƕ��п��ܣ���������ĳ��Ӱ�죩��Ϊ�𰸡�
ͬ��ά������ջ�������ϰ벿���ڵ����ƣ��ڵ���ջ�ж���һ��λ�þͺ��ˡ�
ÿ��CDQsort����̫�����ˡ���Ȼ�ɹ������ǳ�������(��ֹһ��:5800kb 15748ms)��
�Ȱ�x����Ȼ��CDQʱ��y�鲢���򣬷ֳ������֡�������ͬһ���ֵĵ�һ�����ǰ�x�ź���ġ�Ȼ����δ���ͬһ���ֵĵ㡣�������������ҷָ��λ�ã�Ҫ��ɢ�������꣬l,r��ʾy�����䡣
���߿����Ȱ�y���򣬴����������������ֵ㰴x�鲢����������ͬһ���ֵĵ��x������ģ�ͬʱҲ��֤ǰһ���ֵ�y���Ⱥ�һ���ֵ�yС��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=2e5+5;

long long Ans;
char IN[MAXIN],*SS=IN,*TT=IN;
struct Point
{
	int x,y;
}p[N],tmp[N],sk1[N],sk2[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline bool cmpx(const Point &a,const Point &b)
{
	return a.x<b.x;
}
inline bool cmpy(const Point &a,const Point &b)
{
	return a.y<b.y;
}
void CDQ(int l,int r)
{
	if(l==r) return;
	int mid=l+r>>1;
	CDQ(l,mid), CDQ(mid+1,r);

	for(int now=l,top1=0,top2=0,i=mid+1; i<=r; ++i)
	{
		int xn=p[i].x,yn=p[i].y;
		while(top1 && sk1[top1].y>=yn) --top1;
		sk1[++top1]=p[i];

		while(now<=mid && p[now].x<xn)
		{
			int yy=p[now].y;
			while(top2 && sk2[top2].y<=yy) --top2;//��ʵ��Ŀ�ѱ�֤yi������ͬ...
			sk2[++top2]=p[now], ++now;
		}

		int xx=sk1[top1-1].x,L=1,R=top2,M,res=top2+1;
		while(L<=R)
		{
			if(sk2[M=L+R>>1].x>=xx) res=M, R=M-1;//not mid...
			else L=M+1;
		}
		Ans+=top2-res+1;
	}
	for(int i=l,a=l,b=mid+1; i<=r; ++i)
		tmp[i]=((a<=mid&&p[a].x<p[b].x)||b>r)?p[a++]:p[b++];
	for(int i=l; i<=r; ++i) p[i]=tmp[i];
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) p[i]=(Point){read(),read()};
	std::sort(p+1,p+1+n,cmpy);
	sk1[0].x=sk2[0].x=-1, CDQ(1,n), printf("%lld\n",Ans);

	return 0;
}
