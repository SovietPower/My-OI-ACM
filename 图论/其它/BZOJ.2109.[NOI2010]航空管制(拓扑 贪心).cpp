/*
952kb	2796ms
��һ���������򼴿ɡ�
�ڶ��ʣ�����һ��Ԫ�����������о�����ǰ�����񲻺�����
���ǿ�����һ��Ԫ�س��־������󡣸�������һ��С��Ȩֵ���Ѷ��л������ȶ��м��ɣ����ȵ�ͬһ�㵫��Ȩֵ��ģ���
�������ֱ���ж���Ϊ��ʱ�����ߵ�ǰ����ķɻ������ڵ�ǰʱ�䣩��������ʱ��ɡ�
�������ǽ���ͼ����$n$���������򼴿ɡ�����һ��ֱ���÷�ͼ����������У�
���Ӷ�$O(nm\log n)$��
�����ö�����Ȼ�ܹ� ��������Щ�����������ǰ�ʱ������ģ��һ�����ɡ��Ͳ�д�ˡ�
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define mp std::make_pair
#define pr std::pair<int,int>
typedef long long LL;
const int N=2005,M=1e4+5;

int n,tm[N],Enum,H[N],nxt[M],to[M],indgr[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int u,int v)
{
	++indgr[v], to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
}
void Solve1()
{
	static int dgr[N],ans[N];
	std::priority_queue<pr> q;
	memcpy(dgr,indgr,sizeof dgr);

	for(int i=1; i<=n; ++i) if(!dgr[i]) q.push(mp(tm[i],i));
	for(int t=n,x; t; --t)
	{
		ans[t]=x=q.top().second, q.pop();
		for(int i=H[x]; i; i=nxt[i])
			if(!--dgr[to[i]]) q.push(mp(tm[to[i]],to[i]));
	}
	for(int i=1; i<=n; ++i) printf("%d ",ans[i]);
	putchar('\n');
}
int Solve2(int s)
{
	static int dgr[N];
	std::priority_queue<pr> q;
	memcpy(dgr,indgr,sizeof dgr);

	for(int i=1; i<=n; ++i) if(!dgr[i]&&i!=s) q.push(mp(tm[i],i));
	for(int t=n,x; t; --t)
	{
		if(q.empty()) return t;
		x=q.top().second, q.pop();
		if(t>tm[x]) return t;//��Ȼ�н��Ǿ��ܱ�֤����Ҳ�нⰡ �������return�ˡ�
		for(int i=H[x]; i; i=nxt[i])
			if(to[i]!=s && !--dgr[to[i]]) q.push(mp(tm[to[i]],to[i]));
	}
	return 1;
}

int main()
{
	n=read(); int m=read();
	for(int i=1; i<=n; ++i) tm[i]=read();
	while(m--) AE(read(),read());
	Solve1();
	for(int i=1; i<=n; ++i) printf("%d ",Solve2(i));

	return 0;
}
