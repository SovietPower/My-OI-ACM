#include <cstdio>
#include <cstring>
#include <algorithm>
const int N=10505,S=26;//不需要很大！(只是模式串)

int n;
char s[155][75],p[1000005];
struct AC_Automaton
{
	int cnt,q[N],val[N],fail[N],las[N],son[N][S],tm[155];
	void Init()
	{
		cnt=0, memset(son,0,sizeof son), memset(val,0,sizeof val);
	}
	void Insert(char *s,int id)
	{
		int l=strlen(s),u=0;
		for(int v,i=0; i<l; ++i)
		{
			v=s[i]-'a';
			if(!son[u][v]) son[u][v]=++cnt;
			u=son[u][v];
		}
		val[u]=id;
	}
	void Build()
	{
		int h=0,t=0;
		for(int i=0; i<S; ++i)
			if(son[0][i]) fail[son[0][i]]=0,q[t++]=son[0][i];
		while(h<t)
		{
			int x=q[h++];
			for(int v,i=0; i<S; ++i)
				if(son[x][i])
					fail[v=son[x][i]]=son[fail[x]][i], q[t++]=v, las[v]=val[fail[v]]?fail[v]:las[fail[v]];
				else son[x][i]=son[fail[x]][i];
		}
	}
	void Query(char *p)
	{
		memset(tm,0,sizeof tm);
		int l=strlen(p),u=0,res=0;
		for(int i=0; i<l; ++i)
		{
			u=son[u][p[i]-'a'];
			for(int p=u; p; p=las[p])
				++tm[val[p]];
		}
		for(int i=1; i<=n; ++i) res=std::max(res,tm[i]);
		printf("%d\n",res);
		for(int i=1; i<=n; ++i)
			if(tm[i]==res) printf("%s\n",s[i]);
	}
}ac;

int main()
{
	while(scanf("%d",&n),n)
	{
		ac.Init();
		for(int i=1; i<=n; ++i) scanf("%s",s[i]), ac.Insert(s[i],i);
		ac.Build();
		scanf("%s",p), ac.Query(p);
	}
	return 0;
}
