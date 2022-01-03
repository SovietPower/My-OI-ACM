/*
���Լ�������� n[a] - n[b] <= w �Ĳ���ʽ������ת���� n[a] <= n[b] + w
������ʽ dis[a] <= dis[b] + w(a,b)
��SPFA����dis[a]>dis[b]+w(a,b) ʱ������ɳ� 
����Сֵ���·�������ֵ�����· 
1.>= ����Сֵ��Ϊʲô���·����������·���ܶ��������ܲ������㣬 
(SPFA�ɳ�ʱ�ǽ� dis[a]>dis[b]+w(a,b) -> dis[a]=dis[b]+w(a,b))
2.<= �����ֵ��Ϊʲô�����·����ΪҪ��������С�ڵ��ڵ�������ֻ����̵�·��������ͼ������Լ����������������·����������Щ������������ 
3.�������û�еȺŵ���������������� 

Դ��Ӻ���ǰ�ӱߣ����Թ��� 
ע�����ÿ��С���Ѷ�Ҫ�ֵ��ǹ�����Դ����ÿ���㽨��ʱ����ȨΪ1������0 
*/
#include<cstdio>
#include<cctype>
using namespace std;
const int N=1e5+5;

int n,k,Enum,H[N],nxt[N*3],to[N*3],val[N*3],dis[N];
bool Flag,vis[N];

inline int read()
{
	int now=0,f=1;register char c=getchar();
	for(;!isdigit(c);c=getchar())
	  if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=getchar());
	return now*f;
}
inline void AddEdge(int u,int v,int w)
{
	to[++Enum] = v;
	nxt[Enum] = H[u];
	val[Enum] = w;
	H[u] = Enum;
}

void SPFA(int x)
{
	if(Flag) return;
	vis[x]=1;
	for(int i=H[x];i;i=nxt[i])
	{
		if(Flag) return;
		if(dis[to[i]]<dis[x]+val[i])
		{
			if(vis[to[i]])
			{
				Flag=1;
				return;
			}
			dis[to[i]]=dis[x]+val[i],
			SPFA(to[i]);
		}
	}
	vis[x]=0;
}

int main()
{
	n=read(),k=read();
	for(int opt,a,b,i=1;i<=k;++i)
	{
		opt=read(),a=read(),b=read();
		switch(opt)
		{
			case 1:
				AddEdge(a,b,0),AddEdge(b,a,0);
				break;
			case 2:
				if(a==b)
				{
					printf("-1");
					return 0;
				}
				AddEdge(a,b,1);
				break;
			case 3:
				AddEdge(b,a,0);
				break;
			case 4:
				if(a==b)
				{
					printf("-1");
					return 0;
				}
				AddEdge(b,a,1);
				break;
			case 5:
				AddEdge(a,b,0);
				break;
		}
	}
	for(int i=n;i;--i)
		AddEdge(0,i,1);
	SPFA(0);
	long long res=0;//long long
	for(int i=1;i<=n;++i)
		res+=dis[i];
	printf("%lld",Flag?-1:res);

	return 0;
}
