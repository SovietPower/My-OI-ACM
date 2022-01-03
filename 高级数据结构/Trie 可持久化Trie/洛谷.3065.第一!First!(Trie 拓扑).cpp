/*
����n���ַ��������ض���Ӣ���ַ���˳��(���ֵ���)������Щ���ʿ������ڵ�һ 

һ��������Ҫ���ڵ�һ��������û�������ַ���������ǰ׺����ô��һ��Trie�� 
��Σ����ַ������ȼ�Ҫ�Ⱥ���������ͬǰ׺��Ҫ�ߡ�
Ҳ����˵������ͬһ�����ڵ��£�������ӵ����ȼ�Ҫ�������ֵ�Ҫ�� 
��ô���Ǿ���һ���ߣ���ʾ���ȼ��ߵ͡�������ˣ�����л������� 
�ж�һ���ַ���ֻ����Trie���ϱ��߱߼ӱ߼��ɡ���������Ӵ�����Ȼ���С� 

���ֶ����������������...
���ڱ���һ��(u,v)ֻ�ܽ�һ���ߣ���Ϊ�Ǵ�С��ϵ 
�����ӹ���ĳ��Ԫ��һ����������� 

С����������Ҫ����memset��һ����Ҫ����

c_str()��Borland��װ��String���е�һ�������������ص�ǰ�ַ��������ַ���ַ������Ϊconstchar* 
*/
#include<cstdio>
#include<cstring>
#include<iostream>
const int N=3e5+5,M=3e4+5,S=27;

int n,tot,dgr[S],son[N][S],q[S],Enum,H[S],to[S*S],nxt[S*S];
bool vis[N],mrk[M],lnk[S][S];
std::string str[M];
char tmp[10005];

inline void AddEdge(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
}
//void Insert(char *s)
void Insert(std::string s)//faster
//ֱ����ȫ�ֵ�tmp�Կ�һ�� 
{
//	int l=strlen(s),id,u=0;
	int l=s.size(),id,u=0;
	for(int i=0;i<l;++i)
	{
		id=s[i]-'a';
		if(!son[u][id]) son[u][id]=++tot;
		u=son[u][id];
	}
	vis[u]=1;
}
//bool Solve(std::string s)
bool Solve(int p)//faster
{
	int l=str[p].size(),id,u=0;
	for(int i=0;i<l;++i)
	{
		if(vis[u]) return 0;
		id=str[p][i]-'a';
		for(int j=0;j<26;++j)
			if(son[u][j] && id!=j && !lnk[id][j])
				++dgr[j], lnk[id][j]=1, AddEdge(id,j);
		u=son[u][id];
	}
	return 1;
}
bool TopoSort()
{
	int h=0,t=0,x;
	for(int i=0;i<26;++i)
		if(!dgr[i]) q[t++]=i;
	while(h<t)
	{
		x=q[h++];
		for(int i=H[x];i;i=nxt[i])
			if(!--dgr[to[i]]) q[t++]=to[i];
	}
	for(int i=0;i<26;++i)
		if(dgr[i]) return 0;
	return 1;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("3065.in","r",stdin);
//	freopen("3065.out","w",stdout);
#endif

	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%s",tmp), str[i]=tmp, Insert(str[i]);
	int res=0;
	for(int i=1;i<=n;++i)
	{
		Enum=0;
		memset(H,0,sizeof H);
		memset(lnk,0,sizeof lnk);
		memset(dgr,0,sizeof dgr);
		if(!Solve(i)) continue;
		if(TopoSort()) mrk[i]=1,++res;
	}
	printf("%d\n",res);
	for(int i=1;i<=n;++i)
		if(mrk[i]) printf("%s\n",str[i].c_str());

	return 0;
}
