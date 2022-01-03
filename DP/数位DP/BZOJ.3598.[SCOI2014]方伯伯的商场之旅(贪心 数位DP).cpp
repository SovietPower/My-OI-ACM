/*
49592kb	404ms
�ȿ��ǣ�����ȷ����һ�����������ƶ��������٣������Ƶ��ĸ�λ�����ţ���
�������Ƕ��Ƶ��±�1λ�ã��輯�ϵ�Ϊ1������ô�ƶ����±�2��1��ȴ��۲�Ϊ���±�<1��ʯ������-�±�>1��ʯ�����͡�
�����Ϊ������ô���Ƶ�1�Ĵ��ۼ���������ϵ��Ϊ2...����һֱ�ı伯�ϵ㣬ֱ�� �±�<p��ʯ������ >= �±�>p��ʯ�����͡���ô�Ƶ�p�������ŵġ�
�����о��ܶԡ���ô֤����
���Ƿ���ʽ�������ʵ����ǰ׺�ͣ��ұ��Ǻ�׺�͡���Ϊʯ�����Ǹ�����������p�ƶ���ǰ׺���ǵ����ģ���׺�͵ݼ���
��������� ǰ׺�� >= ��׺�� �������ǰ׺�;���Զ���ڵ��ں�׺���ˡ�
��ô���Ƕ�[l,r]�����������������̰�ġ�
��������Ҫ������������ϵ�1�Ĵ��ۺ͡������������λDP������������ĸ������ø�����ͣ���
Ȼ��ö��p=2~nλ�����ǿ����� ��pΪ�ֽ磬ǰ׺��λ�� С�� ��׺��λ�� �� ��[0,r] �����ĸ���������ÿ��������ٵĴ��۾���ǰ׺��-��׺�͡�
��Ϊ��λ���������230������ֱ��ö��������״̬��ͬ����λDP��
f[i][j][k][0/1]��ʾ��ǰ����iλ������λ��Ϊj��pλ֮ǰ����λ��Ϊk���Ƿ��Ͻ磬�����ĸ�����
���⻹����ֱ�Ӽ���k��һά����
���仯�ͺ�д�Ķ��ˣ����죩��
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int N=52,M=245;

int A[N];
LL g[N][2],sum[N][2],f[N][M][M][2];

LL Calc(LL x,int base)
{
	int n=0;
	for(; x; x/=base) A[++n]=x%base;
	std::reverse(A+1,A+1+n);//
	printf("%d %d\n",base,n*(base-1));

	memset(g,0,sizeof g), memset(sum,0,sizeof sum);
	g[0][1]=1;
	for(int i=0; i<n; ++i)//�����Ǵ�0���㡣��
	{
		LL v=g[i][1]; int ai=A[i+1];
		g[i+1][1]+=v, sum[i+1][1]=sum[i][1]+v*i*ai;
		for(int j=0; j<ai; ++j) g[i+1][0]+=v, sum[i+1][0]+=sum[i][1]+v*i*j;
		v=g[i][0];
		for(int j=0; j<base; ++j) g[i+1][0]+=v, sum[i+1][0]+=sum[i][0]+v*i*j;
	}

	LL ans=sum[n][0]+sum[n][1];
	for(int p=1; p<n; ++p)
	{
		f[0][0][0][1]=1;
		for(int i=0; i<n; ++i)
		{
			int ai=A[i+1];
			if(i+1<=p)
			{
				LL v;
				for(int j=0,lim=i*(base-1); j<=lim; ++j)
				{
					if(v=f[i][j][j][1])//�ò�ֱ�ۡ���
					{
						f[i+1][j+ai][j+ai][1]+=v;//+=
						for(int k=0; k<ai; ++k) f[i+1][j+k][j+k][0]+=v;
					}
					if(v=f[i][j][j][0])
						for(int k=0; k<base; ++k) f[i+1][j+k][j+k][0]+=v;
				}
			}
			else
			{
				LL v;
				for(int j=0,lim=i*(base-1); j<=lim; ++j)
					for(int k=0,lim2=p*(base-1); k<=lim2;  ++k)
					{
						if(v=f[i][j][k][1])
						{
							f[i+1][j+ai][k][1]+=v;
							for(int l=0; l<ai; ++l) f[i+1][j+l][k][0]+=v;
						}
						if(v=f[i][j][k][0])
							for(int l=0; l<base; ++l) f[i+1][j+l][k][0]+=v;
					}
			}
		}
		for(int i=0,lim=p*(base-1); i<=lim; ++i)//pre
			for(int j=i+1,lim2=n*(base-1); i+j<=lim2; ++j)//suf
				ans+=(i-j)*(f[n][i+j][i][0]+f[n][i+j][i][1]);
		for(int i=1; i<=n; ++i)
			for(int j=0,lim=i*(base-1); j<=lim; ++j)
				for(int k=0,lim2=p*(base-1); k<=lim2; ++k)
					f[i][j][k][0]=0, f[i][j][k][1]=0;
	}
	return ans;
}

int main()
{
	LL L,R; int K; scanf("%lld%lld%d",&L,&R,&K);
	printf("%lld\n",Calc(R,K)-Calc(L-1,K));
	return 0;
}
