/*
找些串试试可以发现（串只有两种字符！真不懂我为什么拿abcd试半天），不管怎么切都相当于将串循环右移某些长度。
所以在循环表示里找最长的就可以了。注意答案对原串长度取min！
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=2e5+5;

char s[N];

int main()
{
	scanf("%s",s+1);
	int l=strlen(s+1),res=0;
	for(int i=1; i<=l; ++i) s[i+l]=s[i];
	l<<=1;
	for(int now=1,i=2; i<=l; ++i,res=std::max(res,now))
		if(s[i]!=s[i-1]) ++now;
		else now=1;
	printf("%d\n",std::min(res,l>>1));

	return 0;
}
