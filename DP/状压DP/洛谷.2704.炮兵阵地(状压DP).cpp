/*
预处理出一行中所有合法状态的集合(即两个位置至少相距3)
设f[i][s1][s2]为 放置炮兵位置的集合为s1，当前行为i，上一行放置的位置为集合s2 的最多能摆放数量 
由于摆放位置与前两行都有关，所以要开三维，记录一个前一行状态 
枚举第i行的状态后，还要枚举 i-1、i-2行 与第i行合法的状态，将上两行合法的最大值，给当前状态 
f[i][s1][s2] = max{f[i-1][s2][s3]} + sum[s1]  ->  枚举s1、s2、s3
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
	for(int s=0;s<(1<<m);++s)//预处理满足 题目本身要求 的所有可能 
		if(!(s&(s>>1)) && !(s&(s>>2)))
			p[++cnt]=s;
	for(int i=1;i<=cnt;++i)
	{
		for(int t=p[i];t;t>>=1)
			if(t&1)
				++sum[i];//每种情况下的炮兵数 
		if(!(p[i]&Map[1]))
			f[1][i][0]=sum[i];
	}
	for(int i=1;i<=cnt;++i)//因为一行的状态与前两行有关，但第二行的只与第一行有关，单独处理 
		if(!(p[i]&Map[2]))
			for(int j=1;j<=cnt;++j)
				if(!(p[i]&p[j]) && !(p[j]&Map[1]))//sum不是推出的f(不满足地图则为0)，所以必须要判是否满足地图 
					f[2][i][j]=sum[j]+sum[i];
	for(int l=3;l<=n;++l)
		for(int i=1;i<=cnt;++i)//枚举当前行状态s1 
			if(!(p[i]&Map[l]))
				for(int j=1;j<=cnt;++j)//枚举第l-1行状态s2 
					if(!(p[i]&p[j]))
					{
						int Max=0;
						for(int k=1;k<=cnt;++k)//枚举第l-2行状态s3 
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
