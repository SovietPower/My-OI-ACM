/*
�����Ͻڵ���зֿ飬ÿ�����¼dep,fa,val,Max,Sum��Max,Sum��ʾ��ǰ���ڸÿ��ڵ�������Ȩֵ���ֵ��� 
�ڵ�i��ֵ��ʾ��root[i]��iһ��·���ĵĶ�Ӧֵ����Ϊ��ֵʱӦ�������ҵ�LCA�����Լ�¼һ���Ӹ���Ҷ����Ϣ 
�޸�һ����iʱӰ���ֻ�Ǹÿ��ڴ�fa[i]���µĵ㣬�������¸��� 
��ѯ·��ʱ����������LCA��ע��ÿ�ζ�������ȴ�������Ա���������� 
����������һ������ʱ����һ�������� ֱ��LCA 
������ߣ�һ��ԭͼ�еıߣ�����ÿ�����ڵĹ�ϵ�� 
*/
#include<cmath>
#include<cstdio>
#include<cctype>
#include<algorithm>
#define gc() getchar()
const int N=3e4+5,INF=0x3f3f3f3f;

int n,limit,val[N],rt[N],dep[N],fa[N],Max[N],Sum[N],Enum,H[N],nxt[N<<1],to[N<<1];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
void AddEdge(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}

void Build(int x,int &res)
{
	if(res) rt[x]=rt[fa[x]],--res;
	else rt[x]=x,res=limit;
	for(int i=H[x];i;i=nxt[i])
		if(to[i]!=fa[x])
			dep[to[i]]=dep[x]+1,fa[to[i]]=x,Build(to[i],res);
}
void Update(int x,int Mx,int Sm)
{
	Sm+=val[x], Sum[x]=Sm;
	Mx=std::max(Mx,val[x]), Max[x]=Mx;
	for(int i=H[x];i;i=nxt[i])
		if(rt[x]==rt[to[i]] && to[i]!=fa[x])
			Update(to[i],Mx,Sm);
}
int Query(int x,int y,bool f)
{
	int sm=0,mx=-INF;
	while(rt[x]!=rt[y])//����ͬһ��ʱֱ�����������Ϣ 
	{
		if(dep[x]<dep[y]) std::swap(x,y);
		if(dep[rt[x]]<dep[rt[y]]) std::swap(x,y);
		mx=std::max(mx,Max[x]), sm+=Sum[x];
		x=fa[rt[x]];
	}
	while(x!=y)//��ͬһ�����ڣ�����ֱ�����������Ϣ��һ������ 
	{
		if(dep[x]<dep[y]) std::swap(x,y);
		mx=std::max(mx,val[x]), sm+=val[x];
		x=fa[x];
	}
//	while(x!=y)
//	{
//		if(dep[x]<dep[y]) std::swap(x,y);
//		if(rt[x]==rt[y])//��ͬһ�����ڣ�����ֱ�����������Ϣ��һ������ 
//		{
//			mx=std::max(mx,val[x]), sm+=val[x];
//			x=fa[x];
//		}
//		else
//		{
//			if(dep[rt[x]]<dep[rt[y]]) std::swap(x,y);
//			mx=std::max(mx,Max[x]), sm+=Sum[x];
//			x=fa[rt[x]];
//		}
//	}
	mx=std::max(mx,val[x]), sm+=val[x];//Don't forget!!
	return f?mx:sm;
}

int main()
{
	n=read(),limit=pow(n,0.45);
//	limit=sqrt(n);
	for(int u,v,i=1;i<n;++i) u=read(),v=read(),AddEdge(u,v);
	for(int i=1;i<=n;++i) Max[i]=val[i]=read();
	int res=0;
	Build(1,res);
	for(int i=1;i<=n;++i)
		if(rt[i]==i) Update(i,val[i],0);
	int q=read(),u,v;char s[7];
	while(q--)
	{
		scanf("%s",s),u=read(),v=read();
		if(s[0]=='C')
		{
			val[u]=v;
			if(u==rt[u]) Update(u,val[u],0);//��Ȼ���ܴ���һ����� 
			else Update(u,Max[fa[u]],Sum[fa[u]]);//�Ǵӵ�ǰ�ڵ����,not fa[u]!fa[u]��Sum�����Ͷ��� 
		}
		else if(s[1]=='M') printf("%d\n",Query(u,v,1));
		else printf("%d\n",Query(u,v,0));
	}

	return 0;
}
