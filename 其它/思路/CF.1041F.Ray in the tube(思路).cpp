/*
171ms	1500KB
$Description$
������ƽ����$x$���ֱ��$A,B$��ÿ��ֱ���ϵ�ĳЩλ���д�����������Ҫȷ��$A,B$����������������λ��$x_A,x_B$��ʹ��һ��������$x_A\to x_B$���������$A,B$���䣩���ܹ������Ĵ�������������Ƕ��١�
$Solution$
~~�ɹ�ķ��䶨�ɿ�֪��~~�����������������ˮƽ������ȷ���ģ����������Ϊ$dx$���������û��ʲô���ˣ���
��ô�ᱻ��$x_A$�����Ĺ����յ��ĵ㣬��$A$������������Ϊ$x_A+2k\cdot dx$����$B$������������Ϊ$x_A+(2k-1)\cdot dx$��
���Ƿ�����$dx=a\cdot b$��$a$Ϊ������$b$Ϊ$1$��ż������$dx'=\frac{dx}{a}=b$����������$dx$�������ĵ㣬��������
���仰˵���ǣ�����$dx=����$���Ա�$dx'=1$ȡ����$dx=ż��$���Ա�$dx'=ĳ��2����$ȡ����
���Դ��ڣ���$1$��ģ��������ӵ�$dx$û�б�Ҫ�жϡ���ô����ֻ��Ҫ�ж�$dx=2^l,l\geq 0$���������һ����$\log(10^9)$�֡�
����һ��ȷ����$dx$�����$A$����������$x_1,x_2$ͬʱ����������ô����$x_1\equiv x_2\mod{(2 \cdot dx)}$��
���ѡ��$A$���ϵ�$x_1$��$B$���ϵ�һ����$x_2$��Ҫ����������Ҫ����$x_1+dx\equiv x_2\mod{(2 \cdot dx)}$��
�������ǰ�$A$�㼯�е�ÿ��$x_i$��$2dx$ȡģ��$B$���е�ÿ��$x_i$����һ��$dx$�ٶ�$2dx$ȡģ����
Ȼ���������ͬ�ķ�Ϊһ�飬��������һ����ǵ�ǰ���Ž⡣
sort��ֱ��map�����ԡ����Ӷ�$O(n\log n\log(10^9))$��
ע��$ans$��ʼ��$2$����
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 150000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=2e5+5;

int n,A[N],tmp[N],Now;
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
	int n=read(); read();
	for(int i=1; i<=n; ++i) A[i]=read();
	int m=read(),tot=n+m; read();
	for(int i=n+1; i<=tot; ++i) A[i]=read();

	int ans=2/*!*/; tmp[tot+1]=2e9+1;
	for(int dx=1; dx<=int(1e9); dx<<=1)
	{
		int mod=dx<<1;
		for(int i=1; i<=n; ++i) tmp[i]=A[i]%mod;
		for(int i=n+1; i<=tot; ++i) tmp[i]=(A[i]+dx)%mod;
		std::sort(tmp+1,tmp+1+tot);
		for(int i=1,las=1; i<=tot; ++i)
			if(tmp[i+1]!=tmp[i]) ans=std::max(ans,i-las+1), las=i+1;
	}
	printf("%d\n",ans);

	return 0;
}
