/*
93ms	8600KB
$Description$
给定$n$个数，每次可以将任意一个数乘上任意一个正整数。求$k$次操作后，数列中数的种类最少可以是多少。对每个$0\leq k\leq n$输出答案。
$Solution$
有两种贪心策略，一是每次找一个出现次数最少的数，把它变成所有数的LCM；二是找一个出现次数最少，且它的某个倍数存在于原数列里的数，将它变成它的这个倍数。
对两种情况取$\min$即可。
*/
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e6+3;

int tm[N];
std::vector<int> va,vb;
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
	freopen("equal.in","r",stdin);
	freopen("equal.out","w",stdout);

	int n=read();
	for(int i=1; i<=n; ++i) ++tm[read()];
	for(int i=1; i<N; ++i)
		if(tm[i])
		{
			va.push_back(tm[i]);//只关心次数 
			for(int j=i+i; j<N; j+=i)
				if(tm[j]) {vb.push_back(tm[i]); break;}
		}
	std::sort(va.begin(),va.end());
	std::sort(vb.begin(),vb.end());

	int tmp=va.size();
	va.push_back(1e8), vb.push_back(1e8);
	std::vector<int>::iterator pa=va.begin(),pb=vb.begin();
	for(int i=0,sa=0,sb=0,a=0,b=0; i<=n; ++i)
	{
		while(sa+*pa<=i) sa+=*pa++, ++a;
		while(sb+*pb<=i) sb+=*pb++, ++b;
		printf("%d ",tmp-std::max(a-1,b));
	}
	return 0;
}
