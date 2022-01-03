/*
15932kb	676ms
直接SAM+map。对于每个节点其产生的不同子串数为len[i]-len[fa[i]]。
*/
#include <map>
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 1500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=2e5+5;

char IN[MAXIN],*SS=IN,*TT=IN;
struct Suffix_Automaton
{
	int tot,las,fa[N],len[N];
	long long ans;
	std::map<int,int> son[N];
	void Insert(int c)
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
				len[nq]=len[p]+1, son[nq]=son[q];
				fa[nq]=fa[q], fa[q]=fa[np]=nq;
				for(; son[p][c]==q; p=fa[p]) son[p][c]=nq;
			}
		}
		printf("%lld\n",ans+=(long long)(len[np]-len[fa[np]]));
	}
}sam;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int n=read(); sam.las=sam.tot=1;
	for(int i=1; i<=n; ++i) sam.Insert(read());
	return 0;
}
