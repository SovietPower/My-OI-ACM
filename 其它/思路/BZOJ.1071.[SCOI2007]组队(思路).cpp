/*
976kb	2392ms
�������ƣ�
$Ah-AminH+Bv-BminV\leq C\to Ah+Bv\leq C+AminH+BminV$
$v\geq minV$
$h\geq minH$
��$s=Ah+Bv$�������а�$s$��С��������
$n^2$ö��$minV,minH$������̶�$minV$����С����ö��$minH$ʱ������$s\leq C+AminH+BminV$��λ���ǵ����ġ�ͳ�ƴ�ʱ������һ���Ƿ�����$v_i\geq minV$��
������$h_i\geq minH$�����ơ���Ϊ$minH$�ǵ����ģ�֮ǰ���������ĺ������ܲ����㡣��һ����ά��֮ǰ�������С��$h_i$���ɣ������������͵�����
����$O(n^2\log n)$����ȥ��

����������ô����$h_i\geq minH$����$h$����Ȼ��$<minH$�Ķ���������Ȼ������һЩ��������������������δ��ͳ�Ƶġ�
�ٹ۲�һ�����ƣ���$h,v$�ֿ���$A(h-minH)\leq C+B(minV-v)$��
��Ȼ��ʽ����$\geq0$����ôҲ��$0\leq C+B(minV-v)\to minV\leq v\leq \frac CB+minV$��
�������$v$���ܹ���ʹ��$h$��С��
$v\leq\frac CB+minV$ʱ������һ�ͳ���$A(h-minH)+(\leq C��ֵ)\leq C$����$h\leq minH$����Ȼ�������$s$�����ơ�
�����$s$����������$minV\leq v\leq \frac CB+minV$ʱ$ans$++������һ���Ծ����㡣
���$h<minH$��$minV\leq v\leq \frac CB+minV$��������˵��ʱҲ����$s$�����ƣ����Դ�ʱ$ans$--�����ľ�һ����֮ǰͳ�ƹ����ˡ����ԾͿ����������ز�©��orz��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=5005;

struct Node
{
	int h,v; LL s;
}a[N],b[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline bool cmps(const Node &a,const Node &b)
{
	return a.s<b.s;
}
inline bool cmph(const Node &a,const Node &b)
{
	return a.h<b.h;
}

int main()
{
	int n=read(),A=read(),B=read(),C=read();
	for(int i=1; i<=n; ++i) a[i].h=read(), a[i].v=read(), a[i].s=1ll*A*a[i].h+1ll*B*a[i].v, b[i]=a[i];
	std::sort(a+1,a+1+n,cmps);
	std::sort(b+1,b+1+n,cmph);
	int ans=0; a[n+1].s=1e18, b[n+1].h=0x7fffffff;
	for(int i=1,CdivB=C/B; i<=n; ++i)
	{//ö��minv 
		int mnv=a[i].v; LL mxv=CdivB+mnv,tmp=C+1ll*B*mnv;
		for(int j=1,l=1,r=1,cnt=0; j<=n; ++j)
		{//�Ǵ�С����ö�ٵ�minh����_�� 
			while(a[r].s<=tmp+1ll*A*b[j].h)
				cnt+=(a[r].v>=mnv && a[r].v<=mxv), ++r;
			while(b[l].h<b[j].h)
				cnt-=(b[l].v>=mnv && b[l].v<=mxv), ++l;
			ans=std::max(ans,cnt);
		}
	}
	printf("%d\n",ans);

	return 0;
}
