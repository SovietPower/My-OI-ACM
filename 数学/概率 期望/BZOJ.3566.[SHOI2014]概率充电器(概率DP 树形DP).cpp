/*
38344kb	3684ms
$Description$
����һ������ÿ������һ���ɵ���Ԫ����ÿ������$p\%$�ĸ��ʵ��磬ÿ��Ԫ��������$q\%$�ĸ��ʱ���磬�������ж��ٸ�Ԫ���е硣
$n\leq 5\times10^5$��
$Solution$
ÿ����Ĺ��׶���$1$������ֱ����ÿ����ͨ��ĸ���$F_i$���𰸾���$\sum F_i$��
��$F_x$�ֳɣ����ڵ�ͨ���$x$�����ĸ���$g_x$����$x$��������ͨ���$x$�����ĸ���$f_x$��
���������������¼�$A,B$���ɸ��ʼӷ���ʽ��$P(A+B)=P(A)+P(B)-P(A)P(B)$��$F_x=f_x+g_x-f_xg_x$��
��$p_x$��ʾ$x$����ͨ��ĸ��ʣ�$p_{(x,v)}$��ʾ��$(x,v)$ͨ��ĸ��ʣ���ô$f_x=p_x+\sum_{v\in son[x]}f_vp_{(x,v)}$��ע������ļӷ��Ǹ��ʵļӷ�������ټ�ȥͬʱ�����ĸ��ʣ���
$g_x$��ת�ƣ�����$F_{fa}$��ȥ$x$ת�Ƶ�$fa$�ĸ��ʡ���Ϊ$P(A)=\frac{P(A+B)-P(B)}{1-P(B)}$�����Գ�ȥ$x$�Ĺ�����$fa$ͨ��ĸ���$q=\frac{F_{fa}-f_xp_{(fa,x)}}{1-f_xp_{(fa,x)}}$������$g_x=q\times p_{(fa,x)}$��
Ȼ�����������
**ps��**��ʵ���Ǻܶ��ڶ���DFS��$P(B)=1$��ʱ�򣨳�$0$��$P(A)$Ӧ�õ��ڶ���...
Ȼ������ˮ�����������$P(B)=1$�������

��������$F_x$��ʾ$x$��ͨ��ĸ��ʣ�$F_x=f_xg_x$����ôֻ���������Ĺ��ף���$h_v$��ʾ$v$�����ڵ㹱�׵ĸ��ʣ���$h_v=f_v+(1-f_v)(1-p_{(x,v)})$����$f_x=(1-p_x)\prod h_v$��
�ٿ��Ǹ��ڵ�Ĺ���$g_x$��ͬ������ֱ�Ӽ���$x$��$fa$�Ĺ��ף���$g_x=\frac{F_{fa}}{h_x}$��ע������$h_x=0$���������
ͬ������DP��OK����

���˰���ԭ���Ǳ�Ȩû��`double`...
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define eps 1e-10
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=5e5+5;

int Enum,H[N],nxt[N<<1],to[N<<1];
double f[N],F[N],pe[N<<1];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int w,int v,int u)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, pe[Enum]=1.0*w/100;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, pe[Enum]=pe[Enum-1];
}
void DFS1(int x,int fa)
{
	double b;
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa)
			DFS1(v,x), b=f[v]*pe[i], f[x]=f[x]+b-f[x]*b;
}
void DFS2(int x,int fa)
{
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa)
		{
			double b=f[v]*pe[i];
			if(fabs(1-b)<eps) F[v]=1;//=1��ô���ǵİ�...���϶���ôд��=-=
			else
			{
				double q=(F[x]-b)/(1-b)*pe[i];
				F[v]=f[v]+q-f[v]*q;
			}
			DFS2(v,x);
		}
}

int main()
{
	const int n=read();
	for(int i=1; i<n; ++i) AE(read(),read(),read());
	for(int i=1; i<=n; ++i) f[i]=1.0*read()/100;
	DFS1(1,1), F[1]=f[1], DFS2(1,1);
	double ans=0;
	for(int i=1; i<=n; ++i) ans+=F[i];
	printf("%.6f\n",ans);

	return 0;
}
