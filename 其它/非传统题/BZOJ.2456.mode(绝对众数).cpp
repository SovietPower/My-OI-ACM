/*
920kb	56ms
ά������������$now$��$cnt$��ö��$x$��
1. $now\neq a_i$����$cnt=0$����$now=a_i,cnt=1$������$cnt--$��
2. $now=a_i$��$cnt++$��
����$now$Ϊ�𰸡���Ϊ�����������ִ���������һ�롣
������õķ�ʽ�ǳ��ɽ�����Majority Element��
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
