/*
9480kb	1792ms
������Կ�������$a_1,a_2,...,a_n$������ɶ��ٸ�$[L,R]$�е�����
��40�־��Ǹ���ȫ������
���k*ai+x������ɣ���ô(k+1)*ai+x��ȻҲ�������(k>=0,0<=x<ai)�� 
������ѡȡһ��ai��ģ������d=x(mod ai)����d+ai=x(mod ai)����ô���ڵ�ǰ����x���ǿ������[0,R]���ж��ٸ���ģaiΪx��ֻ����dÿ�μ�ai������������������һ�ξ��ܵõ��𰸡�
�������dҪ������ģaiΪx����С��������n������ϵõ�����������ζ�ÿ�����������$d$��
��Ϊÿ����ö��n����ת�ƣ�������ȡģ������״̬����������棬Ҫ����С�����뵽���·��
dis[x]��ʾ����ģaiΪx������ɵ���С��������ô����Ϊ0����С������Ȼ��0����dis[0]=0��Ȼ��SPFA��Dijkstra��
����ai��ȡ��С�İɡ�����ͼ�еĵ�����Ȼ���١�����Ȼȡ�ĸ�������ģ���Ϊ���ͳ�ƴ�ʱ��aiҲ�����ai��
�����Ʒ���������ƣ����԰ѱ߽��ȼ���������ô��
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define mp std::make_pair
#define pr std::pair<LL,int>
typedef long long LL;
const int N=5e5+5;

int n,mod,A[N];
LL dis[N];
std::priority_queue<pr> q;

inline LL read()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void Dijkstra()
{
	static bool vis[N];

	memset(dis,0x3f,sizeof dis);
	dis[0]=0, q.push(mp(0,0));
	while(!q.empty())
	{
		int x=q.top().second; q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(int i=1,v; i<=n; ++i)
			if(dis[v=(x+A[i])%mod]>dis[x]+A[i])
				q.push(mp(-(dis[v]=dis[x]+A[i]),v));
	}
}
inline LL Calc(LL x)
{
	LL ans=0;
	for(int i=0; i<mod; ++i)
		if(dis[i]<=x) ans+=(x-dis[i])/mod+1;//���и�dis[i] 
	return ans;
}

int main()
{
	n=read(); LL L=read(),R=read();
	int cnt=0; mod=N;
	for(int i=1; i<=n; ++i)
		if(!(A[++cnt]=read())) --cnt;//����0 
		else mod=std::min(mod,A[cnt]);
	n=cnt, Dijkstra();
	printf("%lld\n",Calc(R)-Calc(L-1));

	return 0;
}
