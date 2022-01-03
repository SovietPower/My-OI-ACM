/*
8ms	896KB
$Description$
����$n$���ǣ������ֱ�Ϊ$a_i$��Alice��Bob����������ÿ�ο��ԳԵ�����һ�ѣ�Ҳ����ÿ�Ѹ��Ե�һ�����޷����������䣬��˭��Ӯ��
$n\leq10^5,\ a_i\leq10^9$��
$Solution$
![](https://img2018.cnblogs.com/blog/1143196/201903/1143196-20190304204039085-1876471685.png)
����ͼ������= = ~~��Ȼȷʵ�е��~~
������$5$���ǣ������������������Ƿ���ÿ�β��������õ������һ�л����±ߵ�һ�С���ô���Կ��ɣ���ʼ��$(1,1)$��ÿ�����һ�������һ����
������$SG$���߽�λ�õ�$SG$ֵ��ȻΪ$0$����$SG$ֻ��$01$����ȡֵ��ʾʤ��������λ�õ�$SG$��������������Ǹ��ӶȻ�ը��
�����Է��֣���ȥ�����һ�㣬ͬһ�����Խ����ϵ�λ�õ�$SG$ֵ����ͬ�ģ���$sg(x,y)=sg(x+1,y+1)$��
������$sg(x+1,y+1)=1$��$(x,y)$�ĺ�̵ĺ�̻���$(x+1,y+1)$��һ��ʤ̬������$sg(x,y)=1$����$sg(x+1,y+1)=0$����$(x,y)$�ĺ�̴��ڱذ�̬�ĺ�̣�����$sg(x,y)=0$��
Ȼ�����ǾͿ����ҵ�һ������$i+1>A_{i+1}$��λ��$(i,i)$����$(i,i)$��$SG$ֵ�����ұ��ϱ߸��ж��ٸ�λ�����Ǽ��ɡ�
��������Ǻܳ��õĽ��ۣ�**ͬһ���Խ����ϵ�$SG$ֵ��ͬ**��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <functional>
#define gc() getchar()
#define MAXIN 300000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;

int A[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

int main()
{
	const int n=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	std::sort(A+1,A+1+n,std::greater<int>());
	for(int i=1; i<=n; ++i)
		if(i+1>A[i+1])
		{
			int ans=0;
			for(int j=i+1; A[j]==i; ++j) ans^=1;
			ans|=A[i]-i&1;
			puts(ans?"First":"Second");
			return 0;
		}

	return 0;
}
