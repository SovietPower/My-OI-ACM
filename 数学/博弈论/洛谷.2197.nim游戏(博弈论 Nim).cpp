/*
���ֱ�ʤ(���ֱذ�,P-position)���ҽ���n��ʯ��������Ϊ0��
����0һ����P-position�� 
����a1^a2^a3^...^an=K 
��K!=0����һ�������ҵ�һ��ai��ai��K�����λ��1��Ϊ1����Ȼai > ai^K����ô���԰�ai���ai^K������ͳ���a1^a2^...^an^ai^K = K^K = 0 (���־ʹ���P-position) 
��K==0������ȡһ����Ȼ����ʹK��Ϊ0 
*/
#include <cstdio>
#include <cctype>
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int MAXIN=1e6;

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
	int t=read(),n,res;
	while(t--)
	{
		n=read(), res=0;
		while(n--) res^=read();
		puts(res?"Yes":"No");
	}
	return 0;
}
