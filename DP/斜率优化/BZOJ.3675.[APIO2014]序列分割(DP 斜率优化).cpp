/*
4436kb	20008ms
似乎切割顺序很麻烦。但是写一下不同切割顺序的值发现，答案是一样的。所以实际和切割顺序无关，只与切在哪有关。
令$f[i][k]$表示这次在$i$处切，一共已经切了$k$次的最大价值。注意不要算上其它块的价值。
那么$f[i][k]=\min\{f[j][k-1]+s_j*(s_i-s_j)\}$。
$f[j][k-1]$就是上一次DP得到的$f$数组。把$k$放在第一层循环，就可以斜率优化了。
复杂度$O(nk)$。当然可以带权二分优化到$O(n\log k)$。
UOJ是原数据吧QAQ，卡精度（其实不等号加个等号就好了）还卡常数（其实加个fread就过了）。
横坐标还是取正数吧...
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
