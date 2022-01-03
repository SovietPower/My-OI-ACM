/*
���⼴������������������� ʹ���������ı߾���С��������Ȼ������ĳ�����ϵ�����*P��
��P��ʵ����Χ�ڣ���˵������Ҳ��ʵ�������ִ�����������顣���ƵĻ���ֱ������������
̰�ĵĻ����������������һֱ�����������Ծ�GG�ˡ���
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const double eps=1e-6;
const int N=218,M=2018;

int n,m,P,Max,src,des,Enum,H[N],cur[N],fr[M],to[M],nxt[M],cost[M],num[N],lev[N],pre[N],que[N];
double cap[M],Cap[M];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v,int w)
{
	Max=std::max(Max,w);
	to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], H[u]=Enum, Cap[Enum]=cap[Enum]=w;
	to[++Enum]=u, fr[Enum]=v, nxt[Enum]=H[v], H[v]=Enum, Cap[Enum]=cap[Enum]=0;	
}
bool BFS()
{
	for(int i=src; i<des; ++i) lev[i]=des+1;
	lev[des]=0, que[0]=des; int h=0,t=1;
	while(h<t)
	{
		int x=que[h++];
		for(int i=H[x]; i; i=nxt[i])
			if(lev[to[i]]==des+1 && cap[i^1])
				lev[to[i]]=lev[x]+1, que[t++]=to[i];
	}
	return lev[src]<=des;
}
double Augment()
{
	double mn=1e8;
	for(int i=des; i!=src; i=fr[pre[i]])
		mn=std::min(mn,cap[pre[i]]);
	for(int i=des; i!=src; i=fr[pre[i]])
		cap[pre[i]]-=mn, cap[pre[i]^1]+=mn;
	return /*fabs(mn)<eps?0:*/mn;
}
double ISAP()
{
	if(!BFS()) return 0;
	for(int i=src; i<=des; ++i) ++num[lev[i]],cur[i]=H[i];
	int x=src; double res=0;
	while(lev[src]<=des)
	{
		if(x==des) x=src,res+=Augment();
		bool can=0;
		for(int i=cur[x]; i; i=nxt[i])
			if(lev[to[i]]==lev[x]-1 && cap[i])
			{
				can=1, cur[x]=i, pre[x=to[i]]=i;
				break;
			}
		if(!can)
		{
			int mn=des;
			for(int i=H[x]; i; i=nxt[i])
				if(cap[i]) mn=std::min(mn,lev[to[i]]);
			if(!--num[lev[x]]) break;
			++num[lev[x]=mn+1];
			cur[x]=H[x];
			if(x!=src) x=fr[pre[x]];
		}
	}
	return res;
}
void Init(double lim){
	for(int i=2; i<=Enum; ++i) cap[i]=std::min(Cap[i],lim);
}
double Solve(double mxflow)
{
	double l=1.0,r=Max,m;
	while(r-l>1e-4)
		if(Init(m=(l+r)*0.5),fabs(mxflow-ISAP())<eps) r=m;
		else l=m;
	return l;
}

int main()
{
	n=read(),m=read(),P=read(),Enum=src=1,des=n;
	for(int u,v,w,i=1; i<=m; ++i)
		u=read(),v=read(),w=read(),AddEdge(u,v,w);//f&=(w==1);
	double res1=ISAP();
	printf("%.0lf\n%.4lf",res1,1.0*Solve(res1)*P);

	return 0;
}
