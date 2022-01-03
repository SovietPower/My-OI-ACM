/*
$Description$
![](https://img2018.cnblogs.com/blog/1143196/201810/1143196-20181013075426036-577478146.png)
����$n$����$a_i$�����ж��ٸ��Ӽ����㣺�����͵�������������AND��
$n\leq 50,\ a_i\lt 2^{13}$��
$Solution$
https://www.cnblogs.com/SovietPower/p/9781573.html
������f[i][j][k]��ʾǰ$i$������������Ϊj������Ϊk�ķ����������Ӷ�$O(n*4^{13})$��
����λ��������ʣ������ô�õ�ĳһλ��1��&Ҫ����������һλΪ1��^ֻ������һλΪ1��������ż�ԡ�
����������13λ������s��ʾ13λ01��״̬��2��ʾȫ1��0/1��ʾ��ż�ԣ����ٴ�һ��ѡ�����ĸ�����
����DP����$O(n*3^{13})$�ˡ�
����ֱ��f[i][s][0/1]����д������·��dalao�̡�������״̬����Ҳͦ�鷳��
������Ϊx��λ���Ϊy����Ϊ���룬����x����y��y���й�ϵ�ģ�Ҳ���ǵ�ѡ����������ʱ��x&y=y������x&y=0��
��ô�����еĺϷ���$j,k$ʵ��û��$2^{13}*2^{13}$��ô�ࡣ
���кϷ�״̬����x&y=y����x&y=0��Ҳ����yҪô��x���Ӽ���Ҫô��xû�н��������������������
��Ϊ�еڶ����������ֻ�����͵������Ӽ����С�������һ�鲹����״̬Ҳ���ԡ�
��xx=x&(~y)�����Ƿ���xx����ȷ���ģ�������Ϊx,y�Ĺ�ϵ��ѡ������ʱx����xx|y������x=xx��
����ö��y����ö��~y���Ӽ���Ҫ&8191���õ�xx����DP��ʱ�������ż�԰�xת�����������ˣ���״̬��&(~y)����Ȼ��Ϳ���ͬ����ֱ��ת�ơ�
״̬��Ϊ$O(3^{13})$��
����$f[n][status(0,0)][0]+\sum_s f[n][status(s,s)][1]$��
���Ӷ�Ҳ��$O(n*3^{13})$��
DP����ҲҪlonglong������Ļ���Ҳ������int����
id[][]��ö��˳��ȷ���±����һ����
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define all 8191
#define cnt 1594323
typedef long long LL;
const int N=8192+3,M=1594323+3;

int And[M],XX[M],id[N][N];
LL F[M][2],G[M][2];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int Init()
{
	int n=0;
	for(int y=0; y<=all; ++y)//y
	{
		int ss=(~y)&all;
		for(int x=ss; ; x=(x-1)&ss)
		{
			id[y][x]=++n;
			XX[n]=x, And[n]=y;
			if(!x) break;
		}
	}
	return n;
}

int main()
{
//	const int all=8191;
//	const int cnt=1594323;
	Init();
	int n=read(); LL (*f)[2]=F,(*g)[2]=G;
	f[id[all][0]][0]=1;
	for(int i=1,ai; i<=n; ++i)
	{
		ai=read(), std::swap(f,g);
		memcpy(f,g,sizeof F);//f[i][s]=f[i-1][s]
		for(int j=1; j<=cnt; ++j)
			for(int k=0; k<2; ++k)
			{
				if(!g[j][k]) continue;
				int x=XX[j],y=And[j];
				k && (x|=y);
				x^=ai, y&=ai;
				x&=(~y);
				f[id[y][x]][k^1]+=g[j][k];
			}
	}
	LL ans=f[id[0][0]][0];
	for(int i=1; i<=cnt; ++i) if(!XX[i]) ans+=f[i][1];//x==y xx=0
	printf("%lld\n",ans);

	return 0;
}
