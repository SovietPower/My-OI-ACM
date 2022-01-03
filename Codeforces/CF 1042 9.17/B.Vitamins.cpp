//其实直接map<string,int>就可以了，mp["A"]+mp["BC"]...好写清楚。
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
using std::min;
const int N=1005;

int n,mn[10];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int n=read();
	char s[10]; bool vis[10];
	for(int i=0; i<9; ++i) mn[i]=2e8;
	for(int i=1; i<=n; ++i)
	{
		int c=read(); scanf("%s",s+1);
		int l=strlen(s+1),ss=0;
		vis[0]=vis[1]=vis[2]=0;
		for(int j=1; j<=l; ++j)
		{
			vis[s[j]-'A']=1,ss+=1<<(s[j]-'A');
			mn[1<<(s[j]-'A')]=min(mn[1<<(s[j]-'A')],c);
		}
		mn[ss]=min(mn[ss],c);
	}
	int ans=2e8;
	ans=min(mn[1]+mn[2]+mn[4],min(mn[1]+mn[6],min(mn[2]+mn[5],min(mn[4]+mn[3],mn[7]))));
	printf("%d\n",ans>1e7?-1:ans);

	return 0;
}
