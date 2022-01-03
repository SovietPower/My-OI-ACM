/*
106864kb	1520ms
�����ϵ�Hash��ǰ׺�Ͳ�࣬��άHashҲ�Ͷ�άǰ׺�Ͳ���ˡ�
����������r*c��С����hashֵ���ٶ�ѯ�ʵľ���Hash�Ϳ����ˡ�
�����������s[r]-s[l-1]*pow[r-l+1]������s[i-r][j-c]������r*c�Σ��˸�pow[r]*pow[c]�����ˡ�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define P 100000000
#define base1 12289
#define base2 786433
typedef unsigned int uint;//������unsigned long long����û̫���ð�...��Ȼ�����ٵ�T�� 
const int N=1005;

uint A[N][N],sum[N][N],pw1[N],pw2[N];
bool Hash[P];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int read01()
{
	register char c=gc();
	for(;!isdigit(c);c=gc());
	return c-'0';
}

int main()
{
	int n=read(),m=read(),r=read(),c=read();
	for(int i=1; i<=n; ++i)	
		for(int j=1; j<=m; ++j) sum[i][j]=read01();
	pw1[0]=pw2[0]=1;
	for(int i=1; i<=n; ++i) pw1[i]=pw1[i-1]*base1;
	for(int i=1; i<=m; ++i) pw2[i]=pw2[i-1]*base2;
	for(int i=2; i<=n; ++i)//Row
		for(int j=1; j<=m; ++j) sum[i][j]+=sum[i-1][j]*base1;
	for(int i=1; i<=n; ++i)//Column
		for(int j=2; j<=m; ++j) sum[i][j]+=sum[i][j-1]*base2;
	for(int i=r; i<=n; ++i)
		for(int j=c; j<=m; ++j)
		{
			uint hash=sum[i][j]-sum[i-r][j]*pw1[r]-sum[i][j-c]*pw2[c]+sum[i-r][j-c]*pw1[r]*pw2[c];
			Hash[hash%P]=1;
		}
	for(int Q=read(); Q--; )
	{
		for(int i=1; i<=r; ++i)
			for(int j=1; j<=c; ++j) A[i][j]=read01();
		for(int i=2; i<=r; ++i)
			for(int j=1; j<=c; ++j) A[i][j]+=A[i-1][j]*base1;
		for(int i=1; i<=r; ++i)
			for(int j=2; j<=c; ++j) A[i][j]+=A[i][j-1]*base2;
		puts(Hash[A[r][c]%P]?"1":"0");
	}

	return 0;
}