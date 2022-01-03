/*
1116kb	40ms
ÿһλ�Ƕ����ģ�����̰��+ģ������ˡ�
�һ���ΪҪ���Ͻ�ɶ�ģ�ѧɵ�ˣ�����ֱ�����ĳλѡ1��m�����������ˡ�
Ҫ��ĳ��λ��0/1ͨ��n���ŵ�ֵ��Ԥ��������ˡ�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;

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
	int n=read(),m=read(),opt0=0,opt1=(1<<29)-1;
	while(n--)
	{
		register char c=gc();for(;!isupper(c);c=gc());
		int x=read();
		switch(c)
		{
			case 'A': opt0&=x, opt1&=x; break;
			case 'O': opt0|=x, opt1|=x; break;
			case 'X': opt0^=x, opt1^=x; break;
		}
	}
	int ans=0;
	for(int i=29; ~i; --i)
		if(opt0>>i&1) ans|=1<<i;
		else if(m>=1<<i && opt1>>i&1) m-=1<<i, ans|=1<<i;
	printf("%d\n",ans);

	return 0;
}
