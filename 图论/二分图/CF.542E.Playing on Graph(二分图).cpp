//1980ms	3600KB ����������
//http://www.cnblogs.com/SovietPower/p/8502993.html
/*
$Description$
����һ��n����m���ߵ�����ͼ��
��ÿ����Ҫѡ������û�б������ĵ㣬�����Ǻϲ�Ϊһ���µ㣬ֱ������ͼ�����һ������
����������ĳ��ȣ�������޽⡣
n<=1000��m<=10000
$Solution$
���ѷ����޽⵱�ҽ��������滷��
> ����֤������һ���滷�����뻷��һ����ϲ�������滷�Դ��ڣ�������������ϲ����ϲ��������ߵı������������ϲ�֮�������ٻ���һ�߱�������������һ���滷�������һ�������Σ���������ô�ϲ�����ʣ��һ���滷��
![](https://images2018.cnblogs.com/blog/1143196/201803/1143196-20180303205446785-1055437104.png)

���������滷��������һ�Ŷ���ͼ��һ���н⣬ֱ�����ҷֱ�ϳ�һ�������γ�һ������Ϊ2��������

�ȿ���һЩ�������
����һ������Ȼ����ֱ����Ȼ�����ֱ���ߵĵ�ֱ�Ӻϲ���ȥ��
����һ��ż�������ҵ��ǶԳƵ������㣬��Ӧ��n/2+1.
![](https://images2018.cnblogs.com/blog/1143196/201803/1143196-20180303205454232-466142059.png)

������Ϊ�����ľ���̶���������һ����ģ�
�������������·���һ�Ե㡣

����һ�����(a,b)�����·Ϊx������(��������)xֻ���̣���ô�ϲ��� (a,b)�ľ���yһ��<=x�����൱���ҵ�һ��ans���Ͻ磬��취�Ѵ𰸹�������

����ö��һ������Ϊ����һ�ˣ���������㵽���ľ���di��
��Ϊ�Ǹ�����ͼ�����Ծ���ĳ���������ȵĵ�һ���ڶ���ͼ��ͬһ�ࡣ
ֱ�Ӱ�di��ͬ�ĵ�ϵ�һ��Ϳ����ˣ���õ�һ������Ϊmax{di}���������ҿ϶������ڸ���������
ʱ�临�Ӷ�O(nm)(BFS�Ǳ���� ��DFS�����մ��Ǵ�ģ�)

ע: ��ͼ������ͨ�ģ���ans=D1+D2+��+Dk(DiΪÿ����ͨ���max{di})
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define gc() getchar()
const int N=1e3+5,M=1e5+5;

int n,m,Enum,H[N],nxt[M<<1],to[M<<1],vis[N],cnt,bel[N],ans_b[N],dis[N],q[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v){
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void DFS(int x,int f)
{
	bel[x]=cnt;
	for(int v,i=H[x]; i; i=nxt[i])
		if((v=to[i])!=f && !vis[v]) vis[v]=vis[x]^1, DFS(v,x);
		else if(/*v!=f*/vis[v]==vis[x]) {printf("-1"); exit(0);}
}
int BFS(int now)
{
	memset(dis,0,sizeof dis);
	int h=0,t=1,res=0; q[0]=now, dis[now]=1;
	while(h<t)
	{
		int x=q[h++];
		for(int i=H[x]; i; i=nxt[i])
			if(!dis[to[i]])
				res=std::max(res,dis[to[i]]=dis[x]+1),q[t++]=to[i];
	}
	return res-1;
}

int main()
{
	n=read(),m=read();
	for(int u,v,i=1; i<=m; ++i) u=read(),v=read(),AddEdge(u,v);
	for(int i=1; i<=n; ++i)
		if(!vis[i]) ++cnt,vis[i]=2,DFS(i,i);
	for(int i=1; i<=n; ++i)
		ans_b[bel[i]]=std::max(ans_b[bel[i]],BFS(i));
	int res=0;
	for(int i=1; i<=cnt; ++i) res+=ans_b[i];
	printf("%d",res);

	return 0;
}
