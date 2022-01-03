/*
35772kb  1892ms
$Description$
����һ��N����M���ߵ�����ͼ������һ����Ĵ����ǽ�����뿪�����������ߵı�Ȩ�Ľϴ�ֵ��������1����N����С���ۡ����Ĵ������뿪���ıߵı�Ȩ���յ�Ĵ����ǽ����յ�ıߵı�Ȩ��
$Solution$
��ֱ�ӵķ����ǰ�ÿ������Ϊһ���㣬��������ͬһ�������������һ���±ߣ���������1��n�ĵ�ֱ���S��T�������· 
������������O(m^2)�� 
����·��������������(i,j,v1)��(j,k,v2)��v1<v2��������ι�ͼ��v1��v2С�Ĳ��ֲ��� 
��ô���ڵ�j��㣬ÿ�����Ӧһ�����߻���ߣ�����Ȩ���������������ӦȨֵΪv1,v2(v1<v2)����ô����(j',j,0),(j,j',v2-v1) 
�����㴦�Ĵ���û�б����㣬������ÿ�����߼���һ���㼴�� 
���Ӷ�O(mlogm)
����ı߱�ߺ�����д����
����д���롣��
û�б�Ȩ��ΧҪlonglong 
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define pr std::pair<LL,int>
#define mp std::make_pair
typedef long long LL;
const int N=4e5+5,M=4e5+5,MAXIN=3e6;//N:�������� 
const LL INF=1ll<<60;

int src,des,n,m,Enum,H[N],nxt[M<<2],to[M<<2],val[M<<2],tmp[M];//����һֱ����mdzz ��ʼһ��4e5���� 
int num,h[N>>1],tto[M],tnxt[M],tval[M];
LL dis[N];
bool vis[N];
char IN[MAXIN],*SS=IN,*TT=IN;
std::priority_queue<pr> q;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline bool cmp(int i,int j) {return tval[i]<tval[j];}
inline void Add(int u,int v,int w){
	tto[++num]=v, tnxt[num]=h[u], tval[num]=w, h[u]=num;
}
inline void AddEdge(int u,int v,int w){
	to[++Enum]=v, nxt[Enum]=H[u], val[Enum]=w, H[u]=Enum;
}
void Build()
{
	src=1, des=(m+1)<<1;
	for(int i=1; i<=n; ++i)
	{
		int cnt=0;
		for(int j=h[i]; j; j=tnxt[j])
			tmp[++cnt]=j;//���ž����� 
		std::sort(tmp+1,tmp+1+cnt,cmp);
		for(int now,next,j=1; j<=cnt; ++j)//~
		{
			now=tmp[j], next=tmp[j+1];//ֱ���ñߺ������Ϳ����� Ҳ�ǽ���˫��� 
			if(i==1) AddEdge(src,now,tval[now]);//������src�ı߲��һ������ 
			if(tto[now]==n) AddEdge(now,des,tval[now]);
			AddEdge(now^1,now,tval[now]);//ֻ��һ���� ������һ����ı� 
			if(j<cnt) AddEdge(now,next,tval[next]-tval[now]), AddEdge(next,now,0);
		}
//		if(cnt)	AddEdge(tmp[cnt]^1,tmp[cnt],tval[tmp[cnt]]);//WA!û�����������������У� 
	}
}
LL Dijkstra()
{
	for(int i=src+1; i<=des; ++i) dis[i]=INF;
	dis[src]=0, q.push(mp(0,src));
	while(!q.empty())
	{
		int x=q.top().second; q.pop();
		if(vis[x]) continue;
		if(x==des) return dis[x];
		vis[x]=1;
		for(int v,i=H[x]; i; i=nxt[i])
			if(!vis[v=to[i]] && dis[v]>dis[x]+val[i])
				dis[v]=dis[x]+val[i], q.push(mp(-dis[v],v));
	}
	return dis[des];
}

int main()
{
	n=read(),m=read();
	num=1;
	for(int u,v,w,i=1; i<=m; ++i)
		u=read(),v=read(),w=read(),Add(u,v,w),Add(v,u,w);
	Build();
	printf("%lld",Dijkstra());

	return 0;
}
