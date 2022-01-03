/*
396K	47MS
$Description$
����Ϊ$3n$�����л��ֳ�$3$�������У�Ҫ�����������������еĺͶ�$\geq 500*n$�������һ��������֤�н⡣
$Solution$
�϶���Ҫ������$2n$�����ֳ��������������������С�
ֱ��̰�Ĳ�û��ʲô���е���������(�������벻����)
���ǿ����������������������У�Ȼ����������������е���������ֱ�������������Ϊֹ��
�������������е�ĳ�����ڶ������������Ч�ġ�
������֤or���˵���ˣ�������Ҳû�и��õ�������������ɡ�
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
