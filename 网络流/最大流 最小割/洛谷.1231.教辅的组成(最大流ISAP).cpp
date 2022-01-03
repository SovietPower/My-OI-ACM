#include<cstdio>
#include<cctype>
#include<algorithm>
//#define gc() getchar()
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=10010<<2,M=60005+20005,INF=0x7fffffff,MAXIN=5e6;

int n1,n2,n3,Enum,H[N],to[M<<1],nxt[M<<1],fr[M<<1],cap[M<<1],path[N],num[N],lev[N],cur[N],q[N],src,des;
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline void AddEdge(int u,int v)
{
	cap[++Enum]=1, to[Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], H[u]=Enum;
	cap[++Enum]=0, to[Enum]=u, fr[Enum]=v, nxt[Enum]=H[v], H[v]=Enum;
}

bool BFS()
{
	for(int i=src;i<=des;++i) lev[i]=des,cur[i]=H[i];
	int h=0,t=1;
	q[0]=des, lev[des]=0;
	while(h<t)
	{
		int x=q[h++];
		for(int i=H[x];i;i=nxt[i])
			if(cap[i^1] && lev[to[i]]==des)
				lev[to[i]]=lev[x]+1,q[t++]=to[i];
	}
	return lev[src]<des;
}
int Augment()
{
	int flow=INF;
	for(int i=des;i!=src;i=fr[path[i]])
		flow=std::min(flow,cap[path[i]]);
	for(int i=des;i!=src;i=fr[path[i]])
		cap[path[i]]-=flow,cap[path[i]^1]+=flow;
	return flow;
}
int ISAP()
{
	if(!BFS()) return 0;
	int flow=0,x=src;
	for(int i=src;i<=des;++i) ++num[lev[i]];
	while(lev[src]<des)
	{
		if(x==des)
		{
			flow+=Augment();
			x=src;
		}
		bool can=0;
		for(int i=cur[x];i;i=nxt[i])
			if(cap[i] && lev[to[i]]==lev[x]-1)
			{
				cur[x]=i, x=to[i], path[x]=i, can=1;
				break;
			}
		if(!can)
		{
			int mi=des;
			for(int i=H[x];i;i=nxt[i])
				if(cap[i]) mi=std::min(mi,lev[to[i]]);
			if(!--num[lev[x]]) break;
			++num[lev[x]=mi+1];
			cur[x]=H[x];
			if(x!=src) x=fr[path[x]];
		}
	}
	return flow;
}

int main()
{
    n1=read(),n2=read(),n3=read();
    Enum=1;
    int m1=read(),a,b;
    for(int i=1;i<=m1;++i)
    {
        a=read(),b=read(),
        AddEdge(b,a+n2);
    }
    int m2=read();
    for(int i=1;i<=m2;++i)
    {
        a=read(),b=read(),
        AddEdge(a+n2+n1,b+n2+n1+n1);
    }
    src=0,des=n2+n1+n1+n3+2;
    for(int i=1;i<=n2;++i) AddEdge(src,i);
    for(int i=1;i<=n1;++i) AddEdge(i+n2,i+n2+n1);
    for(int i=1;i<=n3;++i) AddEdge(i+n2+n1+n1,des);
    printf("%d",ISAP());
    return 0;
}
