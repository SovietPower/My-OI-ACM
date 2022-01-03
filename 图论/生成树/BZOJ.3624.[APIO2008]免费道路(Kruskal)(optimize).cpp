/*
2904kb	76ms
$Description$
����һ������ͼ��$k$��ÿ�����кڰ���ɫ����һ��������ʹ�úڱߵ���������$k$��
$n\leq 2\times 10^4,\ m\leq 10^5$��
$Solution$
���Ƿ�����Щ�ױ��Ǳ���ӵģ���Щ�Ƕ���ġ�
��ô�����Ȱ����кڱ߼ӽ�ȥ��Ȼ��ѱ���Ҫ�ӵİױ��ҳ�����
Ȼ��Kruskal���ѱ���Ҫ�ӵİױ��ȼӽ�ȥ��С��K�Ļ��ټ��ܼӵİױߡ�Ȼ��Ӻڱߡ�
Ҫ�������һ������ûע�⣬�տ�ʼ��Ϊ�ױ߻�Ҫ���дΡ�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 250000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=2e4+5,M=1e5+5;

int fa[N];
bool choseb[M],chosew[M];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Edge
{
	int fr,to;
}b[M],w[M];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
#define Init() for(int i=1; i<=n; ++i) fa[i]=i
int Find(int x)
{
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
inline bool Union(int u,int v)
{
	if(Find(u)!=Find(v)) {fa[fa[u]]=fa[v]; return 1;}
	return 0;
}
bool Solve(int n,int m,int K,int bt,int wt)
{
	if(wt<K) return 0;
	Init();
	int k=1;
	for(int i=1; i<=bt; ++i) if(Union(b[i].fr,b[i].to)&&++k==n) break;
	if(k<n)
		for(int i=1; i<=wt; ++i)
		{
			if(!Union(w[i].fr,w[i].to)) continue;
			chosew[i]=1;//mark the white edge
			if(++k==n) break;
		}
	if(k<n) return 0;

	Init();
	int used=0; k=1;
	for(int i=1; i<=wt; ++i)
		if(chosew[i]&&Union(w[i].fr,w[i].to))
			if(++used, ++k==n) break;
	if(used>K) return 0;
	if(k<n&&used<K)
		for(int i=1; i<=wt; ++i)
			if(!chosew[i]&&Union(w[i].fr,w[i].to))
			{
				chosew[i]=1, ++used, ++k;
				if(k==n||used==K) break;
			}
	if(used<K) return 0;
	if(k<n)
		for(int i=1; i<=bt; ++i)
		{
			if(!Union(b[i].fr,b[i].to)) continue;
			choseb[i]=1;
			if(++k==n) break;
		}
	return k==n;
}

int main()
{
	int n=read(),m=read(),K=read(),bt=0,wt=0;
	for(int i=1,u,v; i<=m; ++i)
		if(u=read(),v=read(),read()) b[++bt]=(Edge){u,v};
		else w[++wt]=(Edge){u,v};
	if(!Solve(n,m,K,bt,wt)) puts("no solution");
	else
	{
		for(int i=1; i<=wt; ++i) if(chosew[i]) printf("%d %d 0\n",w[i].fr,w[i].to);
		for(int i=1; i<=bt; ++i) if(choseb[i]) printf("%d %d 1\n",b[i].fr,b[i].to);
	}

	return 0;
}
