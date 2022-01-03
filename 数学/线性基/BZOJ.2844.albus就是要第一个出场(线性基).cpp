/*
1016kb	160ms
$Description$
����һ������A���� �����Ӽ��е�������������(�����ռ�) ��С����������һ����K�����е���������֤���֣���
$Solution$
��������Ի���Ȼ��ֻ�������Ի��д�������λ��
������λDP����K�����Ʒֽ⣬���K�ĵ�ǰλΪ1����ô�Ȳ�ѡ��һλ��������i-1λ����ѡ�񶼱�KС������2^i�ַ����������ռ������Ӹ��𰸡�
�����ڲ�ȥ�ص�����£�ÿ�������ܳ��ֶ�Ρ�������Ի��Ĵ�СΪsize��ԭ���ϴ�СΪn����ô���Ի��� ÿ������������2^{n-size}�Ρ�
��Ϊ����n-size���������������Ի��п���Ψһ��ʾ��������ô����һ����x������n-size��������ѡһЩXor������Ψһ�ķ���ʹ�������Ի�����������Ϊx��
���Դ��ٳ���2^{n-size}�����ˡ�
ע���K�ֽ��������Ի��ϴ������Ķ�Ӧλ�Ϸֽ⡣
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 200000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define Bit 30
#define mod 10086
#define Double(x) ((x+=mod)>=mod)&&(x-=mod)

int n,size,base[36],cnt,A[36];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int FP(int x,int k)
{
	int t=1;
	for(; k; k>>=1, x=x*x%mod)
		if(k&1) t=t*x%mod;
	return t;
}
inline void Insert(int x)
{
	for(int i=Bit; ~i; --i)
		if(x>>i & 1)
			if(base[i]) x^=base[i];
			else {base[i]=x, ++size; break;}
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) Insert(read());
	int K=read();
	for(int i=0; i<=Bit; ++i) if(base[i]) A[cnt++]=i;
	int ans=0;
	for(int i=0; i<cnt; ++i)
		if(K>>A[i] & 1) ans+=1<<i;
	printf("%d\n",(ans%mod*FP(2,n-size)%mod+1)%mod);//������1����_��

	return 0;
}
