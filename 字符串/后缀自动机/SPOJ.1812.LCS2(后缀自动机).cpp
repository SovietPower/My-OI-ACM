/*
0.08s	27M
$Description$
�����10������LCS��
$Solution$
������⣬��һ������SAM�����ǿ����𴮵��������ÿ���ڵ�����ƥ�����󳤶�mx[i]��
����ÿ����i�����д���mx[i]����Сֵ��Ϊ�ڵ�i n������LCS���ȡ�ö�����е㼴�ɡ�
����Ҫ��ÿ���㶼ƥ��һ����mx[]����Ϊfa[p]��p����һ����׺������(����)ƥ����pһ��������ȫƥ��fa[p]����ƥ��pʱ������p����ȥ����һ��mx[]��
����ÿƥ��һ������Ҫ��len�Ӵ�С(��Ҷ�����)����һ�飬�����p(�в���)ƥ���ˣ���ômx[fa[p]]�Ϳ��Ը���Ϊlen[fa[p]].
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
const int N=2e5+7;

char s[N>>1];
struct Suffix_Automaton
{
	int las,tot,fa[N],son[N][26],len[N],mx[N],ans[N],tm[N],A[N];
	void Insert(int c)
	{
		int p=las,np=++tot; len[las=np]=ans[np]=len[p]+1;
		for(; p&&!son[p][c]; p=fa[p]) son[p][c]=np;
		if(!p) fa[np]=1;
		else
		{
			int q=son[p][c];
			if(len[q]==len[p]+1) fa[np]=q;
			else
			{
				int nq=++tot; ans[nq]=len[nq]=len[p]+1;
				memcpy(son[nq],son[q],sizeof son[q]);
				fa[nq]=fa[q], fa[q]=fa[np]=nq;
				for(; son[p][c]==q; p=fa[p]) son[p][c]=nq;
			}
		}
	}
	void Build(char *s)
	{
		las=tot=1; int l=strlen(s);
		for(int i=0; i<l; ++i) Insert(s[i]-'a');
		for(int i=1; i<=tot; ++i) ++tm[len[i]];
		for(int i=1; i<=l; ++i) tm[i]+=tm[i-1];
		for(int i=1; i<=tot; ++i) A[tm[len[i]]--]=i;
	}
	void Match(char *s)
	{
		memset(mx,0,sizeof mx);
		for(int now=0,p=1,c,i=0,l=strlen(s); i<l; ++i,mx[p]=std::max(mx[p],now))
			if(son[p][c=s[i]-'a']) p=son[p][c], ++now;
			else
			{
				for(; p&&!son[p][c]; p=fa[p]);
				if(!p) p=1, now=0;
				else now=len[p]+1, p=son[p][c];
			}
		for(int x,i=tot; i; --i)
			if(mx[x=A[i]]&&fa[x]) mx[fa[x]]=len[fa[x]];
		for(int i=1; i<=tot; ++i) ans[i]=std::min(ans[i],mx[i]);
	}
	void Query()
	{
		int res=0;
		for(int i=1; i<=tot; ++i) res=std::max(res,ans[i]);
		printf("%d",res);
	}
}sam;

int main()
{
	scanf("%s",s), sam.Build(s);
	while(~scanf("%s",s)) sam.Match(s);
	sam.Query();
	return 0;
}
