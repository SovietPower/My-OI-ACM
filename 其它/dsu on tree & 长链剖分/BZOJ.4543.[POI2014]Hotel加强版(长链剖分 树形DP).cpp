/*
7788kb	376ms
��f[x][i]��ʾx�����������Ϊi�ĵ�ĸ�����g[x][i]��ʾx�����У�����u,v��LCA(u,v)�ľ��붼��d���ҵ�x�ľ���Ϊd-i�ĵ��(u,v)������
��ô�Ϳ�����g[x][i]����һ��������f[y][i-1]���Լ�g[x][0]���´𰸡�
f��ת�Ƽ򵥡�g[x][i]Ҫô�Ǵ�ĳ�������еõ�(g[x][i]+=g[v][i+1])��Ҫô����x��ΪLCA��ĳ���������еõ�(g[x][i]+=f[x][i]*f[v][i-1])��
ֱ���������Ӷ�$O(n^2)$��
DP������±궼����ȣ����Կ����ó����ʷ֡��̳��ض���ʱf��Ҫ���ƣ�g��Ҫ���ƣ�������ָ�뷽��Щ�ɣ�g��ǰ����Ҫ���ռ䣩��
���Ӷ�$O(n)$��
Ϊɶ������ܵĲ��찡(30ms)==û������
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;

int Enum,H[N],nxt[N<<1],to[N<<1],dep[N],mxd[N],son[N],pos[N],*f[N],Fp[N],*fp=Fp;
LL Ans,*g[N],Gp[N<<1],*gp=Gp;
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
inline void Allot(int x)
{
	f[x]=fp, fp+=mxd[x], gp+=mxd[x], g[x]=gp, gp+=mxd[x];
}
void DFS1(int x,int fa)
{
	int mx=0;
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa) dep[v]=dep[x]+1, DFS1(v,x), mxd[v]>mx&&(mx=mxd[v],son[x]=v);
	mxd[x]=mx+1;
//	for(int i=H[x],v; i; i=nxt[i])
//		if((v=to[i])!=fa) dep[v]=dep[x]+1, DFS1(v,x), mxd[v]>mxd[son[x]]&&(son[x]=v);
//	mxd[x]=mxd[son[x]]+1;
}
void DFS2(int x,int fa)
{
	if(son[x]) f[son[x]]=f[x]+1, g[son[x]]=g[x]-1, DFS2(son[x],x);
	f[x][0]=1, Ans+=g[x][0];//�ض���������x�Ĺ��� 
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa&&v!=son[x])
		{
			Allot(v), DFS2(v,x); int l=mxd[v];
			for(int j=1; j<=l; ++j) Ans+=g[x][j]*f[v][j-1]+g[v][j]*f[x][j-1];
			for(int j=1; j<=l; ++j) g[x][j]+=g[v][j+1]+1ll*f[x][j]*f[v][j-1],f[x][j]+=f[v][j-1];//g[x][0]ת����Ҳûɶ�ð� 
		}
}

int main()
{
	int n=read();
	for(int i=1; i<n; ++i) AE(read(),read());
	DFS1(1,1), Allot(1), DFS2(1,1);
	printf("%lld\n",Ans);

	return 0;
}
