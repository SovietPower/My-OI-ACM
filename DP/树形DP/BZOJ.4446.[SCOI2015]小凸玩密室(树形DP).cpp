/*
72992kb	784ms
$Description$
����$n$���ڵ����ȫ��������ÿ����Ϊ��ɫ��Ȩֵ$a_i$��ÿ����Ȩֵ$b_i$����һ��Ⱦ��ĳ�����޻��ѣ�Ȼ��ÿ��Ⱦ�ڵ�$v$�Ļ��ѣ�Ϊ��һ��Ⱦ�ڵ�$u$��$v$�ľ���$d_{u,v}$����������Ȩֵ$a_v$��������Ҫ��֤����ʱ�̺�ɫ����ͨ����Ⱦ��$v$�������Ⱦ��$v$���������е㣬����Ⱦ�����㡣��Ⱦ�����е���С���ѡ�
$n\leq 2\times10^5$��

$Solution$
���������һ�����ݾ�˵��Ⱦɫ�ˣ��о�Ⱦɫ�Ƚ�˳��...
ע����ȫ������$\neq$����������������һ������$\neq$��һ�ε���һ�ŵ��ݣ����ڵ�Ӧ�þ���$1$...

����ȡ������һ�������ĸ��㣬���Ǽ������״̬����$f[i][j]$��ʾȾ��$i$�����������һ��Ⱦ$j$����С���ѣ�����״̬����$O(n^2)$�ġ�
��ΪȾɫ˳������⣬Ⱦ������$i$��������һ��Ҫô��Ⱦ$i$��ĳ�����ȣ�Ҫô��Ⱦ$i$��ĳ�����ȵ���һ�����ӣ���ȥ$i$������������һ����������ͬʱ������$O(\log n)$�ģ�Ҳ����һ���������$\log n$�����ȡ�
�������Ǽ�$f[i][j]$��ʾȾ��$i$�������ߵ�$i$��$j$�����ȵ���С���ѣ�$g[i][j]$��ʾȾ��$i$�������ߵ�$i$��$j$�����ȵ���һ�����Ӵ�����$i$��$j$�����ȵ��ֵܽڵ㣩����С���ѡ�״̬����$O(n\log n)$�ġ�

����$f[i][j]/g[i][j]$��ת�ơ�
���$i$��Ҷ�ӽڵ㣬��ֱ����һ���ߵ���Ӧ�ڵ�Ļ��Ѽ��ɡ�
���$i$ֻ������ӣ����ߵ�������ٴ�������ߵ���Ӧ�ڵ㼴�ɡ�
����$i$����������$l,r$��Ҫô��$i\to l\to r\to i�Ķ�Ӧ����$��Ҫô��$i\to r\to l\to i�Ķ�Ӧ����$��ȡ��$\min$���ɡ�
DP�ĸ��Ӷ�Ҳ��$O(n\log n)$�ġ�

Ȼ����ôͳ����$x$��Ϊ���Ĵ𰸣�
ע�⵽һ����Ⱦ��$x$������Ȼ������$fa[x]$��Ⱦ$fa[x]$����һ������������У���Ȼ������$fa[fa[x]]$��Ⱦ$fa[fa[x]]$����һ������...�ظ�������̡�
ÿ����$fa$����DP����ͳ��һ�»��Ѿͺ��ˡ��ܸ��Ӷ�Ҳ��$O(n\log n)$��

ע������`dep[1]`����$1$���õ�`dep`�ģ���ΪҪ��$g[i][j]$����ʾ$j$�����ȵ�**��һ������**������
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define MAXIN 300000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define fa(x) (x>>1)
#define lson(x) (x<<1)
#define rson(x) (x<<1|1)
#define Anc(x,j) (x>>j)//x��j������ 
#define Bro(x,j) ((x>>j-1)^1)//x��j�����ȵ���һ������ 
typedef long long LL;
const int N=2e5+5,BIT=18;

int A[N],dep[N],dis[N][BIT];
LL f[N][BIT],g[N][BIT];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

int main()
{
	const int n=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	dep[1]=1;
	for(int x=2; x<=n; ++x)
	{
		dep[x]=dep[fa(x)]+1, dis[x][1]=read();
		for(int j=2; j<=dep[x]; ++j)
			dis[x][j]=dis[fa(x)][j-1]+dis[x][1];
	}
	for(int x=n; x; --x)
	{
		int l=lson(x),r=rson(x);
		for(int j=1; j<=dep[x]; ++j)
			if(r<=n)
			{
				f[x][j]=std::min(1ll*A[l]*dis[l][1]+g[l][1]+f[r][j+1],1ll*A[r]*dis[r][1]+g[r][1]+f[l][j+1]);
				g[x][j]=std::min(1ll*A[l]*dis[l][1]+g[l][1]+g[r][j+1],1ll*A[r]*dis[r][1]+g[r][1]+g[l][j+1]);
			}
			else if(l<=n)
			{
				f[x][j]=1ll*A[l]*dis[l][1]+f[l][j+1];
				g[x][j]=1ll*A[l]*dis[l][1]+g[l][j+1];
			}
			else f[x][j]=1ll*dis[x][j]*A[Anc(x,j)], g[x][j]=1ll*(dis[x][j]+dis[Bro(x,j)][1])*A[Bro(x,j)];
	}
	LL ans=1ll<<61;
	for(int i=1; i<=n; ++i)
	{
		LL now=f[i][1];
		for(int x=fa(i),las=i; x; las=x,x=fa(x))
		{
			int y=las^1;
			if(y<=n) now+=1ll*dis[y][1]*A[y]+f[y][2];
			else now+=1ll*dis[x][1]*A[fa(x)];
		}
		ans=std::min(ans,now);
	}
	printf("%lld\n",ans);

	return 0;
}
