/*
34ms	60416KB
$f[i][j]$��ʾTakahashi����һ����$i$��������$j$������$i-j$������ķ�������
��һ����$i$����ʱ���ܵõ������ĺ���������$1\sim\min(i,n)$�������˵ĺ�����֮�ͣ�����ͬ��
ת��ʱ����һ�µ�ǰ�����������������ɵ��������ɣ�һ�����ڿ��з�������
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define mod 998244353
#define Add(x,v) (x+=v)>=mod&&(x-=mod)
typedef long long LL;
const int N=4005;

int f[N][N],sum1[N],sum2[N];
char s[N];

int main()
{
	scanf("%s",s+1);
	int n=strlen(s+1);
	for(int i=1; i<=n; ++i)
	{
		if(s[i]=='0') sum1[i]=2;
		else if(s[i]=='1') sum1[i]=sum2[i]=1;
		else sum2[i]=2;
		sum1[i]+=sum1[i-1], sum2[i]+=sum2[i-1];
	}
	f[0][0]=1;
	for(int i=1,lim=n<<1; i<=lim; ++i)
	{
		int n1=sum1[std::min(i,n)],n2=sum2[std::min(i,n)];
		for(int j=0; j<=i; ++j)
			if(n1>=j && n2>=i-j)
			{
				f[i][j]=f[i-1][j];//Add
				if(j) Add(f[i][j],f[i-1][j-1]);
			}
	}
	printf("%d\n",f[n<<1][sum1[n]]);

	return 0;
}
