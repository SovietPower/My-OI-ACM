/*
$Description$
��$f(x)$��ʾ����$x$��ʮ�����¸�����λ������֮�͡�����$a$������������$l,r$��ʹ��$\sum_{i=l}^rf(i)\equiv0\ (\mathbb{mod}\ a)$��
$1\leq a\leq10^{18},\ 1\leq l\leq r\leq10^{200}$����֤���ڽ⡣
$Solution$
����һ���򵥵����ʣ�$f(x+10^y)=f(x)+1,\ x\lt10^y$��
������$INF=10^{18}$����$\sum\limits_{i=0}^{INF-1}f(i)\equiv p\ (\mathbb{mod}\ a)$��
����������ʿ�֪��$\sum\limits_{i=1}^{INF}f(i)=p-f(0)+f(INF)=p+1$��
ͬ���У�$\sum\limits_{i=2}^{INF+1}f(i)=p+2...\ \sum\limits_{i=k}^{INF+k-1}f(i)=p+k$������ģ$a$�����£���
Ȼ��Ϳ��Թ����$a=p+a-p=\sum\limits_{i=a-p}^{INF+a-p-1}f(i)$��������$l=a-p,\ r=10^{18}+a-p-1$�Ϳ�������
�и���������$\sum_{i=0}^{10^{18}-1}f(i)\ \mathbb{mod}\ a$��չ��һ�£�$$\begin{aligned}\sum_{i=0}^{10^{18}-1}f(i)&=(1+2+...+9)10^{17}+10\times\sum_{i=0}^{10^{17}-1}f(i)\\&=45\times10^{17}+10(45\times10^{16}+10\times\sum_{i=0}^{10^{15}-1}f(i))\\&=...\\&=18\times45\times10^{17}=81\times10^{18}\end{aligned}$$

��������������

���и������ǣ�������$\sum\limits_{i=1+x}^{10^y+x}f(i)-\sum\limits_{i=1}^{10^y}f(i)=x,\ x\lt10^y$��ö��$y$�������$a-\sum\limits_{i=0}^{10^y}<10^y$����$x$���������������$\sum\limits_{i=1+x}^{10^y+x}f(i)=\sum\limits_{i=0}^{10^y}+a-\sum\limits_{i=0}^{10^y}=a$�ˡ�
��ҪԤ����һ��$\sum_{i=1}^{10^y}f(i)$����Ϊ������$10$����������һ��ÿ�������ִ������ɣ�����������һ��ֱ���㣩��
*/
#include <cstdio>
typedef long long LL;
const LL INF=1e18;

int main()
{
	LL a; scanf("%I64d",&a);
	LL l=a-INF*9%a*9%a;
	printf("%I64d %I64d\n",l,INF+l-1);

	return 0;
}
