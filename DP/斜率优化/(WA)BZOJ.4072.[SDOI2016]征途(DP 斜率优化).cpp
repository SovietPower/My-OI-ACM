/*
题目要求使得下面这个式子最小($\mu=\frac{\sum_{i=1}^ma_i}{m}$是平均数，$a_i$为第$i$段的和): $$\frac{\sum_{i-1}^m(\mu -a_i)^2}{m}*m^2$$ 
$m$可以乘进去，得: $$m\times\sum_{i=1}^m(\frac{sum}{m}-a_i)^2$$ 
那是个平方，于是写成俩，把$m$乘进一个去，得: $$\frac{sum^2}{m}-2*a_i*sum+a_i^2*m$$ 
其中 $a_i=sum_{now}-sum_i$；$\frac{sum^2}{m}$是一个常数，直接用。
显然(...)具有决策单调性。然后展开一堆式子，得到。。不写了。
但是不对，暴力也可能和答案差1，因为$sum^2$不一定整除$m$，但那个常数的位置还没法弄掉分母，所以计算f[]的时候就gg。
~~怕不是还能用double水~~ 
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=3005;

int n,m,w,sum[N],f[N],f2[N][N],q[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int X(int j,int k){
	return m*(sum[j]-sum[k]);
}
inline long long Y(int j,int k){
	return f[j]-f[k]+2*(sum[j]-sum[k])*sum[n]+(sum[j]*sum[j]-sum[k]*sum[k])*m;
}
inline int Calc_F(int i,int j){
	int ai=sum[i]-sum[j];
	return f[j]+w-2*ai*sum[n]+ai*ai*m;
}

int main()
{
	n=read(),m=read();
	for(int i=1; i<=n; ++i) sum[i]=sum[i-1]+read();
	w=sum[n]*sum[n]/m;
	memset(f2,0x3f,sizeof f2);
	f2[0][0]=1;
	for(int i=1; i<=m; ++i)
	{
//		int h=1,t=1; q[1]=0;
		for(int j=i; j<=n; ++j)
		{
//			while(h<t && Y(q[h+1],q[h])<=2*sum[j]*X(q[h+1],q[h])) ++h;
//			f[j]=Calc_F(j,q[h]);
//			while(h<t && Y(i,q[t])*X(q[t],q[t-1])<=Y(q[t],q[t-1])*X(i,q[t])) --t;
//			q[++t]=j;
			for(int k=0; k<j; ++k)
			{
				int ai=sum[j]-sum[k];
				f2[i][j]=std::min(f2[i][j],f2[i-1][k]+w-2*ai*sum[n]+ai*ai*m);
			}
		}
	}
	printf("%d",f2[m][n]);

	return 0;
}
