/*
31000kb	484ms
���Ȳ���Ҫ�洢ÿ���ַ��������Խ�����������ַ����δ��Trie��������ÿ��'P',��¼�ô�������λ�����ģ��Լ���ǰ�ڵ��Ӧ���ǵڼ�����(��ǰ�������ڵ㵱��ǰ�ڵ�)������'B',ֻ��������һ���ڵ㡣
Ȼ�󹹽�Trieͼ��fail[]��һ����Ҫ������: ��fail[y]=x����ôy�ڵ��ʾ�Ĵ�һ������x�ڵ��ʾ�Ĵ���
���Ǳ����Ϳ����Ե����ϲ�ѯy����ÿ���ڵ��fail[]�Ƿ�ֱ�ӻ���ָ��x 
ע�⵽ÿ���ڵ��fail[]�ǽ�ָ��һ���ڵ�ģ����ǿ��Է���ͼfail[x]->x���������γ���һ����������fail�� 
���Ƕ���ÿ����ѯ����ȥ����x�ڵ���������ж��ٸ�y���еĽڵ� 
һ���ڵ��������DFS����һ����������һ�Σ����Կ���ֱ����fail������DFS��Ȼ������״����ά�� 
����ֱ����Trie����DFS���շ��ʵ�һ��������·��+1�����ʽ���ʱ-1����������һ�����Ĵ�ʱ��ǰ��״�����ֵһ���Ǹô��ϵĵ������׵� 
(ע��ԭӦ�ǲ�x��fail���е�������������fail���õ���DFS��)
ÿ�η��ʵ�һ���ڵ� �Ϳ��Եõ�����Ϊy��ѯ�ʵĴ� 
��ѯ�ʰ�y����(������Trie���ϵ����λ��)����ÿ���ڵ���Դ�һ��ѯ�ʱ�ŵ����䣬Ȼ����Trie����һ��DFS 
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define lb(x) (x)&-(x)
const int N=1e5+5,S=26;

int n,m,cnt,Enum,H[N],nxt[N],to[N],ql[N],qr[N]/*һ����������һ��ѯ��*/,Time,in[N],out[N],t[N<<1];
int que[N],fail[N],son[N][S],Son[N][S]/*copyһ�����׺����֮ǰ��son*/,ed[N]/*���Ľ���λ��*/,fa[N],lab[N]/*ĳλ�ý����Ĵ��ı��*/,Ans[N];
char s[N];
struct Ques
{
	int x,y,id;
	bool operator <(const Ques &a)const{
		return y<a.y;
	}
}q[N];

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
void DFS(int x)
{
	Add(in[x],1);
	if(lab[x])//��ǰ�ڵ���ĳ���Ľ�β�ڵ� 
		for(int i=ql[lab[x]]; i<=qr[lab[x]]; ++i)
			Ans[q[i].id]=Query(out[ed[q[i].x]])-Query(in[ed[q[i].x]]-1);//��ȥx���ϵ�ֵ 
	for(int i=0; i<S; ++i)
		if(Son[x][i]) DFS(Son[x][i]);
	Add(in[x],-1);
}

int main()
{
	scanf("%s",s);
	for(int now=0,i=0,l=strlen(s),t; i<l; ++i)
	{
		if(s[i]>='a'&&s[i]<='z')
		{
			if(!son[now][t=s[i]-'a']) Son[now][t]=son[now][t]=++cnt, fa[cnt]=now;
			now=son[now][t];
		}
		else if(s[i]=='P') ed[++n]=now, lab[now]=n;
		else now=fa[now];
	}
	Get_Fail();
	for(int i=1; i<=cnt; ++i) AddEdge(fail[i],i);
	pre_DFS(0);

	m=read();
	for(int i=1; i<=m; ++i) q[i].x=read(),q[i].y=read(),q[i].id=i;
	std::sort(q+1,q+1+m);
	for(int i=1; i<=m; ++i)//�õ�����ÿ������Ϊyʱ��ѯ�� 
	{
		ql[q[i].y]=i;
		while(i<m && q[i+1].y==q[i].y) ++i;
		qr[q[i].y]=i;
	}
	DFS(0);
	for(int i=1; i<=m; ++i) printf("%d\n",Ans[i]);

	return 0;
}
