#include <set>
#include <map>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define pc putchar
#define gc() getchar()
#define int long long
#define LL long long
using namespace std;
const int MAXN = 1e6 + 10, INF = 1e9 + 10, mod = 1e9 + 7;
const double eps = 1e-9;

inline int read()
{
	int now=0,f=1;
	register char c=gc();
	for(; !isdigit(c); c=='-'&&(f=-1),c=gc());
	for(; isdigit(c); now=now*10+c-'0',c=gc());
	return now*f;
}
int N, top;
char s[MAXN], st[MAXN];

main()
{
	scanf("%s", s + 1);
	N = strlen(s + 1);
	bool flag = 0;
	for(int i = 1; i <= N; i++)
	{
		if(top && s[i] == st[top])
		{
			top--, flag ^= 1;
		}
		else st[++top] = s[i];
	}
	if(flag) puts("Yes");
	else puts("No");
	return 0;
}
