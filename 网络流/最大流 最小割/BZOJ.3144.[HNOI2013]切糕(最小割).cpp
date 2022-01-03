/*
7036kb	832ms
û��$D$��������ô����"��С"���ǿ����뵽��С���ͬһ�����ϵĵ㴮�������ֱ�����S,T����С����Ǵ𰸡�(����ѵ�Ȩ�ŵ�ǰһ������)
�����ƣ������Ҫ���$i$��������������ֻ��ȥ��$[i-D,i+D]$��
��INF������ס������䣬����$i$��$i-D$������$i+D$��$i$������Ϊ��ϵ��˫��ģ�ֻ��һ�������ˡ�
ע��"��"��ָ��������������������INF�ߺ�ѡ�񲻺Ϸ��ı�һ�������Ϊ���ͨ��INF��������/����(���Ϊֻ��Ϸ���S,T����ͨҲ���ԣ����������ҳ���)
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define MAXIN 200000
const int N=70005,M=N<<2;
const int way[5]={1,0,-1,0,1},INF=0x3f3f3f3f;

int P,Q,R,D,src,des,Enum,cur[N],H[N],to[M],nxt[M],fr[M],cap[M],pre[N],num[N],lev[N],que[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline void AddEdge(int u,int v,int w)
{
	to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], cap[Enum]=w, H[u]=Enum;
	to[++Enum]=u, fr[Enum]=v, nxt[Enum]=H[v], cap[Enum]=0, H[v]=Enum;
}
inline int ID(int x,int y,int z){
	return z ? (z-1)*P*Q+(x-1)*Q+y : 0;
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
int Augment()
{
	int mn=INF;
	for(int i=des; i!=src; i=fr[pre[i]]) mn=std::min(mn,cap[pre[i]]);
	for(int i=des; i!=src; i=fr[pre[i]]) cap[pre[i]]-=mn, cap[pre[i]^1]+=mn;
	return mn;
}
int ISAP()
{
	if(!BFS()) return 0;
	for(int i=src; i<=des; ++i) ++num[lev[i]],cur[i]=H[i];
	int res=0,x=src;
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
			++num[lev[x]=mn+1], cur[x]=H[x];
			if(x!=src) x=fr[pre[x]];
		}
	}
	return res;
}

int main()
{
	P=read(),Q=read(),R=read(),D=read(),Enum=1,src=0,des=P*Q*R+1;
	for(int p=1; p<=R; ++p)
		for(int i=1; i<=P; ++i)
			for(int j=1; j<=Q; ++j)
			{
				AddEdge(ID(i,j,p-1),ID(i,j,p),read());
				if(p>D)
					for(int xn,yn,k=0; k<4; ++k)
						if((xn=i+way[k]) && (yn=j+way[k+1]) && xn<=P && yn<=Q)
							AddEdge(ID(i,j,p),ID(xn,yn,p-D),INF);
			}
	for(int i=1; i<=P; ++i)
		for(int j=1; j<=Q; ++j) AddEdge(ID(i,j,R),des,INF);
	printf("%d",ISAP());

	return 0;
}
