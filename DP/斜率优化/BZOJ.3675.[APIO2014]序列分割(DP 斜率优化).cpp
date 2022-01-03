/*
4436kb	20008ms
�ƺ��и�˳����鷳������дһ�²�ͬ�и�˳���ֵ���֣�����һ���ġ�����ʵ�ʺ��и�˳���޹أ�ֻ���������йء�
��$f[i][k]$��ʾ�����$i$���У�һ���Ѿ�����$k$�ε�����ֵ��ע�ⲻҪ����������ļ�ֵ��
��ô$f[i][k]=\min\{f[j][k-1]+s_j*(s_i-s_j)\}$��
$f[j][k-1]$������һ��DP�õ���$f$���顣��$k$���ڵ�һ��ѭ�����Ϳ���б���Ż��ˡ�
���Ӷ�$O(nk)$����Ȼ���Դ�Ȩ�����Ż���$O(n\log k)$��
UOJ��ԭ���ݰ�QAQ�������ȣ���ʵ���ȺżӸ��Ⱥžͺ��ˣ�������������ʵ�Ӹ�fread�͹��ˣ���
�����껹��ȡ������...
*/
#include <cstdio>
#include <cctype>
#include<cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
//#define Sqr(x) (1ll*x*x)
#define X(i,j) (s[i]-s[j])//delta_x
#define Y(i,j) (f[i]-f[j]-sqr[i]+sqr[j])
//#define Slope(i,j) (!X(i,j)?0:1.0*Y(i,j)/X(i,j))
typedef long long LL;
const int N=1e5+5;

int s[N],q[N],id[N][202];
LL f[N],g[N],sqr[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline double Slope(int i,int j)
{
	return !X(i,j)?1e15:1.0*Y(i,j)/X(i,j);
}
//void Print(int x,int k)
//{
//	if(!x) return;
//	Print(id[x][k],k-1);
//	printf("%d ",x);
//}

int main()
{
	static int Ans[202];
	int n=read(),m=read();
	for(int i=1; i<=n; ++i) s[i]=s[i-1]+read(),sqr[i]=1ll*s[i]*s[i];
	for(int k=1; k<=m; ++k)
	{
		int h=1,t=1;
		for(int i=k; i<=n; ++i)
		{
			while(h<t && Slope(q[h+1],q[h])>=-s[i]) ++h;//>= not >!
			g[i]=f[q[h]]+1ll*s[q[h]]*(s[i]-s[q[h]]), id[i][k]=q[h];
			while(h<t && Slope(q[t],q[t-1])<=Slope(i,q[t])) --t;
			q[++t]=i;
		}
//		for(int i=k; i<=n; ++i) f[i]=g[i];
		memcpy(f,g,n+1<<3);
	}
	printf("%lld\n",f[n]);
//	Print(id[n][m],m-1);
	int t=0,x=id[n][m];
	while(x) Ans[++t]=x, x=id[x][--m];
	while(t) printf("%d ",Ans[t--]);

	return 0;
}
