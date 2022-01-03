/*
190ms	1704kb
$Description$
交互库中有三个排好序的，长度分别为$n_a,n_b,n_c$的数组$a,b,c$。你需要求出所有元素中第$k$小的数。你可以调用至多$100$次询问某个数组中的第几个数的函数。$n_a,n_b,n_c\leq 10^5$。
$Solution$
显然的做法是先枚举这个数在哪个数组中，再在三个数组中二分。这个次数是$log^2$的。
我们如果每次确定一些数比第$k$个数小，那我们可以直接将这些数删掉。
（可以假设数组是无限长的(补上INF)）这样每次访问三个数组的第$\lfloor\frac{k}{3}\rfloor$个元素，把这个元素最小的数组的前$\lfloor\frac{k}{3}\rfloor$个数删掉。这样$k$每次缩小$\frac{1}{3}$，当$k\leq2$时我们就可以很容易得到答案。$k\leq 3\times 10^5$最多被缩小$31$次变为$2$，操作次数为$93$。$k=2$时直接询问三个数组前两个位置就可以得到答案。这样总操作次数不会超过$99$。
*/
#include "kth.h"
#include <algorithm>

int query_kth(int n_a, int n_b, int n_c, int k)
{
	const int myINF=0x7fffffff;
	int nowa=-1,nowb=-1,nowc=-1,delta,a,b,c,mn;
	while(k>2)
	{
		delta=k/3;
		a=nowa+delta<=n_a?get_a(nowa+delta):myINF,
		b=nowb+delta<=n_b?get_b(nowb+delta):myINF,
		c=nowc+delta<=n_c?get_c(nowc+delta):myINF;
		mn=std::min(a,std::min(b,c));
		if(mn==a) nowa+=delta;
		else if(mn==b) nowb+=delta;
		else if(mn==c) nowc+=delta;
		k-=delta;
	}
	int A[7];
	A[1]=get_a(nowa+1), A[2]=get_a(nowa+2);
	A[3]=get_b(nowb+1), A[4]=get_b(nowb+2);
	A[5]=get_c(nowc+1), A[6]=get_c(nowc+2);
	std::sort(A+1,A+7);
	return A[k];
}
