/*
sb�˺ܳ�ʱ�䡣��
ΪʲôҪ�Ѻܶ��ַ�ƴ�����أ�ͬ���ַ�����һ������ˡ�
Why so? ע�⵽һ�����Ĵ���β������������ͬ�ַ�������һ������x�ε��ַ������ԣ�����Ϊ��β���γ�x(x-1)/2�����Ĵ�����͵�����һ����Ͻ���һ���ġ�
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int tm[N];
char s[N],Ans[N];

int main()
{
	int n=read();
	scanf("%s",s+1);
	std::sort(s+1,s+1+n);
	s[n+1]='\0', puts(s+1);

	return 0;
}
