/*
$Description$
��һ����Ϊ$n$�����У�����������Ԫ��Ϊ$y$������ȫΪ$x$������Խ���$19$��ѯ�ʣ�ÿ��ѯ�������һ���±꼯�ϣ�������᷵����ЩԪ�ص����͡�����$n,x,y$������Ҫ�������$y$���±ꡣ
$n\leq 1000,1\leq x,y\leq 10^9$��
$Solution$
����������ѯ�ʵõ��Ľ��ֻ����ô���֣�����ֱ���ж�$y$�ĸ�������ż�ԡ��������ֲ�������������0������2��$y$��
����$y$���±겻ͬ�����ǿ��Խ�˶��±�ĳһλ��$0/1$���������ͣ�����ͬ��������$y$���±�����һλ�ϲ�ͬ����������ܵõ�����$y$�±�����͡�
��һ��$y$��ĳλ��ͬ��Ԫ�ظ������ٵ�λ�ã��ڽ�С�ļ����ڣ���С$\leq\frac{n}{2}$�����֣�������ֻ��һ��$y$���Ϳ��Եõ�����λ�ã����֮ǰ�ĺ;͵õ���һ������������$19$��
��ȻҲ���Բ����֡����Ҹ�λ��ͬ��һλ$p$��Ȼ��ö�ٲ�����$p$��ÿλ������Ҫ�ж��Ƿ���һ��$y$����һ������ֱ��ͨ��֮ǰ�ڸ�λ��ѯ�ʵõ����ڸ�λ����$1$��ֻö��$p,i$λΪ1���±꣬���Ա�ֻ֤��һ��$y$���жϳ����$y$�Ƿ�����λ����$1$����Ϊѯ�ʿ���ȷ�������Ƿ���$y$��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1005;

int n,x,y;
bool vis[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline bool Query()
{
	int t=0, res;
	for(int i=1; i<=n; ++i) if(vis[i]) ++t;
	if(!t) return 0;
	printf("? %d",t);
	for(int i=1; i<=n; ++i) if(vis[i]) printf(" %d",i);
	putchar('\n'); fflush(stdout);
	return res=read(),(t&1&&!(res^y))||(!(t&1)&&res^y==x);//���ö�Ρ���
}

int main()
{
	n=read(), x=read(), y=read();
	int sum=0, p=0;
	for(int i=0; 1<<i<=n; ++i)
	{
		for(int j=1; j<=n; ++j) if(j>>i&1) vis[j]=1;
		if(Query()) sum|=1<<i, p=i;
		for(int j=1; j<=n; ++j) vis[j]=0;
	}
	int p1=0, p2=1<<p;
	for(int i=0; 1<<i<=n; ++i)
		if(i!=p)
		{
			for(int j=1; j<=n; ++j) if(j>>i&1 && j>>p&1) vis[j]=1;
			p2|=Query()<<i;
			for(int j=1; j<=n; ++j) vis[j]=0;
		}
	if((p1=p2^sum)>p2) std::swap(p1,p2);
	printf("! %d %d\n",p1,p2); fflush(stdout);

	return 0;
}
