/*
1364kb	140ms
$Description$
����һ�Ŵ�Ȩͼ������˫��ģ�����ͬ���򳤶Ȳ�ͬ�������1���������پ�����1���һ���㣬�ٻص�1�����·����ͱ߲����ظ�������
n��5000��m��10000��
$Solution$
���·��Ȼ�Ǵ�1�ߵ�һ���㣬Ȼ��������ͨ�����·������һ���㣬�ٻص�1��
���ǰ���1���ڵĵ㶼���Ϊ�ؼ��㣬Ȼ���1��ͼ��ɾȥ���ͳ���������һ�Թؼ���֮������·��
��Ȼ����ö��ÿ���������·�����ǰѵ㻮�ֳ���������$x,y$��$x$�еĵ��ʼdisΪlen(1,x)������Щ�㿪ʼ�����·��
�����$y$�еĵ��dis+len(y,1)���´𰸡�
��Ȼ����ʵ���Ǹ��ݻ��ֱ���1��ĳЩ���ߣ�ѡ���ĳЩ���ȥ������1�����·��
��ô���ּ����ء�ö��ÿһλ������һλ��0/1�ĵ�ֱ���Ϊ$x,y$������һ�顣
��Ϊ������������һλ��ͬ������ÿ�Ե����ٱ�����һ�Ρ���Ȼֱ��ö���±�Ķ�����Ҳ���ԡ�
����ֻ��Ҫlogn�����·�����Ӷ�$O(n\log^2n)$��
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 200000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define mp std::make_pair
#define pr std::pair<int,int>
const int N=5005,M=20005,INF=0x3f3f3f3f;

int A[N],Enum,H[N],nxt[M],to[M],len[M],dis[N],df[N],dt[N];
std::priority_queue<pr> q;
bool exist[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int u,int v,int w)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, len[Enum]=w;
}
void Dijkstra()
{
	static bool vis[N];

	memset(vis,0,sizeof vis);
	while(!q.empty())
	{
		int x=q.top().second; q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(int v,i=H[x]; i; i=nxt[i])
			if(dis[v=to[i]]>dis[x]+len[i]) q.push(mp(-(dis[v]=dis[x]+len[i]),v));
	}
}

int main()
{
	int n=read(),m=read(),cnt=0;
	memset(df,0x3f,sizeof df), memset(dt,0x3f,sizeof dt);
	for(int u,v; m--; )
	{
		u=read(),v=read();
		if(u==1) df[v]=read(),dt[v]=read(),!exist[v]&&(A[++cnt]=v,exist[v]=1);
		else if(v==1) dt[u]=read(),df[u]=read(),!exist[u]&&(A[++cnt]=u,exist[u]=1);
		else AE(u,v,read()),AE(v,u,read());
	}
	int ans=INF;
	for(int bit=1; bit<=cnt; bit<<=1)//����Ҫ>>1&bit...
	{//ֱ��ö���±�Ķ����ƺ��� 
		memset(dis,0x3f,sizeof dis);
		for(int i=1,x; i<=cnt; ++i)
			if(i&bit) x=A[i], q.push(mp(-(dis[x]=df[x]),x));
		Dijkstra();
		for(int i=1,x; i<=cnt; ++i)
			if(!(i&bit)) x=A[i], ans=std::min(ans,dis[x]+dt[x]);

		memset(dis,0x3f,sizeof dis);
		for(int i=1,x; i<=cnt; ++i)
			if(!(i&bit)) x=A[i], q.push(mp(-(dis[x]=df[x]),x));
		Dijkstra();
		for(int i=1,x; i<=cnt; ++i)
			if(i&bit) x=A[i], ans=std::min(ans,dis[x]+dt[x]);
	}
	printf("%d\n",ans);

	return 0;
}
