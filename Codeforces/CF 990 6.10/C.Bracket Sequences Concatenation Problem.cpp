//46ms	2472KB
//注意一下非法情况。
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=3e5+5;

int n,val[N],rval[N];
char s[N];

bool Check1(int l)
{
	int n=0;
	for(int i=1; i<=l&&n>=0; ++i)
		if(s[i]=='(') ++n;
		else --n;
	return n>=0;
}
bool Check2(int l)
{
	int n=0;
	for(int i=l; ~i&&n>=0; --i)
		if(s[i]==')') ++n;
		else --n;
	return n>=0;
}

int main()
{
	scanf("%d",&n);
	long long res=0;
	for(int i=1; i<=n; ++i)
	{
		scanf("%s",s+1);
		int l=strlen(s+1), cnt=0;
		for(int j=1; j<=l; ++j)
			if(s[j]=='(') ++cnt;
			else --cnt;
		if(cnt==0)
			if(Check1(l)) res+=val[0]*2+1, ++val[0];
			else ;
		else if(cnt>0)
			if(Check1(l)) res+=rval[cnt], ++val[cnt];
			else ;
		else if(Check2(l)) res+=val[-cnt], ++rval[-cnt];
	}
	printf("%I64d",res);

	return 0;
}
