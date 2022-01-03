/*
221660kb	2580ms
Ҫ�Զ����ͬʱ����SAM�������ַ�����
1.�����д�ƴ�������м��÷ָ��������������ַ��������뼴�ɡ�
2.����Щ����Trie�Ͻ�SAM��ʵ���ϲ�����Ҫ��Trie������ֻ��Ҫ�������루��Ϊ�����Ͳ�ࣿ������Ҫ������һ����ʱ���las������Ϊroot������ǹ����׺�Զ�����
���ڱ��⣬��ΪҶ�ڵ����ֻ��20�����������˰�ι��������ЩҶ�ڵ�ֱ�Ϊ����DFS��������Tire����Ȼԭͼ���ǣ������������Ӵ�����Trie��ĳ��·���С������ͳ�����ͬ�Ӵ��ĸ�����
��Ȼ���ǲ���Ҫ��Trie�����β���SAM���ɡ������ǰ��Ҫ������ת�ƣ������½�np������ֱ����son[p][c]��np��������кܶ��ظ��ڵ㣨��Ȼ��Ӱ����ȷ�԰ɣ���
ÿ�β���һ���ַ�����������Ӵ�һ����len[i]������������Ϊ�Ҷ˵�ĺ�׺������ͬ���Ӵ�����len[i]-len[fa[i]]�������нڵ�Ĺ�����ͼ�Ϊ�𰸡�
ע�����20�ν�SAM���ռ�Ҫ��������longlong����
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 1000000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1e5+7,S=N*20*2;

int n,C,A[N],dgr[N],Enum,H[N],nxt[N<<1],to[N<<1];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Suffix_Automaton
{
	int tot,las,fa[S],son[S][11],len[S];
	void Init(){
		tot=las=1;
	}
	int Insert(int p,int c)
	{
		int las;
		if(son[p][c])
		{
			int q=son[p][c];
			if(len[q]==len[p]+1) las=q;
			else
			{
				int nq=++tot; len[las=nq]=len[p]+1;
				memcpy(son[nq],son[q],sizeof son[q]);
				fa[nq]=fa[q], fa[q]=nq;//��Ҫ�뵱Ȼдfa[p]=nq q�ʹ���np�� 
				for(; son[p][c]==q; p=fa[p]) son[p][c]=nq;
			}
		}
		else
		{
			int np=++tot; len[las=np]=len[p]+1;
			for(; p&&!son[p][c]; p=fa[p]) son[p][c]=np;
			if(!p) fa[np]=1;
			else
			{
				int q=son[p][c];
				if(len[q]==len[p]+1) fa[np]=q;
				else
				{
					int nq=++tot; len[nq]=len[p]+1;
					memcpy(son[nq],son[q],sizeof son[q]);
					fa[nq]=fa[q], fa[np]=fa[q]=nq;
					for(; son[p][c]==q; p=fa[p]) son[p][c]=nq;
				}
			}
		}
		return las;
	}
	void Calc()
	{
		long long ans=0;
		for(int i=2; i<=tot; ++i) ans+=(long long)(len[i]-len[fa[i]]);
		printf("%lld\n",ans);
	}
}sam;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v)
{
	++dgr[v], to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	++dgr[u], to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void DFS(int x,int f,int rt)
{
	int t=sam.Insert(rt,A[x]);
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=f) DFS(to[i],x,t);
}

int main()
{
	n=read(), C=read(), sam.Init();
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int i=1; i<n; ++i) AddEdge(read(),read());
	for(int i=1; i<=n; ++i) if(dgr[i]==1) DFS(i,i,1);
	sam.Calc();

	return 0;
}
