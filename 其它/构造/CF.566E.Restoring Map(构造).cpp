/*
296ms	100KB
$Description$
����һ����������ĳ������ھӼ���Ϊ���о�����������$2$�ĵ�ļ��ϣ��������Լ�����
����$n$��$n$������ھӼ��ϣ�Ҫ����һ��$n$���������ʹ��ÿ�������ļ��϶���Ӧһ���㡣���뱣֤�н⡣
$n\leq1000$��
$Solution$
�����������ھӼ��ϴ�СΪ$2$����ô�����е�������֮��һ���бߡ��������ǾͿ���$O(\frac{n^3}{w})$ȷ������Ҷ�ڵ��Լ�����֮������ߡ�
Ȼ����Ҷ�ڵ�Ӧ�ùҵ�������һ��Ҷ�ڵ���ھӼ��ϣ��;���ĳ����Ҷ�ڵ㲻����$1$�ĵ�ļ�����ͬ����ô��������֮���бߡ�����Ҷ��$x$�����а���$x$���ھӼ�������С��һ������$x$���ھӼ��ϡ�һ������$\geq3$��������ĳ������벻����$1$�ĵ�ļ����ǻ�����ͬ�ġ�
��Ҫ���з�Ҷ�ڵ�ֻ��һ���������������
�ٷ�����ǣ��ҳ�Ҷ��$x$���ھӼ��ϣ������ȥ$x$���ϴ�С$\geq3$����ô�ڼ����ڶ���$>1$�ĵ������$x$���ڵġ����򼯺ϴ�С��$2$�����������Щ���У�������$x$���ڵĵ�һ��ֻ��һ����Ҷ�ڵ���������������ֻ��Ҫ����$x-a-b-...$���������
������[���鼯��д��](http://codeforces.com/contest/566/submission/39085398)��̫ɵ���˿�������QAQ��
*/
#include <cstdio>
#include <cctype>
#include <bitset>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1003;

std::bitset<N> st[N],nle,adj[N];
bool not_leaf[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i)
		for(int T=read(); T--; st[i][read()]=1);
	int m=0;
	for(int i=1; i<=n; ++i)
		for(int j=i+1; j<=n; ++j)
			if((st[i]&st[j]).count()==2)
			{
				std::bitset<N> tmp=st[i]&st[j];
				int s=0,t=0;
				for(int k=1; k<=n&&!t; ++k) if(tmp[k]==1) s?t=k:s=k;//������_Find_next�����Ǳ������Ӷ�Ҳ�ǶԵģ������ÿ���
				if(!adj[s][t])
					++m, printf("%d %d\n",s,t), nle[s]=nle[t]=1,
					adj[s][s]=adj[s][t]=1, adj[t][t]=adj[t][s]=1, not_leaf[s]=not_leaf[t]=1;
			}
	if(!m)
	{
		for(int i=2; i<=n; ++i) printf("%d %d\n",1,i);
		return 0;
	}
	if(m==1)
	{
		int s=0,t=0,a=0,b=0;
		for(int i=1; i<=n&&!t; ++i) if(not_leaf[i]) s?t=i:s=i;
		for(int i=1; i<=n; ++i)
			if(st[i].count()!=n)
			{
				for(int j=1; j<=n; ++j) !not_leaf[j]&&printf("%d %d\n",j,st[i][j]?s:t);
				break;
			}
		return 0;
	}
	for(int i=1; i<=n; ++i)
		if(!not_leaf[i])
		{
			int mn=N,p=0;
			for(int j=1; j<=n; ++j) if(st[j][i]&&st[j].count()<mn) mn=st[j].count(), p=j;
			std::bitset<N> tmp=st[p]&nle;
			for(int j=1; j<=n; ++j)
				if(tmp[j]&&tmp==adj[j])
					{printf("%d %d\n",i,j); break;}
		}

	return 0;
}
