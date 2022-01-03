/*
1120kb	4ms
$Description$
��$n$��ʯ�ӡ����˵�һ���⣬ÿ��ʯ�Ӹ�����������ǰһ�ѵ�ʯ�Ӹ�������������������ÿ�ο��Դ�һ��ʯ�����õ�������ʯ�ӣ���Ҫ��֤��������Ȼ�����ʼʱ��������˭û��ʯ�ӿ���ʱ�䡣�������Ƿ��ʤ��
$Solution$
�����������������������Ĳ�Ǹ�����ô�ǲ������$d_i=a_i-a_{i-1}$���������ߵ�$i$�ѵ�$x$��ʯ�ӣ�Ӱ����$d_i$-=$x$��$d_{i+1}$+=$x$�����൱�ڴ�$d_i$����$x$����$d_{i+1}$��
��Ȼԭ����ͶԲ������������Ľ���$Nim$�ǵȼ۵ģ�Ȼ�����������
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1005;

int A[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0; register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	for(int T=read(); T--;)
	{
		const int n=read();
		for(int i=1; i<=n; ++i) A[i]=read();
		int s=0;
		for(int i=n; i>=1; i-=2) s^=(A[i]-A[i-1]);
		puts(s?"TAK":"NIE");
	}

	return 0;
}
