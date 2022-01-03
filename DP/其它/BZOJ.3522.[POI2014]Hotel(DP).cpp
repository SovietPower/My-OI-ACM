/*
976kb	4808ms
��Ϊ�����Σ������ݷ�Χ��ô��ôС��������˷��ֲ��ԡ���
n^2���Ļ���ʵ�Ǹ�sb�⡣��
ö��ÿһ����Ϊ����Ϊ�˲��ظ����㣬����Ҫ����������������ֱ�λ�����������ϡ�
���ǵ�ǰǰ3���������Ϊdeep�ĵ�ֱ���a,b,c�����������������Ϊdeep�ĵ���d������ô�¼ӵĴ�Ϊ:
$$dab+dac+dbc=d[ab+(a+b)c]$$
ͬ���5������ͬһ��ȵĵ���Ϊe���¼Ӵ�:
$$...=e[ab+(a+b)c+(a+b+c)d]$$
��ô��6�������¼ӵĴ�ӦΪ:
$$...=f[ab+(a+b)c+(a+b+c)d+(a+b+c+d)e]$$
(����sz��ʾÿ�������д���ĳһ��ȵĵ���)
�������ǿ�����ÿ������ĳһ��ȵĵ�����ÿ�δ��ȼ��ϵ�ǰ $sz*[]���ʽ��$����ά��[]�������ʽ�ӣ������� $sz*��ǰ��������$���ٸ��������ĺ�($a+b+c...+=sz$)��
���õķ�ʽ��ֱ�Ӵ�������Ķ�������⣬���𰸼��ϵ�ǰ��������֮ǰ��������ѡ�����ķ�������Ȼ�����ѡ�����ķ��������� $��ǰ����sz*֮ǰ����ѡһ���ķ�����$���ٸ���������ѡһ���ķ����������Ǽ���sz.
��ǿ����Ҫ�����ʷ֣�~~�����ô�����~~�Ȳ����ˡ�
~~O(n)DPҲ������~~
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=5005;

int n,Enum,Maxd,H[N],nxt[N<<1],to[N<<1],c1[N],c2[N],sum[N];
long long Ans;

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
void DFS(int x,int f,int d)
{
	++sum[d], Maxd=std::max(Maxd,d);
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=f) DFS(to[i],x,d+1);
}

int main()
{
	n=read();
	for(int u,v,i=1; i<n; ++i) u=read(),v=read(),AddEdge(u,v);
	long long Ans=0;
	for(int x=1; x<=n; ++x)
	{
		memset(c1,0,sizeof c1), memset(c2,0,sizeof c2);
		for(int i=H[x]; i; i=nxt[i])
		{
			Maxd=1, DFS(to[i],x,1);
			for(int j=1; j<=Maxd; ++j)//��ôö�ٸ��Ӷ�Ҳ��ok�ġ�
			{
				Ans+=c2[j]*sum[j], c2[j]+=c1[j]*sum[j], c1[j]+=sum[j],
				sum[j]=0;
			}
		}
	}
	printf("%lld",Ans);

	return 0;
}
