/*
17720kb	428ms
���Ȳ���Ҫ�洢ÿ���ַ��������Խ�����������ַ����δ��Trie��������ÿ��'P',��¼�ô�������λ�����ģ��Լ���ǰ�ڵ��Ӧ���ǵڼ�����(��ǰ�������ڵ㵱��ǰ�ڵ�)������'B',ֻ��������һ���ڵ㡣
Ȼ�󹹽�Trieͼ��fail[]��һ����Ҫ������: ��fail[y]=x����ôy�ڵ��ʾ�Ĵ�һ������x�ڵ��ʾ�Ĵ���
���Ǳ����Ϳ����Ե����ϲ�ѯy����ÿ���ڵ��fail[]�Ƿ�ֱ�ӻ���ָ��x 
ע�⵽ÿ���ڵ��fail[]�ǽ�ָ��һ���ڵ�ģ����ǿ��Է���ͼfail[x]->x���������γ���һ����������fail�� 
���Ƕ���ÿ����ѯ����ȥ����x�ڵ���������ж��ٸ�y���еĽڵ� 
һ���ڵ��������DFS����һ����������һ�Σ����Կ���ֱ����fail������DFS��Ȼ������״����ά�� 
����ֱ����Trie����DFS���շ��ʵ�һ��������·��+1�����ʽ���ʱ-1����������һ�����Ĵ�ʱ��ǰ��״�����ֵһ���Ǹô��ϵĵ������׵� 
(ע��ԭӦ�ǲ�x��fail���е�������������fail���õ���DFS��)
ÿ�η��ʵ�һ���ڵ� �Ϳ��Եõ�����Ϊy��ѯ�ʵĴ� 
����ͬһ����(��Ϊy)��ѯ�ʿ������ڽӱ�洢��Ȼ����Trie����һ��DFS�����DFSֱ��for(i=1 to cnt)�Ϳ����ˣ�
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define lb(x) (x)&-(x)
const int N=1e5+5,S=26;

int m,cnt,Enum,H[N],nxt[N],to[N],Time,in[N],out[N],t[N<<1],_H[N],_Enum,_to[N],_nxt[N],_id[N];
int que[N],fail[N],son[N][S],ed[N]/*���Ľ���λ��*/,fa[N],Ans[N];
char s[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v){
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
}
inline void _AddEdge(int u,int v,int i){
	_to[++_Enum]=v, _nxt[_Enum]=_H[u], _H[u]=_Enum, _id[_Enum]=i;
}
void Get_Fail()
{
	int h=0,t=0;
	for(int i=0; i<S; ++i)
		if(son[0][i]) fail[son[0][i]]=0,que[t++]=son[0][i];
	while(h<t)
	{
		int x=que[h++];
		for(int i=0; i<S; ++i)
			if(son[x][i]) fail[son[x][i]]=son[fail[x]][i],que[t++]=son[x][i];
			else son[x][i]=son[fail[x]][i];
	}
}
void pre_DFS(int x)
{
	in[x]=++Time;
	for(int i=H[x]; i; i=nxt[i]) pre_DFS(to[i]);
	out[x]=++Time;
}
inline void Add(int p,int v){
	while(p<=Time) t[p]+=v,p+=lb(p);
}
inline int Query(int p){
	int res=0;
	while(p) res+=t[p],p-=lb(p);
	return res;
}

int main()
{
	scanf("%s",s);
	int l=strlen(s);
	for(int now=0,i=0,n=0,t; i<l; ++i)
	{
		if(s[i]>='a'&&s[i]<='z')
		{
			if(!son[now][t=s[i]-'a']) son[now][t]=++cnt, fa[cnt]=now;
			now=son[now][t];
		}
		else if(s[i]=='P') ed[++n]=now;
		else now=fa[now];
	}
	Get_Fail();
	for(int i=1; i<=cnt; ++i) AddEdge(fail[i],i);
	pre_DFS(0);

	m=read();
	for(int x,y,i=1; i<=m; ++i) x=read(),y=read(),_AddEdge(y,x,i);
	for(int now=0,i=0,n=0; i<l; ++i)
	{
		if(s[i]=='P')
		{
			++n;
			for(int i=_H[n]; i; i=_nxt[i])
				Ans[_id[i]]=Query(out[ed[_to[i]]])-Query(in[ed[_to[i]]]-1);
		}
		else if(s[i]=='B') Add(in[now],-1),now=fa[now];//������ 
		else now=son[now][s[i]-'a'],Add(in[now],1);
	}
	for(int i=1; i<=m; ++i) printf("%d\n",Ans[i]);

	return 0;
}
