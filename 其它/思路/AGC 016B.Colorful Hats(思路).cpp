/*
2ms	896KB
����ĳ��Ԫ�ط�������һ�£��Ϳ���֪��n��Ԫ�ص�����ɫ�����ˡ�
�����a[1]�������ۣ�
��1����ɫ��ĳ��Ԫ����ͬ��������ɫ��Ϊa[1]��a[i]Ҫô����a[1]��i��ĳ��Ԫ����ɫ��ͬ���Ǹ���ΪA����Ҫô����a[1]+1��i����ɫΨһ���Ǹ���ΪB����
Ҫ���㣺B������n-1�����и�i��1��ɫ��ͬ���������ɫ��=(A+1)/2+BҪ���ڵ���a[1]��ͬʱ�����Ͻ����ƣ���������ɫ��=1+BҪС�ڵ���a[1]��
��1����ɫ��Ψһ�ģ�������ɫ��Ϊa[1]+1��a[i]Ҫô����a[1]��i����ɫΨһ���Ǹ���ΪA����Ҫô����a[1]+1����ĳ��Ԫ����ɫ��ͬ���Ǹ���ΪB����
Ҫ���㣺B����Ϊ1�����Դ���1Ҳ����Ϊ0���������ɫ��=1+A+B/2Ҫ���ڵ���a[1]+1��ͬʱҲ���Ͻ����ƣ���������ɫ��=1+A+(B!=0)ҪС�ڵ���a[1]+1��
��Ȼ�����������ʵ�ʺͱ���д���������Сֵ�ж��ٸ�һ����ֻ��ִ��һ��check����
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e6+5;

int a[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
bool Check1(const int n)
{
	int A=0,B=0;
	for(int i=2,a1=a[1]; i<=n; ++i)
		if(a[i]==a1) ++A;
		else if(a[i]==a1-1) ++B;
		else return 0;
	return B<n-1&&(A+1>>1)+B>=a[1]&&B<a[1];//�Ͻ����ư����� 
}
bool Check2(const int n)
{
	int A=0,B=0;
	for(int i=2,a1=a[1]; i<=n; ++i)
		if(a[i]==a1) ++A;
		else if(a[i]==a1+1) ++B;
		else return 0;
	return B!=1&&A+(B>>1)>=a[1]&&A+(B!=0)<=a[1];
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) a[i]=read();
	puts(Check1(n)||Check2(n)?"Yes":"No");
	return 0;
}
