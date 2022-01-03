/*
1120kb	40ms
$Description$
n�������ȫͼ��������m�����ú�������������Ϊ��ɫ������������ͬɫ�������θ�����
$Solution$
ֱ����ͬɫ ����n^3 ���ᡣ��
������������C(n,3)��������ͬɫ�����θ��������һ��������������ͬ��ɫ�ıߣ���ô��һ���Ǹ���ͬɫ�����Ρ�
�����i�����ĺ����Ϊx����ô��������n-1-x���γɵĲ�ͬɫ�����θ�������x(n-1-x).
��Ϊͬһ����ͬɫ�����λᱻö�����Σ�so $Ans=C(n,3)-\frac{1}{2}\sum_{i=1}^nout[i]*(n-1-out[i])$
�о���������ŵ���˼·�Ƚ��� http://codeforces.com/contest/434/problem/E 
*/
#include <cstdio>
#include <cctype>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1005;

int n,m,red[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read(), m=read();
	while(m--) ++red[read()], ++red[read()];
	long long ans=0;
	for(int i=1; i<=n; ++i) ans+=1ll*red[i]*(n-1-red[i]);
	printf("%lld\n",1ll*n*(n-1)*(n-2)/6-(ans>>1));

	return 0;
}
