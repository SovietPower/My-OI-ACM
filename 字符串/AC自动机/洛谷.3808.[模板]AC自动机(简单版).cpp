#include <cstdio>
#include <cstring>
const int N=1e6+5,S=26;

char s[N];
struct AC_Automaton
{
	int cnt,q[N],val[N],fail[N],las[N],son[N][S];
//	struct Node
//	{
//		int val,las,fail,son[S];
//		Node *son[S];//Ö¸ÕëÌ«Âé·³ÁË¡£¡£
//		Node() {val=las=0, memset(son,0,sizeof son);}
//	}pool[N];
	void Insert(char *s)
	{
		int l=strlen(s),u=0;
		for(int v,i=0; i<l; ++i)
		{
			v=s[i]-'a';
			if(!son[u][v]) son[u][v]=++cnt;
			u=son[u][v];
		}
		++val[u];
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
	int Query(char *s)
	{
		int l=strlen(s),res=0,u=0;
		for(int i=0; i<l; ++i)
		{
			u=son[u][s[i]-'a'];
			for(int p=u; p&&~val[p]; p=las[p])
				res+=val[p], val[p]=-1;
		}
		return res;
	}
}ac;

int main()
{
	int n; scanf("%d",&n);
	while(n--) scanf("%s",s), ac.Insert(s);
	ac.Build();
	scanf("%s",s), printf("%d",ac.Query(s));
	return 0;
}
