/*
�����˶�ֻ������bi�й�ϵ����
���Կ���ö��bi�����ھ��Ǽ���ѡ��bi���� �����˵ȴ���ֵ��������ʦ��ֵ 
��һ������Ȼ����ֱ�ӵ��ư���ÿ��һ���������֮ǰ������ 
������ʦֻ��Ҫ��һ��A��B���Լ�֮ǰ�ж���bj���Ժͺ�����bk�� 
ע��C�ܴ�Ļ�����һ��(�϶�������C�Ĺ���)����������*C��longlong(unsigned longlongҲ��ˮ��ȥ��) 
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5;

int n,m,tm[N],b[N],num[N],sum[N];
LL A,B,C,pre[N],suf[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline LL readll()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
//	freopen("exam.in","r",stdin);
//	freopen("exam.out","w",stdout);

	A=read(),B=read(),C=readll(),m=read(),n=read();//n,m
	int Max=0,Min=1e9;
	for(int i=1; i<=m; ++i) tm[i]=read(),++num[tm[i]];
	for(int i=1; i<=n; ++i) b[i]=read(),++sum[b[i]];
	for(int i=1; i<=m; ++i) Min=std::min(Min,tm[i]),Max=std::max(Max,tm[i]);
	for(int i=1; i<=n; ++i) Min=std::min(Min,b[i]),Max=std::max(Max,b[i]);
	LL now=0;
	for(int i=1; i<=Max; ++i) pre[i]=pre[i-1]+now, now+=sum[i];
	now=0;
	for(int i=Max; i; --i) suf[i]=suf[i+1]+now, now+=sum[i];
	if(C==1e16)
	{
		Min=1e9;
		for(int i=1; i<=m; ++i) Min=std::min(Min,tm[i]);
		LL tmp;
		if(A>=B) printf("%lld",B*suf[Min]);
		else tmp=std::max(suf[Min]-pre[Min],0ll),printf("%lld",A*std::min(pre[Min],suf[Min])+B*tmp);
		return 0;
	}
	LL res=1e15,tmp,peo=0; now=0;
	for(int i=Min; i<=Max; ++i)
	{
		peo+=now;
		if(A>=B) res=std::min(res,C*peo+B*suf[i]);
		else tmp=std::max(suf[i]-pre[i],0ll),res=std::min(res,C*peo+A*std::min(pre[i],suf[i])+B*tmp);
		now+=num[i];
	}
	printf("%lld",res);

	return 0;
}
