/*
204792kb	33008ms
https://www.cnblogs.com/SovietPower/p/10056006.html
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=20005,MAXK=5e5+5,M=25000005+N+MAXK;

int n,m,K,Sz,Ans,A[N],val[N],fa[N],Enum,H[N],nxt[N],F[M],G[M];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
#define AE(u,v) nxt[v]=H[u], H[u]=v//只需要to就用不着了to[]啊 
void Calc(int *f,int A,int val)
{
	static int v[MAXK],q[MAXK];
	for(int i=0,s=0,h=1,t=0,tmp; i<=m; ++i,s+=val)
	{
		tmp=f[i]-s;
		while(h<=t && tmp>v[t]) --t;
		q[++t]=i, v[t]=tmp;
		while(i-q[h]>A) ++h;
		f[i]=v[h]+s;
	}
}
void DFS1(int x)
{
	int *Fx=F+x*K;
	if(A[x]) Calc(Fx,A[x],val[x]);
	for(int v=H[x]; v; v=nxt[v])
	{
		memcpy(F+v*K,Fx,Sz);
		DFS1(v);
		int *fx=Fx+1,*fv=F+v*K,val=::val[v];//f[x][j]=max(f[x][j],f[v][j-1]+val[v])
		for(int j=1; j<=m; ++j,++fx,++fv) *fx=std::max(*fx,*fv+val);
	}
}
void DFS2(int x,int sum)
{
	int *Gx=G+x*K;
	for(int v=H[x]; v; v=nxt[v])
	{
		memcpy(G+v*K,Gx,Sz);
		DFS2(v,sum+val[v]);
		int *gx=Gx+1,*gv=G+v*K,val=::val[v];//从v这棵子树中转移要强制至少选一个v 
		for(int j=1; j<=m; ++j,++gx,++gv) *gx=std::max(*gx,*gv+val);
	}
	if(!H[x])
	{
		int *Fx=F+x*K,*Gx=G+x*K+m,ans=0;
		for(int i=0; i<=m; ++i,++Fx,--Gx) ans=std::max(ans,*Fx+*Gx);
		Ans=std::max(Ans,ans+sum);
	}
	if(A[x]) Calc(Gx,A[x],val[x]);
}

int main()
{
	for(int T=read(); T--; )
	{
		n=read(),m=read(),K=m+1,Sz=K<<2;//m+1!
		memset(H,0,n+1<<2), memset(F,0,Sz), memset(G,0,Sz);
		for(int i=1; i<=n; ++i)
		{
			if((fa[i]=read())) AE(fa[i],i);
			A[i]=read()-1, val[i]=read();
		}
		DFS1(1);
		memset(H,0,n+1<<2);
		for(int i=n; i>1; --i) AE(fa[i],i);
		Ans=0, DFS2(1,val[1]);
		printf("%d\n",Ans);
	}
	return 0;
}
