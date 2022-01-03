/*
93MS	1316K
$Description$
����$n$�Լ�$n$������������֮������������һ������ͼ�������������
$n\leq100$��
$Solution$
��Щ����[��С����]��
���ǿ��Թ���һ������ֻҪ�����ϵı߳�Ϊ��ߣ�����������Ϊ$0$�Ϳ����ˡ�
ÿ���ҵ���ǰ�㼯��������С�ıߣ���������Ϊ$c$��Ȼ�����$c$���㼯�ֳ��������ϣ�������������֮��ĵ�Ե��������$c$�������ڲ��ĵ�������$>c$�����ڼ����ڲ������ݹ������ɡ�
���ּ��ϵ�ʱ��Ҳ�ǿ����������һ����$x$���ֵ��󼯺ϣ���$flow[x][i]>c$�ĵ�$i$�ֵ��󼯺ϣ�����ĵ�ֵ��Ҽ��ϣ����ж�һ�����Ҽ����Ƿ�����֮��������$=c$���ɡ�ע���Ҽ���Ϊ��ʱҲ�޽⣨$x\dfrac{>c}{}u\dfrac{\ c\ }{}v\dfrac{>c}{}x$��������Ȼ���У���
���Ӷ�$O(n^3)$��
ע��$A[i]$��д��$i$����
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=105;

int A[N],tmp[2][N],f[N][N],W[N][N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
bool DFS(int l,int r)
{
	if(l==r) return 1;
	int mn=1<<30,cnt[2]={0,1}; tmp[1][1]=A[l];
	for(int i=l; i<=r; ++i)
		for(int j=i+1; j<=r; ++j) mn=std::min(mn,f[A[i]][A[j]]);
	for(int s=A[l],i=l+1,t; i<=r; ++i) t=f[s][A[i]]>mn, tmp[t][++cnt[t]]=A[i];
	if(!cnt[0]) return 0;
	for(int i=1; i<=cnt[0]; ++i)
		for(int j=1; j<=cnt[1]; ++j)
			if(f[tmp[0][i]][tmp[1][j]]!=mn) return 0;
	for(int i=l,t=1; t<=cnt[0]; ++i) A[i]=tmp[0][t++];
	for(int i=l+cnt[0],t=1; i<=r; ++i) A[i]=tmp[1][t++];
	W[A[l]][A[r]]=mn, W[A[r]][A[l]]=mn;
	return DFS(l,l+cnt[0]-1)&&DFS(l+cnt[0],r);
}

int main()
{
	int n;
	while(~scanf("%d",&n))
	{
		memset(W,0,sizeof W);
		for(int i=1; i<=n; ++i)
			for(int j=1; j<=n; ++j) f[i][j]=read();
		for(int i=1; i<=n; ++i) A[i]=i;
		if(!DFS(1,n)) puts("NO");
		else
		{
			puts("YES");
			for(int i=1; i<=n; ++i)
				for(int j=(W[i][i]=-1,1); j<=n; ++j) printf("%d%c",W[i][j]," \n"[j==n]);
		}
	}

	return 0;
}
