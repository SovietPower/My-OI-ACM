/*
868kb	272ms
��ĿҪ�����ֳɷֳ�$m$�Σ�ʹ���������ʽ����С($\mu=\frac{\sum_{i=1}^ma_i}{m}$��ƽ������$a_i$Ϊ��$i$�εĺ�): 
$$\frac{\sum_{i-1}^m(\mu -a_i)^2}{m}*m^2$$ 
$m$���Գ˽�ȥ����: 
$$m\times\sum_{i=1}^m(a_i-\frac{sum}{m})^2$$ 
ע�⵽������$m$��$sum$��������ͬ���ϵ�$m$һ�����������$m\times\sum_{i=1}^m(a_i^2-2*a_i*\frac{sum}{m})+sum^2$ 
$\sum_{i=1}^m2*a_i$����һ��$sum$���������ջ���Ϊ
$$m\times\sum_{i=1}^ma_i^2-sum^2$$ 
ʹ$\sum_{i=1}^ma_i^2$��С��ת�Ʒ�����$f[i][j]=f[i-1][k]+(s_j-s_k)^2$
�����뵽�е����ԣ���б���Ż����ɡ�����$i$��ص���Ϊkx������Ϊy��
$$f_j-f_k+s_j^2-s_k^2\leq 2*s_i*(s_j-s_k)$$
ע���ʼ����������ĳ��ʱ��һ���ֵ��
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
		int h=1,t=1; q[1]=j-1;//����Գ�ʼ��Ϊ�����i��jö�١�
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
