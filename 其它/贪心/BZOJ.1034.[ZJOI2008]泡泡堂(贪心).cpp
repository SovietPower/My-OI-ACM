/*
2188kb	108ms
容易想到田忌赛马。但是是不对的，比如2 3对1 3，按田忌赛马策略会3->1 2->3，但是3->3 2->1显然更优。
而如果按己方最强>=对方最强则开打，也是不对的，比如1 3对2 3，按该策略会3->3 1->2。
问题在于，在第一种情况下，对面最弱的2分是一定可以得到的。
于是得到贪心策略：1.若己方最弱强于对方最弱，则比，不能就继续2；
2.若己方最强强于对方最强，则比，不能就继续3；
3.己方最弱和对方最强比。（还是有可能赢的）
注意到两支队伍的总得分是2n，最低得分可以用2n减去对面的最高得分。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 600000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1e5+5;

int n,A[N],B[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int Solve(int *a,int *b)
{
	int ans=0;
	for(int h1=1,h2=1,t1=n,t2=n; h1<=t1 && h2<=t2; )
	{
		if(a[h1]>b[h2]) ans+=2,++h1,++h2;
		else if(a[t1]>b[t2]) ans+=2,--t1,--t2;
		else ans+=(a[h1++]==b[t2--]);//不会大于了...
	}
	return ans;
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int i=1; i<=n; ++i) B[i]=read();
	std::sort(A+1,A+1+n), std::sort(B+1,B+1+n);
	printf("%d %d\n",Solve(A,B),2*n-Solve(B,A));

	return 0;
}
