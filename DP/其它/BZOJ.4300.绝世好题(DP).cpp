/*
1016kb	64ms
$Description$
��������$ai$����$ai$��һ���������$bi$������b[i]&b[i-1]!=0��$b_i\&b_{i-1}\neq0(2\leq i\leq len)$����
$Solution$
����ֻ��Ҫ�жϣ�$b$���е���һ�����뵱ǰ����������һλ��Ϊ0���ɡ�
f[i][j]��ʾǰi�����У�����$b$���е����һ������jλΪ1����������г��ȡ�
��������ôֻ��$\log^2$��ת�ơ���
��ǰ��ת��aiΪ1��λ����Ϊ����λת�Ƶ���λ�ö���һ���ģ�������������ȡ��max�����ˡ�
���Ӷ�$O(n\log a)$��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define BIT 30

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
	static int f[33];
	int n=read();
	for(int i=1; i<=n; ++i)
	{
		int ai=read(),tmp=0;
		for(int j=0; j<=BIT; ++j)
			if(ai>>j&1) tmp=std::max(tmp,f[j]);
		++tmp;
		for(int j=0; j<=BIT; ++j)
			if(ai>>j&1) f[j]=tmp;
	}
	int ans=0;
	for(int i=0; i<=BIT; ++i) ans=std::max(ans,f[i]);
	printf("%d\n",ans);

	return 0;
}
