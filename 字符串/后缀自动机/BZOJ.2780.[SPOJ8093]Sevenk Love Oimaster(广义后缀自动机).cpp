/*
24612kb	76ms
$Description$
给定n个模式串，m次询问一个串在多少个模式串中出现过。(字符集为26个小写字母)
$Solution$ 
对每个询问串进行匹配最终会达到一个节点，我们需要得到这个节点所代表的子串出现在多少个模式串中。
建立广义后缀自动机。每次插入一个串，从root开始，对于SAM上每个节点维护cnt和bef，分别表示该节点代表的串出现在几个模式串中 和 该节点最近被哪个模式串更新过cnt。
对于bef[i]!=now的节点，++cnt[i],bef[i]=now；当模式串now下次匹配到当前节点时则不再更新。
另外，如果匹配了当前节点i那么一定会匹配上fa[i],fa[fa[i]]...如果它们的bef[]!=now，则都更新一遍。直到有个节点p满足bef[p]==now，那么就不需要再向上更新了（再往上已经更新过了）。(这个在insert后用np更新就可以啊)
注意新建nq时 bef[nq],cnt[nq]也要复制(=..[q])。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=2e5+5;

struct Suffix_Automaton
{
	int las,tot,fa[N],son[N][26],len[N],cnt[N],bef[N];
	char s[360005];

	void Init(){
		las=tot=1;
	}
	void Insert(int now,int c)
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
				int nq=++tot;
				len[nq]=len[p]+1, bef[nq]=bef[q], cnt[nq]=cnt[q];//!
				memcpy(son[nq],son[q],sizeof son[q]);
				fa[nq]=fa[q], fa[q]=fa[np]=nq;
				for(; son[p][c]==q; p=fa[p]) son[p][c]=nq;
			}
		}
		for(; bef[np]!=now&&np; np=fa[np])
			++cnt[np], bef[np]=now;
	}
	void Build(int now)
	{
		las=1, scanf("%s",s);
		for(int i=0,l=strlen(s); i<l; ++i)
			Insert(now,s[i]-'a');
	}
	void Query()
	{
		int p=1; scanf("%s",s);
		for(int i=0,l=strlen(s); i<l&&p; ++i)
			p=son[p][s[i]-'a'];
		printf("%d\n",cnt[p]);
	}
}sam;

int main()
{
	int n,Q; scanf("%d%d",&n,&Q); sam.Init();
	for(int i=1; i<=n; ++i) sam.Build(i);
	while(Q--) sam.Query();

	return 0;
}
