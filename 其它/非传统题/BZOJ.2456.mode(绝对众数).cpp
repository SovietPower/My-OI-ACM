/*
920kb	56ms
维护两个变量，$now$和$cnt$；枚举$x$：
1. $now\neq a_i$：若$cnt=0$，则$now=a_i,cnt=1$，否则$cnt--$。
2. $now=a_i$：$cnt++$。
最后的$now$为答案。因为绝对众数出现次数超过了一半。
这题更好的方式是出成交互：Majority Element。
*/
#include <cstdio>
#include <cctype>
//#define gc() getchar()
#define MAXIN 100000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)

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
	int n=read(),now,cnt=0,t;
	while(n--)
		if((t=read())==now) ++cnt;
		else if(!cnt) now=t, cnt=1;
		else --cnt;
	printf("%d\n",now);

	return 0;
}
