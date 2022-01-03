/*
868kb	272ms
题目要求将数分成分成$m$段，使得下面这个式子最小($\mu=\frac{\sum_{i=1}^ma_i}{m}$是平均数，$a_i$为第$i$段的和): 
$$\frac{\sum_{i-1}^m(\mu -a_i)^2}{m}*m^2$$ 
$m$可以乘进去，得: 
$$m\times\sum_{i=1}^m(a_i-\frac{sum}{m})^2$$ 
注意到其中有$m$个$sum$，于是连同乘上的$m$一起提出来就是$m\times\sum_{i=1}^m(a_i^2-2*a_i*\frac{sum}{m})+sum^2$ 
$\sum_{i=1}^m2*a_i$又是一个$sum$，于是最终化简为
$$m\times\sum_{i=1}^ma_i^2-sum^2$$ 
使$\sum_{i=1}^ma_i^2$最小，转移方程是$f[i][j]=f[i-1][k]+(s_j-s_k)^2$
容易想到有单调性，用斜率优化即可。（与$i$相关的项为kx，其余为y）
$$f_j-f_k+s_j^2-s_k^2\leq 2*s_i*(s_j-s_k)$$
注意初始化。。即到某点时分一组的值。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=3005;

int n,m,sum[N],f[N][2],q[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int X(int j,int k){
	return sum[j]-sum[k];
}
inline int Y(int j,int k,int s){
	return f[j][s]-f[k][s]+(sum[j]*sum[j]-sum[k]*sum[k]);
}
inline int Calc_F(int i,int j,int s){
	return f[j][s]+(sum[i]-sum[j])*(sum[i]-sum[j]);
}

int main()
{
	n=read(),m=read();
	for(int i=1; i<=n; ++i) sum[i]=sum[i-1]+read(),f[i][0]=sum[i]*sum[i];
	int p=0;
	for(int j=2; j<=m; ++j)
	{
		int h=1,t=1; q[1]=j-1;//这可以初始化为这个，i从j枚举。
		for(int i=j; i<=n; ++i)
		{
			while(h<t && Y(q[h+1],q[h],p)<=2*sum[i]*X(q[h+1],q[h])) ++h;
			f[i][p^1]=Calc_F(i,q[h],p);
			while(h<t && 1ll*Y(i,q[t],p)*X(q[t],q[t-1])<=1ll*Y(q[t],q[t-1],p)*X(i,q[t])) --t;
			q[++t]=i;
		}
		p^=1;
	}
	printf("%d",m*f[n][p]-sum[n]*sum[n]);

	return 0;
}
