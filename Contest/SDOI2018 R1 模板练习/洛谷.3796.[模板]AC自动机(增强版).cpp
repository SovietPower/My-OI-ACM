#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=152*72,S=26;

int n;
char s[152][72],p[1000005];

struct AC_Automaton
{
	int tot,son[N][27],fail[N],val[N],las[N],q[N],tm[152];
	void Init(){
		tot=0, memset(son,0,sizeof son), memset(val,0,sizeof val);
	}
	void Insert(char *s,int pos)
	{
		int l=strlen(s),x=0;
		for(int id,i=0; i<l; ++i)
		{
			id=s[i]-'a';
			if(!son[x][id]) son[x][id]=++tot;
			x=son[x][id];
		}
		val[x]=pos;
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
					fail[v=son[x][i]]=son[fail[x]][i],q[t++]=v,las[v]=val[fail[v]]?fail[v]:las[fail[v]];
				else son[x][i]=son[fail[x]][i];
		}
	}
	void Query(char *p)
	{
		int l=strlen(p),res=0,x=0;
		memset(tm,0,sizeof tm);
		for(int i=0; i<l; ++i)
		{
			x=son[x][p[i]-'a'];
			for(int j=x; j; j=las[j]) ++tm[val[j]];
		}
		for(int i=1; i<=n; ++i) if(res<tm[i]) res=tm[i];
		printf("%d\n",res);
		for(int i=1; i<=n; ++i) if(tm[i]==res) printf("%s\n",s[i]);
	}
}ac;

int main()
{
	while(scanf("%d",&n),n){
		ac.Init();
		for(int i=1; i<=n; ++i) scanf("%s",s[i]),ac.Insert(s[i],i);
		ac.Build(), scanf("%s",p), ac.Query(p);
	}
	return 0;
}
