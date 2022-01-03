/*
$Description$
��������n����ʿ���ֱ�λ��1,2,3,...,n�����ǵ��ƶ��ٶ���ͬ����ʼ�ƶ�������֪����������ʿ����ʱ������50%�ĸ��ʻ�ʤ��ʧ�ܵ���ʿ�����ˡ�
����ʿ�ƶ���0,n+1λ��ʱ����ᷴת�������ұߵ���ʿ�����ĸ��ʡ�
$Solution$
��Ŀ���ٶȡ�ʱ�䶼���޹ؽ�Ҫ�ġ���n����ʿ��ҪӮ��һ���Ǵ����������д�����ʿ��
��ô��$f[i][j]$��ʾǰi����ʿ����j����ʿ���ĸ��ʡ�
������ô�󡣵�i����ʿ�����������Ӧ��ǰi-1����ʿ��k-j�����ҵ���ʿ�����(Ȼ��go_die->1/2)������ʣ��j��.
��$f[i][j]=\sum_{k=j}^{i-1}f[i-1][k]*(\frac{1}{2})^{k-j+1}$ 
��$k=j$ʱ�ķ�����������Ի���Ϊ$$f[i][j]=\frac{1}{2}*(f[i-1][j]+f[i][j+1])$$ 
�����ʿi���ң���ô$$f[i][j]=f[i-1][j-1]$$ 
�������ֻ��һ����ʿ���ң�������������������������ʿ����0���ۻصġ�
���Ը�ÿ��$f[i][1]+=\sum_{j=1}^{i-1}f[i-1][j]*(\frac{1}{2})^j$ 
��$$(f[i][1]+=\frac{1}{2}*(f[i-1][1]+f[i][2]))=f[i-1][1]+f[i][2]$$ 
$Ans=\sum_{i=1}^{n-1}f[n-1][i]*(\frac{1}{2})^i$����$$Ans=\frac{f[n][1]}{2}$$ 
ע����ʿn��Ҫǿ�������ߵģ��������ǣ���
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#define gc() getchar()
#define inv (500000004)
#define mod (1000000007)//����2ȫ����Ϊ����Ԫ(��ĿҪ��)������Ҳ��ֱ�������� 
const int N=1005;

int n,f[N][N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int T=read();
	for(int cas=1; cas<=T; ++cas)
	{
		memset(f,0,sizeof f);
		n=read(), read();
		f[1][1]=1;
		for(int i=2; i<=n; ++i)
		{
			if(read()&&i!=n)
				for(int j=1; j<=i; ++j)
					f[i][j]=f[i-1][j-1];
			else{
				for(int j=i-1; j>1; --j)
					f[i][j]=1ll*inv*(f[i-1][j]+f[i][j+1])%mod;
				f[i][1]=(f[i-1][1]+f[i][2])%mod;
			}
		}
		printf("Case #%d: %I64d\n",cas,1ll*f[n][1]*inv%mod);
	}
	return 0;
}
