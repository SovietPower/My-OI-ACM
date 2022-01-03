/*
40992kb	1876ms
���ѿ���ì�ܹ�ϵ���Թ���һ���������ȡһ���ڵ㣬��ô���ĸ��ڵ�Ͳ���ȡ������DP�����ˡ�
�ⲻ��û����˾������𡣡�
����©��һ��������������ϵ�����γ�һ����(��n���ߺ������ܿ�����)�����ж����ͨ�飬ÿ����ͨ��һ���ҽ��ڸ��ڵ㴦��һ������
�ڻ���ѡ��һ���߶Ͽ����Ѷ˵�ֱ���Ϊ���ڵ�dpһ�飬ȡmax���Ǹ���ͨ��Ĵ𰸡����������ͨ����ӡ�
ע��ȡmax��ȡmax{f[x][0]}��������ѡȡ��ǰ�ĸ��ڵ㣬��Ϊ��ʱ�Ѿ��Ͽ��ˣ����Ž��������һ�˵㱻ѡ�е������������ȡmax��������Ͷ����ˡ�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e6+5;

int n,s1,s2,mark,val[N],Enum,H[N],nxt[N<<1],to[N<<1];
LL f[N][2];
bool vis[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void Find_Circle(int x,int fa)
{
	vis[x]=1;
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=fa)
		{
			if(vis[to[i]])
				s1=x, s2=to[i], mark=i;
			else Find_Circle(to[i],x);
		}
}
void DFS(int x,int fa)
{
	f[x][0]=0, f[x][1]=val[x];
	for(int v,i=H[x]; i; i=nxt[i])
		if(to[i]!=fa && i!=mark && (i^1)!=mark)
		{
			DFS(v=to[i],x);
			f[x][0]+=std::max(f[v][0],f[v][1]);//������������� ��©����
			f[x][1]+=f[v][0];
		}
}

int main()
{
	n=read(),Enum=1;
	for(int i=1; i<=n; ++i) val[i]=read(),AddEdge(read(),i);
	LL res=0,tmp;
	for(int i=1; i<=n; ++i)
		if(!vis[i])
		{
			mark=0, Find_Circle(i,i);//s1->s2
//			if(mark)
//			{
				DFS(s1,s1), tmp=f[s1][0];
				DFS(s2,s2), tmp=std::max(tmp,f[s2][0]);
				res+=tmp;
//			}
//			else DFS(i,i), res+=std::max(f[i][0],f[i][1]);
		}
	printf("%lld",res);

	return 0;
}
