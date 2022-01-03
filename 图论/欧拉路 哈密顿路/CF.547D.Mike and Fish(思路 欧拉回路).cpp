/*
139ms	28400KB
$Description$
����ƽ����n���㣬����Щ��Ⱦ�ɺ�or��ɫ��Ҫ��ÿ�С�ÿ�к�ɫ������ɫ�������Ĳ�ľ���ֵ<=1���������(��֤�н�)��
$Solution$
��ÿ�������ꡢ������ֱ���һ���㣬��ÿ����(x,y)���x(row)->y(column)�ı� 
�������ǿ��Խ���Ⱦɫ��ʹ����ÿ����������������ɫ��<=1 
���Ƕ������е�ŷ����·�����ǿ���ֱ�ӽ���Ⱦɫ 
���ǻ��ж���Ϊ�����ĵ㣬�����ĵ�һ����ż���������Ƕ�������������ߣ���������������ĵ�����Ͷ�Ϊż���� 
����ÿ����ͨ�飬ѡһ����ʼ����Ϊ�����ĵ�(��û������ѡ����Ϊż���ĵ�)����һ��ŷ����·(�������������Ӧ��������Ե�������������ı�)����·���ϵı߽���Ⱦɫ���� 
��ȷ��:  
����һ��ŷ����·���������ÿ���������ĺ��������������ͬ�� 
������㣬ŷ����·�ĵ�һ���ߺ����һ���ߵ���ɫ��������ͬ�� 
������ʼ����Ϊ�������������������������ıߣ����Ծ����һ�������һ���ߵ���ɫ��ͬҲû��ϵ 
(ͬɫ�Ļ�������Ӱ��ĵ���ͬ��ͬ�У�һ����ͨ������������ͨ��ֻ�������һ������ɫ��ͬ)
������ʼ����Ϊż��������ͨ����һ������ͼ����һ�������һ���ߵ���ɫһ������ͬ 
*/
#include <cstdio>
#include <cctype>
#define gc() getchar()
const int N=4e5+5,MAX=2e5;

int n,Enum,H[N],to[N<<1],nxt[N<<1],id[N<<1],dgr[N],top,sk[N],A[N];
char Ans[N];
bool vis[N<<1],v[N];//��ͱߵ�vis�ǲ�һ���İ���

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline void AddEdge(int u,int v,int i){
	++dgr[v], to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, id[Enum]=i;
}
void DFS(int x)
{
	v[x]=1;
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[i])
		{
			vis[i]=vis[i^1]=1, H[x]=i;
			DFS(to[i]);
			sk[++top]=id[i], i=H[x];
		}
}

int main()
{
	n=read(); Enum=1;
	for(int x,y,i=1; i<=n; ++i)
		x=read(),y=read()+MAX,AddEdge(x,y,i),AddEdge(y,x,i);
	int cnt=0;
	for(int i=1; i<=MAX<<1; ++i)
		if(dgr[i]&1) A[++cnt]=i;
	for(int i=1; i<=cnt; i+=2)
		AddEdge(A[i],A[i+1],0),AddEdge(A[i+1],A[i],0);
	for(int i=1; i<=cnt; ++i)
		if(!v[A[i]])
		{
			DFS(A[i]);
			bool f=0;
			while(top)
				Ans[sk[top--]]=f?'r':'b',f^=1;
		}
	for(int i=1; i<=MAX<<1; ++i)
		if(!v[i])
		{
			DFS(i);
			bool f=0;
			while(top)
				Ans[sk[top--]]=f?'r':'b',f^=1;
		}
	Ans[n+1]='\0';
	printf("%s",Ans+1);

	return 0;
}
