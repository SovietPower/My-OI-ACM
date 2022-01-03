#include <cstdio>
#include <cstring>
#include <algorithm>
const int N=1e6+5;

char s[N];
struct AC_Automaton
{
	int tot,fail[N],son[N][26],las[N],val[N],q[N];
	void Insert(char *s)
	{
		int l=strlen(s),x=0;
		for(int id,i=0; i<l; ++i)
		{
			id=s[i]-'a';
			if(!son[x][id]) son[x][id]=++tot;
			x=son[x][id];
		}
		++val[x];
	}
	void Build()
	{
		int h=0,t=0;
		for(int i=0; i<26; ++i)
			if(son[0][i]) fail[son[0][i]]=0,q[t++]=son[0][i];
		while(h<t)
		{
			int x=q[h++];
			for(int v,i=0; i<26; ++i)
				if(son[x][i])
					fail[v=son[x][i]]=son[fail[x]][i],q[t++]=v,las[v]=val[fail[v]]?fail[v]:las[fail[v]];
				else son[x][i]=son[fail[x]][i];//ֱ����son[]��
		}
	}
	void Query(char *s)
	{
		int l=strlen(s),res=0,x=0;
		for(int i=0; i<l; ++i)
		{
			x=son[x][s[i]-'a'];//����һ�� 
			for(int j=x; j&&~val[j]; j=las[j])
				res+=val[j], val[j]=-1;//�����ظ��ߡ�
		}
		printf("%d",res);
	}
}ac;

int main()
{
	int n; scanf("%d",&n);
	while(n--) scanf("%s",s),ac.Insert(s);
	ac.Build(), scanf("%s",s), ac.Query(s);

	return 0;
}
