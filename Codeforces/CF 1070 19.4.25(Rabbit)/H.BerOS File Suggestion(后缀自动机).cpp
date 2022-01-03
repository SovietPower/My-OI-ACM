/*
77ms	17500KB
怎么写AC自动机、写Hash的都有... 这不是[BZOJ2780]吗？粘过代码来就完了。
*/
#include <cstdio>
#include <cctype>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#define pc putchar
#define gc() getchar()
typedef long long LL;
const int N=10005*10;
using namespace std;

int mp[233];
string str[10005];
struct Suffix_Automaton
{
	int tot,las,fa[N],len[N],son[N][40],cnt[N],bef[N];

	void Insert(int c,int now)
	{
		int np=++tot,p=las; len[las=np]=len[p]+1;
		for(; p&&!son[p][c]; p=fa[p]) son[p][c]=np;
		if(!p) fa[np]=1;
		else
		{
			int q=son[p][c];
			if(len[q]==len[p]+1) fa[np]=q;
			else
			{
				int nq=++tot;
				len[nq]=len[p]+1, bef[nq]=bef[q], cnt[nq]=cnt[q];
				memcpy(son[nq],son[q],sizeof son[q]);
				fa[nq]=fa[q], fa[q]=fa[np]=nq;
				for(; son[p][c]==q; p=fa[p]) son[p][c]=nq;
			}
		}
		for(; bef[np]!=now&&np; np=fa[np])
			++cnt[np], bef[np]=now;
	}
	void Query(char *s,int l)
	{
		int x=1;
		for(int i=0; i<l; ++i) x=son[x][mp[s[i]]];
		cout << cnt[x] << ' ' << str[bef[x]] << '\n';
	}
}sam;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	static char s[233];
	int cnt=0; mp['.']=cnt++;
	for(int i='0'; i<='9'; ++i) mp[i]=cnt++;
	for(int i='a'; i<='z'; ++i) mp[i]=cnt++;
	int n=read(); sam.tot=1;
	for(int i=1; i<=n; ++i)
	{
		scanf("%s",s), str[i]=s;
		sam.las=1;
		for(int j=0,l=strlen(s); j<l; ++j) sam.Insert(mp[s[j]],i);
	}
	str[0]="-";
	for(int Q=read(); Q--; scanf("%s",s), sam.Query(s,strlen(s)));

	return 0;
}
