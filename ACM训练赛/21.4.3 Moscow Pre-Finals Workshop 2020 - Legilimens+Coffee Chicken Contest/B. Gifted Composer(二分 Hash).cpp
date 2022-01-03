/*
655ms	46000KB
$Description$
��ʼ��һ�����ַ�����$n$�β�����ÿ���ڴ���ǰ�������һ���ַ�����ÿ�β������ַ�����ѭ����������
$s$��ѭ����$t$����Ϊ��$s$��$k$��$t$��ɻ���$k$��$t$��$t$��һ��ǰ׺��ɡ�
$n\leq 10^6$��
$Solution$
����$s$�ͳ���$k$���ж�$s$�Ƿ�������ѭ���� �ȼ��� �ж�**�Ƿ���$s[1,n-k]==s[k+1,n]$**����ϣ����$O(1)$�жϡ�

�и������ǣ�����Ϊ$k$��ѭ���ڻ���$k$ʱ�̳��֣�������$k+t$ʱ����ʧ�����Ժ󲻻��ٳ��֡�
��Ϊ��һ���ַ�����$k$ѭ������ʧ������ǰ��������ַ�����Ҳ�����ٳ�Ϊѭ���ڡ�
�����ȶ����մ���ϣ��ö��ѭ���ڳ���$k$����������ʧ��ʱ��$k+t$��ʹ$[k,k+t]$�Ĵ�$+1$���ɡ�
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb emplace_back
#define seed 31
typedef long long LL;
typedef unsigned long long ull;
const int N=1e6+6;

int sum[N],L[N],R[N];
ull hs[N*3],pw[N];
char s[N*3];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline char Get()
{
	char c=gc(); while(!isalpha(c)) c=gc();
	return c;
}
inline ull Hash(int l,int r)
{
	return hs[r]-hs[l-1]*pw[r-l+1];
}
bool Check(int t,int k)
{
	return Hash(L[t],R[t]-k)==Hash(L[t]+k,R[t]);
}

int main()
{
	int n=read(),h=1e6+1,t=1e6+1;
	static char ss[5];
	for(int i=1; i<=n; ++i)
	{
		if(Get()=='a') scanf("%s",ss), s[t++]=ss[0]=='s'?ss[1]:ss[0];
		else scanf("%s",ss), s[--h]=ss[0]=='s'?ss[1]:ss[0];
		L[i]=h, R[i]=t-1;
	}

	pw[0]=1;
	for(int i=1; i<=n; ++i) pw[i]=pw[i-1]*seed;
	for(int i=h; i<t; ++i) hs[i]=hs[i-1]*seed+s[i]-'a';

	for(int i=1; i<=n; ++i)
	{
		int l=i,r=n,mid;
		while(l<r)
			if(Check(mid=l+r+1>>1,i)) l=mid;
			else r=mid-1;
		++sum[i], --sum[l+1];
	}
	for(int i=1; i<=n; ++i) sum[i]+=sum[i-1], printf("%d\n",sum[i]);

	return 0;
}
