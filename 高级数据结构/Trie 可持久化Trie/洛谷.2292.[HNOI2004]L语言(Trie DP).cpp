/*
�򵥵�DP�������Ƿ����ֵ��еĵ���ʱ��Trie������ 
Ҫע�������Match(0)һ���i����Ҫ��0��ʼƥ�䣬��Ϊ����г���Ϊ1�ĵ��ʣ�Match(i+1)�����1���� 

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
//		if(dp[id2]) continue;//��Ҫ�������dp�뵱ǰ��u��id���й� 
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
			if(dp[j]) ans=j+1, Match(j+1);//����j+1...ע������Ҳ��Ҫ���j<l-1 
		printf("%d\n",ans);
	}

	return 0;
}
