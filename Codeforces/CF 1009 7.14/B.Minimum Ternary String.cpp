#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=1e5+7;

int n;
char s[N],ans[N];

int main()
{
	scanf("%s",s+1), n=strlen(s+1);
	int cnt[5],now;
	cnt[0]=cnt[1]=cnt[2]=0;
	for(now=1; now<=n; ++now)
		if(s[now]!='2') ++cnt[s[now]-'0'];
		else break;
	for(int i=1; i<=cnt[0]; ++i) ans[i]='0';
	for(int i=cnt[0]+1; i<=cnt[0]+cnt[1]; ++i) ans[i]='1';
	cnt[0]=cnt[1]=cnt[2]=0;
	for(int i=now; i<=n; ++i) ++cnt[s[i]-'0'];
	for(int i=now; i<now+cnt[1]; ++i) ans[i]='1';
	s[n+1]='3';
	for(int i=now+cnt[1]; i<=n; ++i)
	{
		while(s[now]=='1') ++now;
		ans[i]=s[now++];
	}
	puts(ans+1);

	return 0;
}/*
102012012
*/
