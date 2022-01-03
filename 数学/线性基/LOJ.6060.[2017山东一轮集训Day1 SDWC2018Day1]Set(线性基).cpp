/*
2092kb	424ms
������Ԫ�ص�����Ϊ$s$����ô$x_1+x_2=x_1+x_1\ ^{\wedge}s$��
$s$��ȷ���ġ����ǴӸ�λ����λö��$s$�Ķ�����λ������ǰλ$s$Ϊ$1$����$x_1$��$0$��$1$������ͬ������$x_1$��һλ������$1$���������$1$����������������$x_1+x_2$���
����$x_1$��С��Ҫ�󣬾�����$s$Ϊ$1$ʱ��$x_1$��ȡ$0$��ȡ$0$��
������λ$\text{xor}$�ģ����ǹ������Ի���

ԭ�������Ի����ԴӸ�λ����λΪ���ȼ��ġ��������ǣ�$s$Ϊ$0$��λ���ȼ���ߣ���θ�λ���ȼ���ߡ�
��ô�ڰ�һ�������뵽���Ի���ʱ������ѡ$s$Ϊ$0$��λ���룬Ȼ����ȥ���Բ���$s$Ϊ$1$��λ���������һ�β��ܲ����ȥ��˵�������$s$Ϊ$0$��λ����Ӱ�찡��Ҳ�Ͳ���Ӱ��$x_1+x_2$����ˣ�
��$x_1$ʱ��$s$Ϊ$0$��λ����Ϊ$1$�����$s$Ϊ$1$��λ����Ϊ$0$���ɡ�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define BIT 59
#define gc() getchar()
#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;

LL A[N],base[BIT+2];
char IN[MAXIN],*SS=IN,*TT=IN;

inline LL read()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void Insert(LL x,LL s)
{
	for(int i=BIT; ~i; --i)
		if(!(s>>i&1) && x>>i&1)
			if(base[i]) x^=base[i];
			else {base[i]=x; return;}
	for(int i=BIT; ~i; --i)
		if(/*s>>i&1 &&*/ x>>i&1)
			if(base[i]) x^=base[i];
			else {base[i]=x; return;}
}

int main()
{
	const int n=read(); LL s=0;
	for(int i=1; i<=n; ++i) s^=A[i]=read();
	for(int i=1; i<=n; ++i) Insert(A[i],s);
	LL ans=0;
	for(int i=BIT; ~i; --i) if(!(s>>i&1) && !(ans>>i&1)) ans^=base[i];
	for(int i=BIT; ~i; --i) if(s>>i&1 && ans>>i&1) ans^=base[i];
	printf("%lld\n",ans);

	return 0;
}
