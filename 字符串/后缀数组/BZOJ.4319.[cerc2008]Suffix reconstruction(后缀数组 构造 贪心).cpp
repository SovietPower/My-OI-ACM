/*
6680kb	576ms
����: ����SA���飬������SA[]��һ��ԭ�ַ���(ÿ���ַ�ΪСд��ĸ)���޽����-1. 
��������������suf(SA[j])��Ҫ����suf(SA[i]) (Ҫ����i>j) 
���Ǻ�׺�ıȽϷ�ʽ���ȱȽϵ�һλ���ٱȽ�suf(SA[i]+1)��suf(SA[j]+1) 
��suf(SA[i]+1)>suf(SA[j]+1)�������ַ�����һλ������ͬ������һ��Ҫ�ڵ�һλ����suf(SA[i])>suf(SA[j]) 
�������ַ�ʽ���죬���ܱ�֤�����ܶ���ظ�ʹ����ĸ 
��αȽ�suf(SA[i]+1)��suf(SA[j]+1)����Ҫ���˸���SA�ǿ�����rk�ġ����Ƚ�rk���ɡ�
�޽⼴ʹ���ַ�����������Сд��ĸ���� 
*/
#include <cstdio>
#include <cctype>
#define gc() getchar()
const int N=5e5+5;

int n,sa[N],rk[N],A[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) sa[i]=read();
	for(int i=1; i<=n; ++i) rk[sa[i]]=i;
	int x=0; A[sa[1]]=x;
	for(int i=2; i<=n&&x<26; ++i)
		if(rk[sa[i-1]+1]<rk[sa[i]+1]) A[sa[i]]=x;
		else A[sa[i]]=++x;
	if(x>=26) printf("-1");
	else
		for(int i=1; i<=n; ++i) printf("%c",A[i]+'a');

	return 0;
}
