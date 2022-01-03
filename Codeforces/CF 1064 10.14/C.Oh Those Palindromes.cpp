/*
sb了很长时间。。
为什么要把很多字符拼起来呢，同种字符放在一起就行了。
Why so? 注意到一个回文串首尾至少是两个相同字符，所以一个出现x次的字符最多可以（以它为首尾）形成x(x-1)/2个回文串，这和单个放一起的上界是一样的。
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
