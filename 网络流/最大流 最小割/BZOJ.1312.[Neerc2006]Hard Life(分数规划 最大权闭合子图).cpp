/*
1300kb	236ms
���ִ�$x$��תΪ���Ƿ���ڷ������㣺$����-x*����\geq 0$��
ѡһ���߾ͱ���ѡ�����㣬���Կ���ת�����Ȩ�պ���ͼ������$1$����Ȩ������$x$�ĸ�Ȩ���ж�$����-��С��$�Ƿ�Ǹ����ɡ�
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define eps 1e-8
const int N=2005,M=6005+205;
const double INF=1ll<<55;

int n,m,src,des,Ans,A[N],B[N],Enum,H[N],nxt[M],fr[M],to[M],lev[N],pre[N];
double cap[M];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int u,int v,double w)
{
	to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], H[u]=Enum, cap[Enum]=w;
	to[++Enum]=u, fr[Enum]=v, nxt[Enum]=H[v], H[v]=Enum, cap[Enum]=0;
}
bool BFS()
{
	static int q[N];
	for(int i=0; i<des; ++i) lev[i]=des+1;
	int h=0,t=1; q[0]=des, lev[des]=0;
	while(h<t)
	{
		int x=q[h++];
		for(int i=H[x]; i; i=nxt[i])
			if(cap[i^1]>=eps && lev[to[i]]==des+1)
				lev[to[i]]=lev[x]+1, q[t++]=to[i];
	}
	return lev[src]<=des;
}
inline double Augment()
{
	double mn=INF;
	for(int i=des; i; i=fr[pre[i]])
		mn=std::min(mn,cap[pre[i]]);
	for(int i=des; i; i=fr[pre[i]])
		cap[pre[i]]-=mn, cap[pre[i]^1]+=mn;
	return mn;
}
double ISAP()
{
	static int cur[N],num[N];
	if(!BFS()) return 0;
	for(int i=0; i<=des; ++i) cur[i]=H[i], ++num[lev[i]];
	int x=0; double res=0;
	while(lev[0]<=des)
	{
		if(x==des) x=0, res+=Augment();
		bool can=0;
		for(int i=cur[x]; i; i=nxt[i])
			if(lev[to[i]]==lev[x]-1 && cap[i]>=eps)
			{
				can=1, cur[x]=i, pre[x=to[i]]=i;
				break;
			}
		if(!can)
		{
			int mn=des;
			for(int i=H[x]; i; i=nxt[i])
				if(cap[i]>=eps) mn=std::min(mn,lev[to[i]]);
			if(!--num[lev[x]]) break;
			++num[lev[x]=mn+1], cur[x]=H[x];
			if(x) x=fr[pre[x]];
		}
	}
	return res;
}
bool Check(double x)
{
	Enum=1, memset(H,0,des+1<<2);
	for(int i=1; i<=m; ++i) AE(0,i+n,1), AE(i+n,A[i],INF), AE(i+n,B[i],INF);
	for(int i=1; i<=n; ++i) AE(i,des,x);
	return m-ISAP()>=eps;
}
void DFS(int x)
{
	static bool vis[N];
	vis[x]=1, Ans+=(x<=n);
	for(int i=H[x]; i; i=nxt[i])
		if(cap[i]>=eps && !vis[to[i]]) DFS(to[i]);
}

int main()
{
	n=read(),m=read(),src=0,des=n+m+1;
	if(!m) return puts("1"),0;
	for(int i=1; i<=m; ++i) A[i]=read(),B[i]=read();
	double l=0.49,r=m/2.0,mid,EPS=1.0/n/n;//l������0.5����Ȼ���ű�����С��0.5��������Ϊ����ĸ������0.5�����ű��ʲ����ԣ�0.49999999403953�Ŷԣ�
	while(l+EPS<r)
		if(Check(mid=(l+r)*0.5)) l=mid;
		else r=mid;
	Check(l), DFS(src);
	printf("%d\n",Ans-1);

	return 0;
}
