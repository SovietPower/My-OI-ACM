//删掉一个单词需要前移一段位置，用链表维护就好了 复杂度O(sum(len)) 
#include <cstdio>
#include <cstring>
#define S 26
const int N=1e5+7;

int n;
char s[N],p[N];
struct AC_Automaton
{
	int cnt,son[N][S],fail[N],pos[N],q[N],dep[N];
	bool val[N];
	struct List
	{
		int l,r;
	}lst[N];
	void Insert(char *s)
	{
		int x=0;
		for(int i=0,l=strlen(s),id; i<l; ++i)
		{
			id=s[i]-'a';
			if(!son[x][id]) son[x][id]=++cnt,dep[cnt]=dep[x]+1;//这里改用一个局部int ++dep还要更慢。。大概是重复节点很多的原因 
			x=son[x][id];
		}
		val[x]=1;
	}
	void Build()
	{
		int h=0,t=0;
		for(int i=0; i<S; ++i)
			if(son[0][i]) fail[son[0][i]]=0, q[t++]=son[0][i];
		while(h<t)
		{
			int x=q[h++];
			for(int i=0; i<S; ++i)
				if(son[x][i]) fail[son[x][i]]=son[fail[x]][i],q[t++]=son[x][i];
				else son[x][i]=son[fail[x]][i];
		}
	}
	void Query(char *s)
	{
		int l=strlen(s+1);
		for(int i=1; i<l; ++i) lst[i].l=i-1,lst[i].r=i+1;
		lst[0].r=1, lst[l].l=l-1;
		for(int x=0,t,i=1; i; i=lst[i].r)
		{
			if(son[x][t=s[i]-'a']) 
			{
				x=son[x][t];
				if(val[x])
				{
					t=i;
					for(int j=dep[x]; j; --j) t=lst[t].l;
					lst[t].r=lst[i].r, lst[lst[i].r].l=t;
					x=pos[t];
				}
			}
			else x=0;//not x=fail[x]!
			pos[i]=x;
		}
		for(int i=lst[0].r; i; i=lst[i].r) printf("%c",s[i]);
	}
}ac;

int main()
{
	scanf("%s%d",p+1,&n);
	for(int i=1; i<=n; ++i) scanf("%s",s),ac.Insert(s);
	ac.Build(), ac.Query(p);
	return 0;
}
