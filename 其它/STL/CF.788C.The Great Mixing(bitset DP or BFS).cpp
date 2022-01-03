/*
31ms	5744KB
$Description$
��k�����ϣ�Ũ��Ai�������������ٵ�������n/1000Ũ�ȵ����ϡ�
$Solution$
���������з��� (A1*x1+A2*x2+...+An*xn)/[(x1+x2+...+xn)*1000] = x/1000 
xi��ʾAiѡ������(0<=xi).1000����Լ��.
�������Ŵ���ѡ�벻ѡ���ÿ���(��Ϊʲô����ô���ǡ���̫naive��) 
ai��ʾѡ��aiŨ��1L����(a1+a2+...+am) = m*n 
��ô ��(ai-n) = 0 , -1000 <= ai-n <= 1000 
����1.������0Ϊ���BFS����ÿ��(ai-n)��Ϊһ���ߣ�ֱ��(�����ٵĲ���)���ߵ�0 
����2.����DP����f[i][sum]��ʾ��iL�Ƿ�õ�sum 
�������ص�DP��
for(i=1; i<=1000; ++i)//����֤�����ֻ��Ҫ1000L 
	for(sum=-1000; sum<=1000; ++sum)//��Ҫ��sum�Ӹ�ƫ���� 
		for(j=1; j<=k; ++j)
			if(-1000<=sum-(a[j]-n)<=1000)
				f[i][sum]|=f[i-1][sum-(a[j]-n)]
����Ȼ��O(n^3)�� 
���԰�sum��һ��ѭ����bitsetѹ��(f[i-1]����a[j]λ��������nλ)��������Ӷȣ�O((n^3)/64)��
�����֤��(�����Ҫ1kL): ����Ҫ��xŨ�ȣ���a>x��Ũ�ȡ�b<x��Ũ�ȣ���u(a-x)+v(b-x)=0 
u=x-b, v=a-xʱ���Ϳ������x����ʱu+v = a-b <= 1000 
aiֻ�迼��1000���ڵļ��� 
����T�ˡ������ò��Ӹ����� 
*/
#include <cstdio>
#include <cctype>
#include <bitset>
#define gc() getchar()
const int N=1e6+5;

int n,k,cnt,A[N];
bool vis[1005];
std::bitset<2018> f[2];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read(),k=read();
	for(int tmp,i=1; i<=k; ++i)
		if((tmp=read())<=1000) A[++cnt]=tmp,vis[tmp]=1;
	f[1][1000]=1;
	if(cnt<1000)
		for(int now=1,las,i=1; i<=1000; ++i)
		{
			las=now, now^=1;
			f[now].reset();
			for(int j=1; j<=cnt; ++j)
				f[now]|=(f[las]<<A[j])>>n;
			if(f[now][1000]) {printf("%d",i); return 0;}
		}
	else
		for(int now=1,las,i=1; i<=1000; ++i)
		{
			las=now, now^=1;
			f[now].reset();
			for(int j=0; j<=1000; ++j)
				if(vis[j]) f[now]|=(f[las]<<j)>>n;
			if(f[now][1000]) {printf("%d",i); return 0;}
		}
	printf("-1");

	return 0;
}
