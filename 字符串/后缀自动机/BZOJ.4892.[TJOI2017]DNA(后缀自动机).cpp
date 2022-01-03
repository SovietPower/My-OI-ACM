/*
9224kb	1624ms
$Description$
����������$S,T$����$T$��$S$�г����˶��ٴΡ�������ָ��������$3$�Σ�$3$���ַ�����ƥ�䣨�޸�ʹ��ƥ�䣩��
$Solution$
һ����·�������ǹ������ʽ����ÿ���ַ�c�������ǣ�$f[i]=[S[i]��ƥ��c],g[i]=[T[i]==c]$��
Ȼ��$F=f*g$�����Եõ�ÿ��λ������m�Ĵ����ж��ٸ�λ��S,T��ƥ����c�����ĳ��λ��ƥ���ַ���>=m-3��������Ϊ��˵�Ĵ����С�
FFT/NTTʵ�֣�������Ҳ���ܹ���
SA������ö��S��ÿ��λ��i���赱ǰƥ��Tƥ�䵽j���õ���������ht��������ǿ���$O(1)$���LCP(suf[i],suf[j])��ֱ��j+=LCP�����ˡ�
���ĳ��λ�ò�ƥ�䣬����������3�λ���ֱ������ȥ������ʵ��ö��j�Ĵ���ֻ��5��
���Ӷ�$O(Tn\log n)$��
SAM�������õ�parent����ֱ��������DFS�������ƥ�����ߣ�����ƥ������һ�δ���������m������ϸõ�Ĺ���(���ֹ����ٴ�)��
���Ӷ�$O(Tn)$��
����ĳ�������Hash�������������ӶȱȽ��š�
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
const int N=2e5+5;

struct Suffix_Automaton
{
	int n,Ans,tot,las,son[N][4],fa[N],len[N],cnt[N],tm[N],A[N],ref[233];
	char s[N];

	Suffix_Automaton() {tot=las=1;}
	void Insert(int c)
	{
		int np=++tot,p=las;
		len[las=np]=len[p]+1, cnt[np]=1;
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
		tot=las=1;
		ref['A']=0, ref['T']=1, ref['G']=2, ref['C']=3;
		memset(tm,0,sizeof tm);//! ��ǰ׺���ˡ�_��
		memset(cnt,0,sizeof cnt), memset(son,0,sizeof son);

		scanf("%s",s+1); int l=strlen(s+1);
		for(int i=1; i<=l; ++i) Insert(ref[s[i]]);
		for(int i=1; i<=tot; ++i) ++tm[len[i]];
		for(int i=1; i<=l; ++i) tm[i]+=tm[i-1];
		for(int i=1; i<=tot; ++i) A[tm[len[i]]--]=i;
		for(int i=tot,x=A[i]; i; x=A[--i]) cnt[fa[x]]+=cnt[x];
	}
	void DFS(int x,int use,int l)
	{
		if(l==n) return (void)(Ans+=cnt[x]);
		for(int i=0; i<4; ++i)
			if(son[x][i])
				if(ref[s[l]]==i) DFS(son[x][i],use,l+1);
				else if(use<3) DFS(son[x][i],use+1,l+1);
	}
	void Query()
	{
		scanf("%s",s), n=strlen(s);
		Ans=0, DFS(1,0,0), printf("%d\n",Ans);
	}
}sam;

int main()
{
	int T; scanf("%d",&T);
	while(T--) sam.Build(), sam.Query();
	return 0;
}
