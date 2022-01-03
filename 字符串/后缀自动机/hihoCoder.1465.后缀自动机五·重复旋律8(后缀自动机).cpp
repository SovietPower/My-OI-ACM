/*
80ms	25MB
��ģʽ��s����һ�飬��ĸ����SAM��ƥ�䣬��¼��ÿ��λ����Ϊ��׺����ƥ�����󳤶�mx[i]��
���mx[i]>=l��ģʽ����������ô����ĸ������Ϊһ��"ѭ����������"���ֹ���
�Ӹô�ƥ������������ҵ���parent�����ڵ����������len[p]>=l��λ��p�����ִ�������|right[p]|��
ģʽ�����ƺ���ܵõ�������ͬ��ѭ�����������ظ�ͳ�ƣ�����Ҫ���ǡ�
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
const int N=2e5+5;

struct Suffix_Automaton
{
	int las,tot,fa[N],son[N][26],len[N],A[N],tm[N],right[N],vis[N];
	char s[N];

	Suffix_Automaton() {tot=las=1;}
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
		scanf("%s",s+1); int l=strlen(s+1);
		for(int i=1; i<=l; ++i) Insert(s[i]-'a');
		for(int i=1; i<=tot; ++i) ++tm[len[i]];
		for(int i=1; i<=l; ++i) tm[i]+=tm[i-1];
		for(int i=1; i<=tot; ++i) A[tm[len[i]]--]=i;
		for(int i=tot,x=A[i]; i; x=A[--i]) right[fa[x]]+=right[x];
	}
	int Calc(int p,int l,int id)
	{
		for(; len[fa[p]]>=l; p=fa[p]);
		return vis[p]==id?0:(vis[p]=id,right[p]);
	}
	void Query()
	{
		static int Index=0;
		++Index;
		scanf("%s",s+1); int l=strlen(s+1);
		for(int i=1; i<=l; ++i) s[i+l]=s[i];
		int ans=0;
		for(int c,now=0,p=1,i=1; i<=l<<1; ++i)
		{
			if(son[p][c=s[i]-'a']) p=son[p][c], ++now;
			else
			{
				for(; p&&!son[p][c]; p=fa[p]);
				if(!p) p=1, now=0;
				else now=len[p]+1, p=son[p][c];
			}
			if(now>=l) ans+=Calc(p,l,Index);
		}
		printf("%d\n",ans);
	}
}sam;


int main()
{
	sam.Build();
	int n; scanf("%d",&n);
	while(n--) sam.Query();
	return 0;
}
