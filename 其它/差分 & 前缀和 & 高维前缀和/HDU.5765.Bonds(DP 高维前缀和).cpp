/*
624MS	9416K
$Description$
����һ��$n$����$m$���ߵ�����ͼ������$E$Ϊȥ��$E$��ʹ��ͼ����ͨ�ı߼�������һ��bondΪһ����С�����bond�бߵ�����һ�����Ӽ������Ǹ����
��ÿ���ߣ������ڶ��ٸ�bond�С�
$n\leq20,\quad n-1\leq m\leq\frac{n(n-1)}{2}$��
$Solution$
����bond�Ǽ�С�������һ���ǽ�ͼ�ֳ���**������ͨ��**��
״ѹ��ʾ�㼯�����$s$��һ����ͨ�飬��ʣ�µ����е�$s'=2^n-1-s$Ҳ��һ����ͨ�飬��ô$s$��$s'$֮��ı߾��γ���һ��bond����Щ�ߵ�$ans$++��
���ԣ�����ֻ��Ҫö��һ����ͨ��$s$��
Ȼ����ôͳ�ƱߵĴ��أ���Ȼ����ö��һ��bond�еıߣ��������ӶȾͳ���$O(2^nm)$��
�ܵ�bond�������������������
���һ����$(u,v)$����bond�У���Ȼ$u,v$��ʱ��ͬһ��ͨ���С�Ҳ����������һ��$u,v$��ͬһ��ͨ��ʱbond�ж��ٸ������������߲��ڶ��ٸ�bond���ˡ����ܸ���һ���Ϳ��Եõ������ߵĴ𰸡�
$u,v$��ͬһ��ͨ��ʱbond�ĸ��������ǰ���$\{u,v\}$�ļ������ж��ٸ�bond����ô�Ϳ����ø�άǰ׺��ö�ٳ����õ����ˡ�
���Ӷ�$O(2^nn)$��
����һ�������ǣ�ҪԤ������Щ������һ����ͨ�顣
����һ�£�ö�ٵ�ǰ�Ѿ���һ����ͨ��ĵ㼯����ôÿ�μ���һ����õ㼯���ڵĵ㣬�γɵ���Ȼ��һ����ͨ�顣
���Ӷ�Ҳ��$O(2^nn)$��
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=(1<<20)+4;

int e[25],f[N],sum[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void Pre(int n)
{
	for(int i=0; i<n; ++i) f[1<<i]=1;//not f[i]...
	for(int s=0,lim=1<<n; s<lim; ++s)
	{
		if(!f[s]) continue;
		for(int i=0; i<n; ++i)
			if(!(s>>i&1) && s&e[i]) f[s|(1<<i)]=1;
//		int adj=0;
//		for(int i=0; i<n; ++i) s>>i&1&&(adj|=e[i]);
//		for(int i=0; i<n; ++i)
//			if(!(s>>i&1) && adj>>i&1) f[s|(1<<i)]=1;
	}
}

int main()
{
	static int u[500],v[500];

	for(int TT=read(),T=1; T<=TT; ++T)
	{
		int n=read(),m=read(),lim=1<<n;
		memset(e,0,sizeof e), memset(f,0,lim<<2), memset(sum,0,lim<<2);
		for(int i=1; i<=m; ++i)
			u[i]=read(), v[i]=read(), e[u[i]]|=1<<v[i], e[v[i]]|=1<<u[i];
		Pre(n);
		int tot=0;
		for(int s=0; s<lim; ++s)
		{
			if(!f[s]||!f[lim-1-s]) continue;
			if(s>lim-1-s) break;
			sum[s]=1, sum[lim-1-s]=1, ++tot;
		}
		for(int i=0; i<n; ++i)
			for(int s=0; s<lim; ++s)
				if(!(s>>i&1)) sum[s]+=sum[s|(1<<i)];
//		for (int i = 1; i <= s; i += 2)
//			if (f[i] ^ f[s ^ i]) f[i] = f[s ^ i] = 0; else if(f[i]) ++tot;
//		for (int i = 0; i < n; ++i)
//			for (int j = 0; j <= s; ++j)
//				if (!(j & (1 << i))) f[j] += f[j | (1 << i)];
		printf("Case #%d:",T);
		for(int i=1; i<=m; ++i)
			printf(" %d",tot-sum[(1<<u[i])|(1<<v[i])]);
		putchar('\n');
	}
	return 0;
}
