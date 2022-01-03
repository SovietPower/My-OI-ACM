/*
52776kb	1500ms
$Description$
���������ַ������������ж��ٸ���ͬ�Ӵ�����ͬ����λ�ò�ͬ������
$Solution$
��һ������SAM����ΪҪͳ�Ʋ�ͬλ�ø���������ƥ��һ����Ĺ���Ϊ(val[i]=(len[i]-len[fa[i]])*|right[i]|)+val[fa[i]]+val[fa[fa[i]]]...
Ȼ����һ������SAM���ߡ�ά����ǰ��ƥ��ĳ���l����ǰ����Ϊval[fa[i]]+(l-len[fa[i]])*|right[i]|��
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=4e5+5;

struct Suffix_Automaton
{
	int las,tot,fa[N],son[N][26],len[N],A[N],tm[N],right[N];
	LL val[N];
	char s[N];

	void Insert(int c)
	{
		int np=++tot,p=las;
		len[las=np]=len[p]+1, right[np]=1;
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
	void Build()
	{
		las=tot=1;
		scanf("%s",s); int l=strlen(s);
		for(int i=0; i<l; ++i) Insert(s[i]-'a');
		for(int i=1; i<=tot; ++i) ++tm[len[i]];
		for(int i=1; i<=l; ++i) tm[i]+=tm[i-1];
		for(int i=1; i<=tot; ++i) A[tm[len[i]]--]=i;

		for(int i=tot,x=A[i]; i; x=A[--i]) right[fa[x]]+=right[x];
		for(int i=1; i<=tot; ++i) val[i]=1ll*(len[i]-len[fa[i]])*right[i];
		for(int i=2,x=A[2]; i<=tot; x=A[++i]) val[x]+=val[fa[x]];
	}
	void Query()
	{
		scanf("%s",s);
		LL ans=0;
		for(int p=1,now=0,c,i=0,l=strlen(s); i<l; ++i)
		{
			if(son[p][c=s[i]-'a']) ++now, p=son[p][c];
			else
			{
				for(; p&&!son[p][c]; p=fa[p]);
				if(!p) p=1, now=0;
				else now=len[p]+1, p=son[p][c];
			}
			ans+=val[fa[p]]+1ll*(now-len[fa[p]])*right[p];
		}
		printf("%lld",ans);
	}
}sam;

int main()
{
	sam.Build(), sam.Query();
	return 0;
}
