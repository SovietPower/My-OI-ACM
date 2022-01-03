/*
171ms	9600KB
������֪Ҫѡ�����ֵ�i����ô��0��ʼ�ߣ�ÿ����i�����i�ɷ��ã���ôһ������i���ö�����ȥ������Ҫ�˻ص�����Ŀɷ���λ�á�����ʵ��Ȼ������
n/1+n/2+n/3+...+n/n��O(nln(n))�����Ӷ�û���Ⱑ��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 1000000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1e6+5;
const long long INF=1e17;

int n,m,K,A[N],move[N];
bool block[N];
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
	n=read(),m=read(),K=read();
	int delta=0;
	for(int p,i=1; i<=m; ++i)
	{
		block[p=read()]=1;
		move[p]=move[p-1]+1;
		delta=std::max(delta,move[p]);
	}
	if(delta>=K||block[0]) {puts("-1"); return 0;}
	for(int i=1; i<=K; ++i) A[i]=read();
	long long res=INF;
	for(int i=delta+1; i<=K; ++i)
	{
		int now=0; long long sum=0;
		while(now<n)
			if(block[now]) now-=move[now];
			else now+=i, sum+=A[i];
		res=std::min(res,sum);
	}
	printf("%I64d",res==INF?-1ll:res);

	return 0;
}
