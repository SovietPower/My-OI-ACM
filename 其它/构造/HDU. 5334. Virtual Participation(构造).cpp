/*
124MS	1384Kb
$Description$
����$K$������һ���ַ�����Сû�����ơ����Ȳ�����$10^5$���ַ�����ʹ�ò�ͬ���Ӵ�����ǡ��Ϊ$K$��
$K\leq 10^9$��
$Solution$
**����1��**
���Ǽ򵥵�$\begin{matrix}\underbrace{111...1}\\a_1��\end{matrix}\begin{matrix}\underbrace{222...2}\\a_2��\end{matrix}\begin{matrix}\underbrace{333....}\\a_3��..\end{matrix}$��$\sum a_i=n$����ͬ�Ӵ���Ϊ��$C_{n+1}^2-\sum_{a_i\geq 2} C_{a_i}^2$��
�����������С��$n$ʹ��$C_{n+1}^2\geq K$����$x=C_{n+1}^2-K$����һ��������**���κ�һ������������������������ɡ�**�����ԴӴ�С�ҳ�����$x$��$C_{a_i}^2\ (a_i\geq 2)$���ɡ�ʣ��$L-\sum a_i$����ֱ�Ӳ�$4\ 5\ 6\ 7\ 8...$��
�����и�����Ǵ�С�����ң��ƺ��ǻᳬ�������ģ���������ۣ���

ϸ�ڣ�$K$��С��$K=4$ʱ��ʵ��ֻ��$K=4$��$K=16$����$\sum a_i$�����$n$����Ϊ$C_n^2$���������컹�ǣ���������$K$��Сʱ�����У�ֱ�����$K$��$1$��ok��

**[����2](https://blog.csdn.net/jtjy568805874/article/details/47174185)��**
ֱ�ӿ��ǹ���$\begin{matrix}\underbrace{111...1}\\a��\end{matrix}\begin{matrix}\underbrace{222...2}\\b��\end{matrix}\begin{matrix}\underbrace{111...1}\\c��\end{matrix}$����$a\geq c$�����Ӵ���Ϊ$ab+bc+ac+a+b$��
����Ϊ$ab+bc+ac+a+b=K$��$(a+c+1)(b+c+1)=K+(c+1)^2$��ö��$c+1$��$a$����֤$a\geq c$��$a+b+c\leq 10^5$�����ҵ��⡣
$K$�ϴ��ʱ�����ö��Ч���ƺ��Ͳ���**����1**�ˡ�
*/
#include <bits/stdc++.h>
#define pc putchar
#define pb emplace_back
typedef long long LL;
const int N=1e5+5;

int main()
{
	int K;
	while(~scanf("%d",&K))
	{
		if(K<=1000)//(K==4||K==16)
		{
			printf("%d\n",K);
			for(int i=1; i<=K; ++i) printf("%d%c",1," \n"[i==K]);
			continue;
		}
		int l=1,r=44721,mid;
		while(l<r)
			if(mid=l+r>>1,mid*(mid+1)/2>=K) r=mid;
			else l=mid+1;

		int n=l,x=n*(n+1)/2-K;
		std::vector<int> vec;
		while(x)
		{
			int l=1,r=sqrt(2*x)+1,mid,ans=1;
			while(l<=r)
				if(mid=l+r>>1,mid*(mid-1)/2<=x) ans=mid,l=mid+1;
				else r=mid-1;
			vec.pb(ans), x-=ans*(ans-1)/2;
		}
		int now=1,f=0; printf("%d\n",n);
		for(auto t:vec)
		{
			for(int i=1; i<=t; ++i)
				if(f) printf(" %d",now);
				else f=1, printf("%d",now);
			++now, n-=t;
		}
		while(n--)
			if(f) printf(" %d",now++);
			else f=1, printf("%d",now++);
		pc('\n');
	}

	return 0;
}
