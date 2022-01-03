/*
904MS	3148K
$Description$
$n*m$�����ڸ���$k$�����ߣ�������ڻ��ֳɵ���ͨ������
$Solution$
һ���ܿ������Ľ��ۣ���ͨ����=������+1.
֤������ŷ����ʽ/����������R+����V-����E=2.
�����߼佻����Ϊ$c$�����ܱ���Ϊ$4+������n+��������ν������n+���߽������2c$
�ܶ�����Ϊ$4+���߱���n+������ཻ����n+c$���κ�һ�������һ�����㣩
��������������$R=2+4+2n+2c-4-n-n-c=c+2$��������Ҳ��һ���������Դ�Ϊ$c+1$��

�󽻵��������ܶࡣ
**Sol1:**
����ֱ���µ����ߺ�ˮƽ�����߰�$y$���򣬰�˳��ö�٣�����$x$����״���顣ˮƽ���߾�����������һ������״����ǰ׺���׺+1����ֱ���߾Ͳ�һ�µ����ֵ��
Ȼ���ٶԴ�ֱ���ϵ�������һ���ok�ˡ�
**Sol2:**
���������߰�$y$���򣬰�˳��ö�٣�����$x$����״���顣��ֱ���߳���ʱ������״���鵥��+1����ʧʱ����-1��ˮƽ���߾Ͳ�һ��ǰ׺���׺�����ֵ����׺���ǵ�ǰ��ֱ��������-ǰ׺�ģ���
����Sol1һ���ģ������ô�ֱ�����޸�ֻ��Ҫһ�顣��״������$x$����$y$Ҳ��һ���ģ����������޸Ļ��ǵ����޸ĵ����𣩣�
**Sol3:**
�������µ�����$(xi,yi)$�������������$(xj,yj)$������$xj>xi$��$yj<yi$�����߸����������ҵ�����$(xj,yj)$������$xj<xi$��$yj<yi$�����߸�����
�������ϵ����ߣ���תһ��$y$�����ˮƽ���ߵķ�������һ�Ρ�
Ȼ�������̾��Ƕ�λƫ������+��״���鼴�ɡ�

����Ϊ$Sol2$������Ҫ$2k$����״���飩��
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5;

int A[N];
struct Segment
{
	int type,x,y;//0:U 1:D 2:L 3:R
	bool operator <(const Segment &s)const
	{
		return y<s.y;
	}
}seg[N];
struct BIT
{
	int n,t[N];
	#define lb(x) (x&-(x))
	void Add(int p)
	{
		for(; p<=n; p+=lb(p)) ++t[p];
	}
	void Delete(int p)
	{
		for(; p<=n; p+=lb(p)) --t[p];
	}
	int Query(int p)
	{
		int res=0;
		for(; p; p^=lb(p)) res+=t[p];
		return res;
	}
}T;

inline int read()
{
	int now=0; char c=gc();
	for(; !isdigit(c); c=gc());
	for(; isdigit(c); now=now*10+c-48,c=gc());
	return now;
}
inline int Get()
{//0:U 1:D 2:L 3:R
	char c=gc(); for(; !isalpha(c); c=gc());
	return c=='U'?0:c=='D'?1:c=='L'?2:3;
}
inline int Find(int r,int x)
{
	int l=1,mid;
	while(l<r)
		if(A[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}

int main()
{
	for(int Case=read(); Case--; )
	{
		int L=read(),R=read(),n=read();
		for(int i=1,x,y; i<=n; ++i)
			A[i]=x=read(), y=read(), seg[i]=(Segment){Get(),x,y};
		std::sort(A+1,A+1+n);
		int cnt=1;
		for(int i=2; i<=n; ++i) if(A[i]!=A[i-1]) A[++cnt]=A[i];
		for(int i=1; i<=n; ++i) seg[i].x=Find(cnt,seg[i].x);
		std::sort(seg+1,seg+1+n);

		int ans=1,sum=0; T.n=cnt;
		for(int i=1; i<=n; ++i) seg[i].type==1&&(T.Add(seg[i].x),++sum);
		for(int i=1; i<=n; ++i)
			switch(seg[i].type)
			{
				case 0: ++sum, T.Add(seg[i].x); break;
				case 1: --sum, T.Delete(seg[i].x); break;
				case 2: ans+=T.Query(seg[i].x); break;
				case 3: ans+=sum-T.Query(seg[i].x-1); break;
			}
		for(int i=1; i<=n; ++i) seg[i].type==0&&(T.Delete(seg[i].x),0);
		printf("%d\n",ans);
	}

	return 0;
}
