#include <set>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=4e5+5;

int A[N],Ans[N];
std::multiset<pr> st;
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main() {

	int n=read(),m=read(),D=read();
	for(int i=1; i<=n; ++i) st.insert(mp(read(),i));
	int tot=0,now=1e9+5;
	std::multiset<pr>::iterator it;
	while(!st.empty())
	{
		it=st.lower_bound(mp(now+D+1,0));
		if(it==st.end()) ++tot, it=st.begin();
		now=it->first, Ans[it->second]=tot;
		st.erase(it);
	}
	printf("%d\n",tot);
	for(int i=1; i<=n; ++i) printf("%d ",Ans[i]);

	return 0;
}
