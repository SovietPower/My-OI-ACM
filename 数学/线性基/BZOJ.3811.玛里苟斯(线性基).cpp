/*
2096kb	728ms
������ĿҪ�������ȷ��С������������Ƶ���֪��Ҫô��������Ҫô��һλС��$.5$��������$.25,\ .125$ʲô�ġ�
��$k$���ۣ�����$k=2$Ϊ������������������$S$�����������Ʋ�֣�ÿһλ��Ϊ$b_i=0/1$����ô����$(b_02^0+b_12^1+...+b_m2^m)(b_02^0+b_12^1+...+b_m2^m)=b_0b_02^0+b_0b_12^1+b_0b_22^2+...b_mb_m2^{m+m}$$=\sum_i\sum_jb_ib_j2^{i+j}$��
��ô����$b_i,b_j$�����Ĺ�����$\frac{P}{2^n}\times2^{i+j}$��$P$��$i,j$��λ��Ϊ$1$�ķ�������
��ô��$b_{i,j}$��ʾ��$i$���������Ʋ�ֺ�ĵ�$j$λ��$x_i$��ʾ������Ƿ������ѡ���ļ����У���$i,j$λ��Ϊ$1$�ķ������������и������飺
$$\begin{matrix}x_1b_{1,0}\oplus x_2b_{2,0}\oplus...\oplus x_nb_{n,0}=0/1\\x_1b_{1,0}\oplus x_2b_{2,0}\oplus...\oplus x_nb_{n,0}=0/1\\\dots\\x_1b_{1,i}\oplus x_2b_{2,i}\oplus...\oplus x_nb_{n,i}=1\\\dots\\x_1b_{1,j}\oplus x_2b_{2,j}\oplus...\oplus x_nb_{n,j}=1\\\dots\\x_1b_{1,m}\oplus x_2b_{2,m}\oplus...\oplus x_nb_{n,m}=0/1\end{matrix}$$

�����˸о������ȥ$i,j$�ķ��̵���ʽӦ����$0/1$�ɣ���ƪ������д����$0$��
����������飬���Է���ֻ����$t\leq k$��$x_i$����Ψһ��ģ�����$n-t$��$x_i$�������⡣���Է�����Ϊ$2^{n-t}$�����׾�Ϊ$2^{i+j-t}$��
��$i\neq j$ʱ��$i+j\geq1,\ t\leq2$������$2^{i+j-t}\geq0.5$��
��$i=j$ʱ��$i+j\geq0,\ t\leq1$��������$2^{i+j-t}\geq0.5$��
��չ��$k\geq2$���������ѡ����λ��$k'$λ�ǻ�����ͬ�ģ���Ϊ$i,j,l...$����ô����������ʽΪ$1$�ĵ�ʽ��$k'$������$i+j+l+...\geq0+1+2+...=\frac{k(k-1)}{2}\geq k-1\geq t-1$������$i+j+l+...-t\geq-1$������$2^{i+j+l+...-t}\geq0.5$��
$k=1$ʱ����ȻҲ������
���ϣ���Ҫô��������Ҫô��һλС��$.5$��

-----
���Ҫע��������ݷ�Χ����С��$2^{63}$����ô�ƺ�����$a_i^k\lt2^{63}$��$a_i\lt\frac{2^{63}}{k}$��
���Ǹ�����Ϊ������$k=1$��$a_i\lt2^{63}$�����Ǵ���$2^{63}\leq a_i\lt2^{64}$Ҳ�ǿ��Եģ���Ϊ�Ͼ�����ƽ��ֵ����һλ���ǿ��ܱ����͵���һλȥ�ġ�����Ӧ����$a_i\lt\frac{2^{64}}{k}$��$k=1$��Ҫ`unsigned long long`����
Ȼ��û����������ôд�ģ�д��Χ�Ķ���$a_i\lt\frac{2^{63}}{k}$��...���ҾͲ�֪��Ϊɶ������`unsigned long long`�ˡ�
���������ݣ�ȷʵ���ֵ��`18446727131960884031`$>2^{63}$��������$2^{63}-0.5$ 233��ǿ��

-----
������ô������$k$�ֱ���⡣

$k=1$��
��ÿһλ�ֱ��ǡ���ĳһλΪ$1$������$t$����Ϊ$0$����$n-t$������ôѡ����������λΪ$1$�ķ������ǣ�$\sum_{i\ is\ odd}C_n^i2^{n-t}$��ż�����ķ�������$\sum_{i\ is\ even}C_n^i2^{n-t}$��
��$C_n^1+C_n^3+C_n^5+...=2^{n-1}=C_n^0+C_n^2+C_n^4...$
Ҳ����ѡ����λΪ$1$�����ĸ���Ϊ������ż���ĸ�����һ���ġ���ôֻҪ$t\geq0$����λΪ$1$Ϊ$0$�ĸ�����һ���ġ�
������һ����Щλ�ϳ��ֹ�$1$������������$2$�ͺ��ˡ�

$k=2$��
����˵�˴𰸿���д��$\sum_i\sum_jb_ib_j2^{i+j}$������ֱ��$\log^2$ö��$i,j$��
$b_i$Ϊ$1$�ĸ��ʺ�$k=1$ʱ�����һ�����������һ������$i$λΪ$1$����ô����$\frac12$��������$0$�����������������$i$λ��Ϊ$0$�Ҵ�������$j$λ��Ϊ$0$����ô���׾���$\frac14\times2^{i+j}$��
��Ҫע��������ÿ����$i,j$λ����ͬ�����ٴ���һ��������$i,j$λ��Ϊ$1$����ô$i,j$Ϊ$1$��ͬʱ���ֵģ�������$\frac12$��

$k\geq3$��
��ʱ$a_i\lt2^{22}$�����Ի��е�Ԫ�ظ���������$22$�����Կ���ֱ��$2^{cnt}$ö�����Ի���Ԫ�ؼ��ϣ������Ի�Ԫ�ظ���Ϊ$cnt$����
���Ի���ÿ���Ӽ����ֵĸ��ʶ���$2^n\times2^{n-cnt}=\frac{1}{2^{cnt}}$������Ӽ�����$x^k$���һ�¼��ɡ�
��Ҫע����ǳ�$2^{cnt}$֮ǰ$x^k$�ǿ��Գ���$2^{63}$�ġ���Ҫ��$x$��ʾ��$\lfloor\frac{x}{2^{cnt}}\rfloor\times2^{cnt}+x\%2^{cnt}$��
��Ϊ��$\lfloor\frac{x^k}{2^{cnt}}\rfloor\times x+\lfloor\frac{(x^k\%2^{cnt})\times x}{2^{cnt}}\rfloor=\lfloor\frac{x^{k+1}}{2^{cnt}}\rfloor$��
> ֤������$x^k=a\times2^{cnt}+b\ (b<2^{cnt})$����ô��ʽ���$=ax+\lfloor\frac{bx}{2^{cnt}}\rfloor$����ʽ�ұ�$=\lfloor\frac{x^k\times x}{2^{cnt}}\rfloor=\lfloor\frac{ax2^{cnt}+bx}{2^{cnt}}\rfloor=ax+\lfloor\frac{bx}{2^{cnt}}\rfloor=��ʽ$��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
typedef unsigned long long ull;
const int N=1e5+5;

ull A[N];
int cnt,base[30],b[30];
char IN[MAXIN],*SS=IN,*TT=IN;

inline ull read()
{
	ull now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
void Subtask1(int n)
{
	ull ans=0;
	for(int i=1; i<=n; ++i) ans|=A[i];
	printf("%llu",ans>>1);
	if(ans&1) printf(".5");
	putchar('\n');
}
void Subtask2(int n)
{
	ull x=0,y=0;
	for(int a=0; a<32; ++a)
	{
		bool f1=0;
		for(int i=1; i<=n; ++i) if(A[i]>>a&1) {f1=1; break;}
		if(!f1) continue;
		for(int b=0; b<32; ++b)
		{
			bool f2=0;
			for(int i=1; i<=n; ++i) if(A[i]>>b&1) {f2=1; break;}
			if(!f2) continue;
			bool f3=0;
			for(int i=1; i<=n; ++i) if((A[i]>>a&1)^(A[i]>>b&1)) {f3=1; break;}
			if(a+b-f3-1>=0) x+=1ull<<a+b-f3-1;
			else ++y;//+0.5
		}
	}
	printf("%llu",x+=y>>1);
	if(y&1) printf(".5");
	putchar('\n');
}
inline void Insert(int x)
{
	for(int i=21; ~i; --i)
		if(x>>i&1)
			if(base[i]) x^=base[i];
			else {b[cnt++]=base[i]=x; break;}
}
void Subtask3(int n,int K)
{
	for(int i=1; i<=n; ++i) Insert(A[i]);
	ull ansx=0,ansy=0;
	const int lim=1<<cnt;
	for(int s=0; s<lim; ++s)
	{
		ull val=0,x=0,y=1;
		for(int i=0; i<cnt; ++i) s>>i&1&&(val^=b[i]);
		for(int i=1; i<=K; ++i)
			x*=val, y*=val, x+=y>>cnt, y&=lim-1;
		ansx+=x, ansy+=y;
	}
	ansx+=ansy>>cnt, ansy&=lim-1;
	printf("%llu",ansx);
	if(ansy) printf(".5");
	putchar('\n');
}

int main()
{
	int n=read(),K=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	if(K==1) Subtask1(n);
	else if(K==2) Subtask2(n);
	else Subtask3(n,K);

	return 0;
}
