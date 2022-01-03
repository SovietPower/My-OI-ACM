#include <cstdio>
#include <cstring>
const int N=1e6+5;

int len,fail[N];
char p[N],s[N];

void Get_fail()
{
	fail[0]=fail[1]=0;
	for(int i=1,j; i<len; ++i)
	{
		j=fail[i];
		while(s[i]!=s[j]&&j) j=fail[j];
		fail[i+1]=s[i]==s[j]?j+1:0;
	}
}
void KMP()
{
	for(int i=0,j=0,l=strlen(p); i<l; ++i)
	{
		while(p[i]!=s[j]&&j) j=fail[j];
		if(p[i]==s[j]) ++j;
		if(j==len) printf("%d\n",i-j+2);
	}
	for(int i=1; i<=len; ++i) printf("%d ",fail[i]);
}

int main()
{
	scanf("%s%s",p,s), len=strlen(s), Get_fail(), KMP();
	return 0;
}
