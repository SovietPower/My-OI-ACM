/*
858MS 5528K(��ô��ô���ܵĺܿ�İ�--��֣�)
$Description$
����һ������ÿ������Ȩֵ����$[0,m-1]$֮�䡣������Ϊ$0,1,...,m-1$�ķǿ���ͨ����ж��ٸ���
$n\leq 1000,m\leq 2^{10}$��
$Solution$
��ÿ����ͨ��ĸ��ڵ㴦ͳ�ơ�$f[x][k]$��ʾ��$x$Ϊ��������Ϊ$k$����ͨ�飨�������ж��ٸ���
��ô$f[x][k]=f[x][k]+\sum_{i\ \mathbb{xor}\ j=k}f[x][i]*f[v][j],\ v=son[x]$��
��һ���־����������������$FWT$�Ż���
����ʵ�֣�����Ҫÿ��ת��һ��������$FWT,IFWT$һ�Ρ��м����һֱ��$FWT$���$f$����Ϳ����ˡ�
�����е������ǣ�$f$����$f[x][k]$����Ҫ�����Լ���������ת�Ƶ�ʱ��$IFWT$��ȥ��������$f[v]$������֮��$IFWT(f[v])$����$f[v][0]++$��Ȼ����$FWT$��ȥ�������$f[v]$ȥ����$f[x]$�������Ϳ���ֱ����$FWT$���$f$�����ˡ�
$f[x][0]$�ڼ���ǰ�ǲ���$+1$�ģ���Ϊ����Ҫ��$f[x]$�����**�ǿ���ͨ��**����$x$Ϊ���ġ�
��������$f[i]\ IFWT$��ȥ������$f[i][0]--$��
���Ӷ�$O(nm\log m)$��
������������д���Ĳ��졣��
https://www.cnblogs.com/cjyyb/p/9065611.html
https://blog.csdn.net/clover_hxy/article/details/72722352
�����Ե���Ρ����ڵڶ�ƪ���С�
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 200000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define inv2 500000004
#define mod 1000000007
#define Add(x,y) (x+y>=mod?x+y-mod:x+y)
#define Sub(x,y) (x<y?x-y+mod:x-y)
typedef long long LL;
const int N=1024+5;

int lim,Enum,H[N],nxt[N<<1],to[N<<1],f[1005][N];
char IN[MAXIN],*SS=IN,*TT=IN;

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
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void FWT(int *a,int lim,int opt)
{
	for(int i=2; i<=lim; i<<=1)
		for(int j=0,mid=i>>1; j<lim; j+=i)
			for(int k=j; k<j+mid; ++k)
			{
				int x=a[k], y=a[k+mid];
				a[k]=Add(x,y), a[k+mid]=Sub(x,y);
				if(opt==-1) a[k]=1ll*a[k]*inv2%mod, a[k+mid]=1ll*a[k+mid]*inv2%mod;
			}
}
void DFS(int x,int fa)
{
	FWT(f[x],lim,1);
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa)
		{
			DFS(v,x);
			for(int j=0; j<lim; ++j) f[x][j]=1ll*f[x][j]*f[v][j]%mod;
		}
	FWT(f[x],lim,-1), f[x][0]=Add(f[x][0],1), FWT(f[x],lim,1);
}

int main()
{
	static LL Ans[N];
	for(int T=read(); T--; )
	{
		Enum=0, memset(H,0,sizeof H);
		memset(f,0,sizeof f), memset(Ans,0,sizeof Ans);
		int n=read(),m=read(); lim=m;
		for(int i=1; i<=n; ++i) ++f[i][read()];
		for(int i=1; i<n; ++i) AE(read(),read());
		DFS(1,1);
		for(int i=1; i<=n; ++i)
		{
			FWT(f[i],lim,-1), f[i][0]=Sub(f[i][0],1);
			for(int j=0; j<m; ++j) Ans[j]+=f[i][j];
		}
		for(int i=0; i<m; ++i) printf("%d%c",int(Ans[i]%mod)," \n"[i+1==m]);//�����ʽ����
	}
	return 0;
}
