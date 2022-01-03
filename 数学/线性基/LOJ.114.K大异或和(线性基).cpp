/*
��������Ի��е�KС�����ͣ�����̫������
������������Ի��ڲ�Xorһ�£�ʹ�ôӸߵ���λö��ʱ��ѡbase[i]һ���Ȳ�ѡbase[i]��(����base[i])��
������ع�һ�����Ի����Ӹߵ���λö��i�����base[i]�ڵ�jλ(j<i)��ֵ����ôXorһ��base[j]��
���� 1001(3)��0001(0)��ͬʱѡ0,3ֻ��3ҪС���ع����� 1000(3)��0001(0)������ͬʱѡ0,3��ֻѡ0��3��Ҫ��
������K�����Ʒֽ��Ϳ���ֱ�Ӷ�Ӧ�����Ի���Ӧλ��ѡ���ˡ�Ҫ��base[i]��ֵ��i��
��Ҫע��������Ի��б�ʾ����������n����˵��һ������һ����������������ع�ϵ��������Xor��Ϊ0�����������ҪʹK��1��
�ж���K>=(1<<size)�����Ի��͵ĸ�����2^{size}-1(����0)��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 100000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define Bit 51
typedef long long LL;
const int N=1e5+5;

int n,size,cnt;
LL base[69],b2[69];
char IN[MAXIN],*SS=IN,*TT=IN;

inline LL read()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void Insert(LL x)
{
	for(int i=Bit; ~i; --i)
		if(x>>i & 1)
			if(base[i]) x^=base[i];
			else {base[i]=x, ++size; break;}
}
inline LL Query(LL K)
{
	LL ans=0;
	for(int i=cnt; ~i; --i)
		if(K>>i & 1) ans^=b2[i];
	return ans;
}
void Rebuild()
{
	for(int i=Bit; ~i; --i)
		for(int j=i-1; ~j; --j)
			if(base[i]>>j & 1) base[i]^=base[j];
	for(int i=0; i<=Bit; ++i) if(base[i]) b2[cnt++]=base[i];
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) Insert(read());
	Rebuild();
	for(int Q=read(); Q--; )
	{
		LL K=read()-(size!=n);//����for�￪int��mmp 
		printf("%lld\n",(K>=(1ll<<size))?-1ll:Query(K));
	}
	return 0;
}
