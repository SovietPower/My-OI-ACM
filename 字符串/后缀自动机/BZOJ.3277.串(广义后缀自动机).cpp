/*
30740kb	612ms
$Description$
����n������K����ÿ�������ж��ٸ��Ӵ�����n����������K�������Ӵ���
$Solution$
ͬ���⣬���ǿ������ÿ���ڵ�������Ĵ��������˼������У���������֪��������ÿ���ڵ�i��������Ĵ�������Ϊlen[i]-len[fa[i]]��
���������׺�Զ�����Ԥ����ÿ���ڵ��cnt��ÿ���ڵ��val���Ը���cnt�Ƿ�>=K��Ϊlen[i]-len[fa[i]]��0��
����Ҫ����������Ӵ����������ͳ��val[i]��ҲҪ����val[fa[i]],val[fa[fa[i]]]...ֱ�ӽ���parent�����ϵ���DFS����ÿ���㡣
����ÿ��Ҫ��𰸵Ĵ�����SAM����һ�鲢�ۼ����о����ڵ�ĸ��º��val���ɡ�
��𰸵�ʱ����Ϊ���ܴ洮��so�ø�����/vector�������о���������
�Ҳ����뿴100+�е�SA����
*/
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=2e5+5;//��len <= 1e5 ?

struct Suffix_Automaton
{
	int n,K,las,tot,fa[N],son[N][26],len[N],cnt[N],bef[N],Enum,H[N],nxt[N],to[N];//parent���ռ���2n�� 
	LL val[N];
	char s[N>>1];
	std::vector<int> v[N>>1];

	void Init(int nn){
		n=nn, scanf("%d",&K), las=tot=1;
	}
	inline void AddEdge(int u,int v){
		to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
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
				len[nq]=len[p]+1, bef[nq]=bef[q], cnt[nq]=cnt[q];
				memcpy(son[nq],son[q],sizeof son[q]);
				fa[nq]=fa[q], fa[q]=fa[np]=nq;
				for(; son[p][c]==q; p=fa[p]) son[p][c]=nq;
			}
		}
		v[now].push_back(np);
		for(; bef[np]!=now&&np; np=fa[np])
			++cnt[np], bef[np]=now;
	}
	void Build(int now)
	{
		scanf("%s",s), las=1;//las=1���� 
		for(int i=0,l=strlen(s); i<l; ++i)
			Insert(now,s[i]-'a');
	}
	void DFS(int x)
	{
		val[x]+=val[fa[x]];
		for(int i=H[x]; i; i=nxt[i]) DFS(to[i]);
	}
	void Solve()
	{
		for(int i=2; i<=tot; ++i)
		{
			AddEdge(fa[i],i);
			if(cnt[i]<K) val[i]=0;
			else val[i]=len[i]-len[fa[i]];
		}
		DFS(1);
		for(int i=1; i<=n; ++i)
		{
			LL res=0;
			for(int j=0,l=v[i].size(); j<l; ++j)
				res+=val[v[i][j]];
			printf("%lld ",res);
		}
	}
}sam;

int main()
{
	int n; scanf("%d",&n), sam.Init(n);
	for(int i=1; i<=n; ++i) sam.Build(i);
	sam.Solve();
	return 0;
}
