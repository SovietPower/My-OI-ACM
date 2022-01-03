/*
$Description$
����һ������ͼ�����ж�����ѡ��$(s,x,t)$�ķ�����ʹ��ͼ�д���һ��$s\to x\to t$�Ĳ������ظ����·����
$n\leq 10^5,\ m\leq 2\times 10^5$��
$Solution$
�ȶ�����ͼ��Բ������
����S->T����(Щ)·������Դ𰸵Ĺ���Ϊ���ܾ��������е�������ô���ǰѷ���Ȩֵ��Ϊ��ͨ�����Ĵ�С��������·��Ȩֵ�;����ˡ�
��Ϊ������֮���Բ���������Σ�����Բ��Ȩֵ��Ϊ-1�ͺ��ˡ�
��ô������n^2����ԣ���ÿ�����֮���·���ϵ��Ȩֵ�͡�
�Ƕ�ÿ�������һ�±���������Ϳ����ˡ����·����������ע�⿼��ȫ����
��������Բ��ģ����Է����ʼsz[]Ϊ0��Բ�����1��
������ʵ��һ���߾Ϳ����ˡ�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 100000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=100005<<1,M=4e5+7;//2N!��_��

int n,m,tot,sk[N],top,dfn[N],low[N],Index,fa[N],sz[N],val[N];
long long Ans;
char IN[MAXIN],*SS=IN,*TT=IN;
struct Graph
{
	int H[N],Enum,to[M],nxt[M];
	inline void Add_E(int u,int v){
		to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	}
	inline void AddEdge(int u,int v){
		Add_E(u,v), Add_E(v,u);
	}
}G,T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void Tarjan(int x)
{
	dfn[x]=low[x]=++Index, sk[++top]=x, val[x]=-1;
	for(int v,i=G.H[x]; i; i=G.nxt[i])
		if(!dfn[v=G.to[i]])
		{
			fa[v]=x, Tarjan(v), low[x]=std::min(low[x],low[v]);
			if(dfn[x]<=low[v])
			{
				T.Add_E(x,++tot), val[tot]=1;
				do{
					T.Add_E(tot,sk[top--]), ++val[tot];
				}while(sk[top+1]!=v);//�������x��������x�����Ƕ�����ĸ��ڵ㡣
			}
		}
		else low[x]=std::min(low[x],dfn[v]);
}
void pre_DFS(int x,int f)
{
	if(x<=n) sz[x]=1;
	for(int i=T.H[x]; i; i=T.nxt[i])
		if(T.to[i]!=f) pre_DFS(T.to[i],x), sz[x]+=sz[T.to[i]];
}
void Solve(int x,int f,int tot)
{
	if(x<=n) Ans+=1ll*(tot-1)*val[x];//��xΪ����·���� 
	Ans+=1ll*(tot-sz[x])*sz[x]*val[x];//�����x���������һ�࣬�յ�����һ�� 
	for(int i=T.H[x]; i; i=T.nxt[i])
		Ans+=1ll*val[x]*(tot-sz[T.to[i]])*sz[T.to[i]], Solve(T.to[i],x,tot);//��������������յ㵽�����ط�ȥ(����x)
		//ע��տ�ʼ���˸���xΪ��������ֱ�ӽ�������յ�(*2)�ǲ��Եģ�
}
//void Solve(int x,int f,int tot)
//{
//	if(x<=n) Ans+=2ll*(tot-1)*val[x];//��xΪ���&�յ��·���� 
//	int sum=tot-sz[x];
//	for(int i=T.H[x]; i; i=T.nxt[i])
//		Ans+=2ll*val[x]*sum*sz[T.to[i]], sum+=sz[T.to[i]], Solve(T.to[i],x,tot);
//}

int main()
{
	tot=/*!*/n=read(),m=read();
	while(m--) G.AddEdge(read(),read());
	for(int i=1; i<=n; ++i)//��һ����ͨ�������mmp��
		if(!dfn[i]) Tarjan(i), pre_DFS(i,i), Solve(i,i,sz[i]);
	printf("%lld",Ans);

	return 0;
}
