/*
后手必胜(先手必败,P-position)当且仅当n堆石子数异或和为0。
首先0一定是P-position， 
假设a1^a2^a3^...^an=K 
若K!=0，则一定可以找到一个ai，ai在K的最高位的1上为1，显然ai > ai^K，那么可以把ai变成ai^K，局面就成了a1^a2^...^an^ai^K = K^K = 0 (后手就处于P-position) 
若K==0，至少取一个显然不能使K仍为0 
*/
#include <cstdio>
#include <cctype>
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int MAXIN=1e6;

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
	int t=read(),n,res;
	while(t--)
	{
		n=read(), res=0;
		while(n--) res^=read();
		puts(res?"Yes":"No");
	}
	return 0;
}
