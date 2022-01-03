/*
简单的DP，查找是否有字典中的单词时在Trie树上做 
要注意在最初Match(0)一遍后，i还是要从0开始匹配，因为如果有长度为1的单词，Match(i+1)不会从1更新 

1M=1024K=1024*1024B
*/
#include<cstdio>
#include<cstring>
const int N=1025*1025,M=220,S=28;

int n,m,tot,son[M][S],qu[M],qid[M];
bool dp[N],vis[M];
char s[N];

void Insert()
{
	int l=strlen(s),u=0,id;
	for(int i=0;i<l;++i)
	{
		id=s[i]-'a';
		if(!son[u][id]) son[u][id]=++tot;
		u=son[u][id];
	}
	vis[u]=1;
}
bool Match(int p)
{
	int id,id2,u,h=0,t=1;
	qu[0]=0,qid[0]=p;
	while(h<t)
	{
		u=qu[h], id=s[qid[h]]-'a', id2=qid[h++];
//		printf(" %d:\t  u:%d id:%c i:%d\n",p,u,id+'a',id2);
//		if(dp[id2]) continue;//不要有这个！dp与当前的u和id都有关 
		if(!son[u][id]) continue;
		u=son[u][id];
		if(vis[u]) dp[id2]=1;
//		printf("dp:%d\n",dp[id2]);
		qu[t]=u, qid[t++]=id2+1;
	}
}

int main()
{
//	freopen("language.in","r",stdin);
//	freopen("language.out","w",stdout);

	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%s",s),Insert();
	for(int i=1;i<=m;++i)
	{
		scanf("%s",s);
		int l=strlen(s);
		memset(dp,0,sizeof dp);
//		dp[0]=1;
		int ans=0;
		Match(0);
		for(int j=0;j<l;++j)
			if(dp[j]) ans=j+1, Match(j+1);//这是j+1...注意条件也不要设成j<l-1 
		printf("%d\n",ans);
	}

	return 0;
}
