/*
Description: һ��n���������ÿ�ο���ѡ����������Ҷ�ӽڵ㲢ɾȥһ�����õ��ļ�ֵΪ�����ľ��� 
ɾn-1�Σ��������ʹ���õ��ļ�ֵ��󣬲�������� 
Solution: ���Ͼ��룬����󣬿��Կ���������ֱ�� 
������֪����ֱ��u->v����ô����һ��x�������������Զ�������u,v��һ��(���������������ֱ��һ�����Ը���������uv) 
����x��u��Զ���ǿ϶���ɾx 
ɾֱ���ϵĵ�(ֱ���˵�)�ᵼ��һЩ��ȡ������Զ���� 
��Ȼ������˳��ɾ��ֱ���ϵĵ㣬���ɾֱ���˵� 
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
#define gc() getchar()
const int N=2e5+5;

int n,U,V,mxdis,fa[N],dis[N][2],cnt,D[N],Enum,H[N],to[N<<1],nxt[N<<1];
long long res;
bool Is_d[N];
struct Triple
{
	int u,v,w;
}ans[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline void AddEdge(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void DFS(int x,int f,int ds)
{
	fa[x]=f;
	for(int i=H[x];i;i=nxt[i])
		if(to[i]!=f) DFS(to[i],x,ds+1);
	if(ds>mxdis) mxdis=ds, V=x;
}
void DFS2(int x,int f,bool op)
{
	for(int i=H[x];i;i=nxt[i])
		if(to[i]!=f)
			dis[to[i]][op]=dis[x][op]+1, DFS2(to[i],x,op);
}
void DFS3(int x,int f)
{
	for(int i=H[x];i;i=nxt[i])
		if(to[i]!=f) DFS3(to[i],x);
	if(!Is_d[x])
		if(dis[x][0]>dis[x][1]) res+=dis[x][0],ans[++cnt]=(Triple){U,x,x};
		else res+=dis[x][1],ans[++cnt]=(Triple){V,x,x};
}

int main()
{
	n=read();
	for(int u,v,i=1;i<n;++i) u=read(),v=read(),AddEdge(u,v);
	DFS(1,-1,0);
	U=V, mxdis=0;
	DFS(U,-1,0);
	int x=V,tot=0;
	res=1ll*mxdis*(mxdis+1)>>1;
	while(x!=U) Is_d[x]=1,D[++tot]=x,x=fa[x];
	Is_d[U]=1;
	DFS2(U,-1,0), DFS2(V,-1,1);
	DFS3(U,-1);
	printf("%I64d\n",res);
	for(int i=1;i<=cnt;++i) printf("%d %d %d\n",ans[i].u,ans[i].v,ans[i].w);
	for(int i=1;i<=tot;++i) printf("%d %d %d\n",U,D[i],D[i]);

	return 0;
}
