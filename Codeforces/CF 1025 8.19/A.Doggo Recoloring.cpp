//ֻҪ���ҵ�һ�����ִ������ڵ���2����ɫ�Ϳ����ˡ�ע��n=1���С���
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1e5+5;

int tm[300];
char s[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int n=read(); scanf("%s",s+1);
	if(n==1) return puts("Yes"),0;
	for(int i=1; i<=n; ++i) ++tm[s[i]];
	for(int i='a'; i<='z'; ++i) if(tm[i]>1) return puts("Yes"),0;
	puts("No");

	return 0;
}
