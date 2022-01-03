/*
��ĿҪ��ʹ���������ʽ����С($\mu=\frac{\sum_{i=1}^ma_i}{m}$��ƽ������$a_i$Ϊ��$i$�εĺ�): $$\frac{\sum_{i-1}^m(\mu -a_i)^2}{m}*m^2$$ 
$m$���Գ˽�ȥ����: $$m\times\sum_{i=1}^m(\frac{sum}{m}-a_i)^2$$ 
���Ǹ�ƽ��������д��������$m$�˽�һ��ȥ����: $$\frac{sum^2}{m}-2*a_i*sum+a_i^2*m$$ 
���� $a_i=sum_{now}-sum_i$��$\frac{sum^2}{m}$��һ��������ֱ���á�
��Ȼ(...)���о��ߵ����ԡ�Ȼ��չ��һ��ʽ�ӣ��õ�������д�ˡ�
���ǲ��ԣ�����Ҳ���ܺʹ𰸲�1����Ϊ$sum^2$��һ������$m$�����Ǹ�������λ�û�û��Ū����ĸ�����Լ���f[]��ʱ���gg��
~~�²��ǻ�����doubleˮ~~ 
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
