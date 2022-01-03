/*
26700kb	244ms
$Description$
����ÿ����������n������ֻ�ڸô��г��ֹ����Ӵ���������
$Solution$
������SAM����ÿ��������ʱ�½���np����������ĸ�����
Ȼ����parent����DFS���ϲ��ӽڵ�״̬�����ˡ�
ÿ����Ĺ��׾���len[i]-len[fa[i]]��
��Ϊ�����Ĺ���SAM���Ǻ�����ɣ�ֱ�Ӱ�������������Ǵ�ġ�
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
const int N=2e5+5;

struct Suffix_Automaton
{
	int tot,las,son[N][26],len[N],fa[N],bel[N],Enum,H[N],nxt[N],to[N];
	char s[N>>1];
	long long ans[N>>1];

	#define AE(u,v) to[++Enum]=v,nxt[Enum]=H[u],H[u]=Enum
	Suffix_Automaton() {tot=las=1;}
	void Insert(int c,int id)
	{
		int np=++tot,p=las;
		len[las=np]=len[p]+1, bel[np]=id;
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
				fa[nq]=fa[q], fa[q]=fa[np]=nq;
				for(; son[p][c]==q; p=fa[p]) son[p][c]=nq;
			}
		}
	}
	void Build(int id)
	{
		las=1;  scanf("%s",s);
		for(int i=0,l=strlen(s); i<l; ++i) Insert(s[i]-'a',id);
	}
	void DFS(int x)
	{
		for(int i=H[x]; i; i=nxt[i]) DFS(to[i]);
		for(int i=H[x],v; i; i=nxt[i])
		{
			if(!bel[v=to[i]]) {bel[x]=0; break;}
			if(!bel[x]) bel[x]=bel[v];
			else if(bel[x]!=bel[v]) {bel[x]=0; break;}
		}
	}
	void Solve(int n)
	{
		for(int i=2; i<=tot; ++i) AE(fa[i],i);
		DFS(1);
		for(int i=2; i<=tot; ++i) if(bel[i]) ans[bel[i]]+=len[i]-len[fa[i]];
		for(int i=1; i<=n; ++i) printf("%lld\n",ans[i]);
	}
}sam;

int main()
{
	int n; scanf("%d",&n);
	for(int i=1; i<=n; ++i) sam.Build(i);
	sam.Solve(n);
	return 0;
}
