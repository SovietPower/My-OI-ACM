/*
15064K	79MS
SPOJ:69M	0.04s
$Description$
�������ַ���������Ӵ� 
$Solution$
�Դ�A������׺�Զ�����
A��SAM�а���A�������Ӵ����Ҹ���ÿ���ڵ��·������A���Ӵ������B(��һ����?)ƥ�䵽��SAM�ϵ�ĳ���ڵ㣬��ô�����AB�Ĺ����Ӵ��������Щ���max(len)���ɡ�
�ô�B��SAM����λƥ�䣬���ƥ�䣬�ͼ�������ƥ����ߣ�
����Ϊ��ƥ�䵱ǰ��λ������Bǰ��һ���֣���Ϊfa[p]�ڵ����ĺ�׺��p�������׺����һ���ɽ��ܺ�׺��������fa[p]��ֱ����ƥ�䵱ǰλ�򵽸��ڵ㡣
ע��now�ĸ��·�ʽ�����ƥ����+1����������p����p=son[p][c]ǰ��len[p]+1����now����Ϊ��ʱp��ȫƥ���ˣ���len[son[p][c]]��son[p][c]������Ĵ���max(len)��(����������ɡ���)
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
const int N=250005<<1;//2n

char s[N>>1];
struct Suffix_Automaton
{
	int las,tot,son[N][26],fa[N],len[N];
	void Insert(int c)
	{
		int p=las,np=++tot; len[las=np]=len[p]+1;
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
	void Build(char *s)
	{
		las=tot=1;
		for(int i=0,l=strlen(s); i<l; ++i) Insert(s[i]-'a');
	}
	void Query(char *s)
	{
		int ans=0;
		for(int c,now=0,p=1,i=0,l=strlen(s); i<l; ++i,ans=std::max(ans,now))
			if(son[p][c=s[i]-'a']) p=son[p][c], ++now;
			else
			{
				for(; p&&!son[p][c]; p=fa[p]);
				if(!p) p=1, now=0;
				else now=len[p]+1, p=son[p][c];
//			WA:	else p=son[p][c], now=len[p];
			}
		printf("%d",ans);
	}
}sam;

int main()
{
	scanf("%s",s), sam.Build(s);
	scanf("%s",s), sam.Query(s);
	return 0;
}
