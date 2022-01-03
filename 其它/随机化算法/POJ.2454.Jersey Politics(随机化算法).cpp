/*
396K	47MS
$Description$
将长为$3n$的序列划分成$3$个子序列，要求至少有两个子序列的和都$\geq 500*n$，输出任一方案。保证有解。
$Solution$
肯定是要将最大的$2n$个数分成两个满足条件的子序列。
直接贪心并没有什么可行的做法。。(反正我想不出来)
我们考虑先随便地填满这两个序列，然后再随机交换序列中的两个数，直到最后满足条件为止。
交换两个序列中的某个数在多数情况下是有效的。
并不会证or别的说明了，反正我也没有更好的做法，就随机吧。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define pr std::pair<int,int>
#define mp std::make_pair
const int N=190;

int n;
pr A[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
bool cmp(const pr &a,const pr &b){
	return a.first>b.first;
}

int main()
{
//	srand(20180412);
	n=read();
	for(int i=0; i<3*n; ++i) A[i]=mp(read(),i+1);
	std::sort(A,A+1+3*n,cmp);
	int sum1=0,sum2=0,lim=500*n,p1,p2;
	for(int i=0; i<n; ++i) sum1+=A[i].first,sum2+=A[i+n].first;
	while(sum1<=lim||sum2<=lim)
	{
		p1=rand()%n,p2=rand()%n+n;
		(sum1-=A[p1].first)+=A[p2].first;
		(sum2-=A[p2].first)+=A[p1].first;
		std::swap(A[p1],A[p2]);
	}
	for(int i=0; i<3*n; ++i) printf("%d\n",A[i].second);

	return 0;
}
