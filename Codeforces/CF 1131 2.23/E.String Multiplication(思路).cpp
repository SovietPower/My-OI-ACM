/*
46ms	10100KB
�Ӻ���ǰ�����һ���ַ���$p_n$��ǰ��׺�Ƿ���ͬ����һ�¡����忴[����](https://www.cnblogs.com/mjtcn/p/10424484.html)�ɲ���д��= =
���������������ݹ�ȥ����Ҳ���Դ�$p_1$������ơ���Ϊ�õ�����ĳ���ַ���������Ӵ���������$f[i][j]$��ʾ$p_1\cdot p_2\cdot...\cdot p_i$��$j$�ַ�����������ȣ�ת��ʱ��һ��$p_{i+1}$�Ƿ�����$j$�ַ����ɵģ��Ǿ���$len\times(f[i][j]+1)+f[i][j]$���£�������$1+j�ַ����ǰ��׺$���£�$p_{i-1}$�к�$j$�ַ�����ת�ƣ���
���Ӷ�$O(\sum|p_i|)$���ݹ飩��$O(26\sum|p_i|)$�����ƣ���Ȼ��ǰ�߳����Ƚϴ󣩡�
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define S 26
typedef long long LL;
const int N=1e5+5;

int f[N][S],pre[S],suf[S];
char s[N];

void Solve(int *f)
{
	scanf("%s",s+1);
	int l=strlen(s+1);
	for(int j=0; j<S; ++j)
	{
		int mx=0;
		for(int i=1,cnt=0; i<=l; ++i)
			if(s[i]==j+'a') mx=std::max(mx,++cnt);
			else cnt=0;
		f[j]=mx, pre[j]=suf[j]=0;
		for(int i=1; i<=l; ++i)
			if(s[i]==j+'a') ++pre[j];
			else break;
		for(int i=l; i; --i)
			if(s[i]==j+'a') ++suf[j];
			else break;
	}
}

int main()
{
	int n; scanf("%d",&n);
	Solve(f[1]);
	for(int i=2; i<=n; ++i)
	{
		Solve(f[i]);
		int l=strlen(s+1);
		for(int j=0; j<S; ++j)
			if(f[i-1][j])
				if(pre[j]!=l) f[i][j]=std::max(f[i][j],pre[j]+suf[j]+1);
				else f[i][j]=std::max(f[i][j],l*(f[i-1][j]+1)+f[i-1][j]);
	}
	int ans=0;
	for(int i=0; i<S; ++i) ans=std::max(ans,f[n][i]);
	printf("%d\n",ans);

	return 0;
}
