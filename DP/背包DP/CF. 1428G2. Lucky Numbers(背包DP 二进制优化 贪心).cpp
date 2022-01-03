/*
295ms	7800KB
$Description$
��$x$�ļ�ֵ����Ϊ��$x$ʮ���Ʊ�ʾ�е�$i$λΪ$3$���λ��ֵΪ$F_i$����λΪ$6$��ֵΪ$2F_i$��Ϊ$9$��ֵΪ$3F_i$������Ϊ$0$��Ȼ������λ�ϼ�ֵ��ӡ�
����$K$��$Q$��ѯ�ʣ�ÿ��ѯ�ʸ���$n$��������$K$�����ĺ�Ϊ$n$����£���$K$����������ֵ�͡�
$n,K\leq 999999,q\leq 10^5$��
$Solution$
����$K$����������λ��ֻ��$0,3,6,9$����ôÿһλ�����Կ��� ����Ϊ$3K$�����Ϊ$3\times10^i$����ֵΪ$F_i$����Ʒ������$6$����Ʒ������Ϊ$n$�Ķ��ر�����
��ô������ô�þ����ܶ����λ����$0,3,6,9$��
���ʱÿλ�Ƕ����ģ�����ĳһλ���������������λ�ֱ���$a,b$������$0,3,6,9$������$a+b\leq 9$����ô���Խ�$a,b$����$0,a+b$������$a+b>9$����Խ�$a,b$����$9,a+b-9$��
���Զ���ÿһλ�������������������ֻ��һ������λ��Ϊ$0,3,6,9$������Щ��Ϊ$0,3,6,9$��λ�ŵ�һ�����ϣ�������$K-1$����������λ��Ϊ$0,3,6,9$��ʣ��һ�������⡣
��������һ������ÿλ$3(K-1)$����Ʒ���������Ż����ر�����Ȼ�����ʣ�µ�һ������ok��
���Ӷ�$O(6m\log K)$��
ϸ�ڣ�Ԥ����һ�£��Ȱѵ������Ǹ�����ֵ�����������������
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
typedef long long LL;
const int N=1e6+5,INF=1e6;
const LL V[]={0,0,0,1,0,0,2,0,0,3};

int F[10];
LL f[N];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline void Upd(int v,LL val)
{
	for(int i=INF-1; i>=v; --i) f[i]=std::max(f[i],f[i-v]+val);
}
void Update(int num,int v,int val)
{
	num=std::min(num,INF/v);
	for(int x=1; x<num; x<<=1) Upd(x*v,1ll*x*val), num-=x;
	Upd(num*v,1ll*num*val);
}

int main()
{
	int K=read();
	for(int i=0; i<=5; ++i) F[i]=read();
	for(int i=1,pw=1,las=1,bit=-1; i<INF; ++i)
		i==pw&&(las=pw,pw*=10,++bit), f[i]=f[i%las]+V[i/las]*F[bit];
	for(int i=0,pw=3; i<=5; ++i,pw*=10) Update(3*(K-1),pw,F[i]);

	for(int Q=read(); Q--; printf("%lld\n",f[read()]));

	return 0;
}
