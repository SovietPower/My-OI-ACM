/*
Ԥ�����һ�������кϷ�״̬�ļ���(������λ���������3)
��f[i][s1][s2]Ϊ �����ڱ�λ�õļ���Ϊs1����ǰ��Ϊi����һ�з��õ�λ��Ϊ����s2 ������ܰڷ����� 
���ڰڷ�λ����ǰ���ж��йأ�����Ҫ����ά����¼һ��ǰһ��״̬ 
ö�ٵ�i�е�״̬�󣬻�Ҫö�� i-1��i-2�� ���i�кϷ���״̬���������кϷ������ֵ������ǰ״̬ 
f[i][s1][s2] = max{f[i-1][s2][s3]} + sum[s1]  ->  ö��s1��s2��s3
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;
const int N=12;

int n,m,cnt,p[105],sum[105],f[102][105][105],Map[102];

inline int read()
{
	int now=0,f=1;register char c=getchar();
	for(;!isdigit(c);c=getchar())
	  if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=getchar());
	return now*f;
}

int main()
{
	n=read(),m=read();
	char s[15];
	for(int i=1;i<=n;++i)
	{
		scanf("%s",s);
		for(int j=0;j<m;++j)
			if(s[j]=='H')
				Map[i]|=(1<<j);
	}
	for(int s=0;s<(1<<m);++s)//Ԥ�������� ��Ŀ����Ҫ�� �����п��� 
		if(!(s&(s>>1)) && !(s&(s>>2)))
			p[++cnt]=s;
	for(int i=1;i<=cnt;++i)
	{
		for(int t=p[i];t;t>>=1)
			if(t&1)
				++sum[i];//ÿ������µ��ڱ��� 
		if(!(p[i]&Map[1]))
			f[1][i][0]=sum[i];
	}
	for(int i=1;i<=cnt;++i)//��Ϊһ�е�״̬��ǰ�����йأ����ڶ��е�ֻ���һ���йأ��������� 
		if(!(p[i]&Map[2]))
			for(int j=1;j<=cnt;++j)
				if(!(p[i]&p[j]) && !(p[j]&Map[1]))//sum�����Ƴ���f(�������ͼ��Ϊ0)�����Ա���Ҫ���Ƿ������ͼ 
					f[2][i][j]=sum[j]+sum[i];
	for(int l=3;l<=n;++l)
		for(int i=1;i<=cnt;++i)//ö�ٵ�ǰ��״̬s1 
			if(!(p[i]&Map[l]))
				for(int j=1;j<=cnt;++j)//ö�ٵ�l-1��״̬s2 
					if(!(p[i]&p[j]))
					{
						int Max=0;
						for(int k=1;k<=cnt;++k)//ö�ٵ�l-2��״̬s3 
							if(!(p[i]&p[k]) && !(p[j]&p[k]) && Max<f[l-1][j][k])
								Max=f[l-1][j][k];
						f[l][i][j]=Max+sum[i];
					}
	int res=0;
	for(int i=1;i<=cnt;++i)
		for(int j=1;j<=cnt;++j)
			res=max(res,f[n][i][j]);
	printf("%lld",res);

	return 0;
}
