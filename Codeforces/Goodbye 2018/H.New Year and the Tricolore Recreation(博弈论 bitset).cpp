/*
1638ms	4700KB
$Description$
Alice��Bob����Ϸ������$n,f$����ʾ��$n$�У�ÿ�����������ӡ�Alice����ѡ��һ�н������һ�����������������ƶ�$d$����Bob����ѡ��һ�н����ұ�һ�����������������ƶ�$d$����
Ҫ���ƶ�ʱһ�����Ӳ��ܿ�Խ��һ�����ӣ���$d$�����������������ĳ˻�����$d\neq f$����˭��Ӯ��
$n\leq10^5,\ �������ֵ\leq10^5$��
$Solution$
����һ�����Ӿ�����С�ڶ�����������֮��ľ��룬�����������Ӿ�����Сһ����������֮��ľ��롣����������λ��Ϊ$a,b,c$��ÿһ��ʵ�ʾ�������������Ϊ$c-b-1,b-a-1$��$nim$��Ϸ��
��������������Ϊ$x$����Ϸ��$SG$��������$2n$����Ϸ��$sg$ֵȫ����������ɡ���������㣬��Ȼ��$sg(x)=\mathbb{mex}_{d\in P}\{sg(x-d)\}$�����Ǹ��Ӷ���$n^2$�ġ�
������֣�$sg$ֵ��󲻻ᳬ��$100$����Ҳ��֪����ô�ܵó��ģ������ǿ�$100$��$bitset\ A[i]$���ֱ��ʾÿ�������Ƿ����$sg$ֵΪ$i$�ĺ�̡���Ԥ����$d\in P$��$bitset\ S$��������С������$sg(i)$ʱ����`for`һ�鿴���������ĸ�$sg$ֵ�ĺ�̣�Ȼ��$A[sg(i)]|=S<<i$���ɣ��������ܵ�$i$��λ�ã���
���Ӷ�$O(\frac{n^2}{w})$��
*/
#include <cstdio>
#include <cctype>
#include <bitset>
#include <algorithm>
#define gc() getchar()
#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e5+1,M=102;

int sg[N];
std::bitset<N> S,A[M];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
void Init()
{
	static int P[N],mn[N];
	int cnt=0;
	for(int i=2; i<N; ++i)
	{
		if(!mn[i]) P[++cnt]=i;
		for(int j=1; j<=cnt&&i*P[j]<N; ++j)
		{
			mn[i*P[j]]=i;
			if(!(i%P[j])) break;
		}
	}
	for(int i=2; i<N; ++i) if(!mn[mn[i]]) S[i]=1;
}

int main()
{
	int n=read(); Init(), S[read()]=0;
	for(int i=0; i<N; ++i)
	{
		while(A[sg[i]][i]) ++sg[i];
		A[sg[i]]|=S<<i;
	}
	int ans=0;
	for(int a,b,c; n--; ) a=read(),b=read(),c=read(),ans^=sg[b-a-1]^sg[c-b-1]; 
	puts(ans?"Alice\nBob":"Bob\nAlice");

	return 0;
}
