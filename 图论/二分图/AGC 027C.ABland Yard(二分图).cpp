/*
30ms	10496KB
$Description$
����һ��ͼ�����ܴ����Ի�����ÿ��������A��B�����Ƿ����һ��·����ʹ�������治���ߣ��ܹ��õ�����AB����ϣ������ظ������㣩��
$n\leq2\times10^5,m\leq2\times10^5$��
$Solution$
����һ���㣬������ĺ��ֻ��A��B����Ȼ������������·���ϡ�
$Sol 1$
���ǰ������ĵ�ɾ����Ȼ�����ж��������ĵ��Ƿ�Ҫ��ɾ��...����һֱɾ���ж�����Ƿ����δ��ɾ���ĵ㡣�����������ࡣ
$Sol 2$
������Ľ���Ҳ���Կ�����·��ֻ����AABB�����Ļ�������AABBAABB...��������ÿ����ʹ�������ת�ƣ���
AA,AB,BB,BA�������Ļ����ǿ���ͨ������ͼ�ң���������ͬ�ַ���һ��S->T�ıߣ���ͬ�ַ���һ��T->S�ıߣ�����л���
*/
#include <cstdio>
#include <cctype>
#include <cstdlib>
#define gc() getchar()
const int N=4e5+5;

int Enum,H[N],nxt[N],to[N],vis[N];
char s[N>>1];

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
}
void DFS(int x)
{
	vis[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]]) DFS(v);
		else if(vis[v]==1) {puts("Yes"); exit(0);}
	vis[x]=-1;
}

int main()
{
	int n=read(),m=read(); scanf("%s",s+1);
	for(int u,v; m--; )
	{
		u=read(),v=read();
		s[u]==s[v]?(AE(u,v+n),AE(v,u+n)):(AE(u+n,v),AE(v+n,u));
	}
	for(int i=1; i<=n; ++i) if(!vis[i]) DFS(i);
	puts("No");

	return 0;
}
