/*
122404kb	1924ms
len(Ti)+len(Tj)����ֱ���������ÿ��С��n�ĳ��Ȼᱻ����n-1�Ρ�
$$\sum_{i=1}^n\sum_{j=i+1}^n i+j = (n-1)*\sum_{i=1}^n = (n-1)*\frac{n*(n+1)}{2}$$
**SAM��**���׺��LCP�����ǿ����뵽���ַ�����ת����ǰ׺���������׺��
parent����ÿ��Ҷ�ӽڵ㶼��Ӧһ��ǰ׺�������ڵ����������׺�����ǵ�LCA��������Ϊlen[LCA]��
���Ƕ���ÿ���ڵ�����ͳ���ж��ٶ�Ҷ�ӽڵ��LCAΪ��������DP�Ϳ����ˡ�
**SA��**LCP��Ȼ�ǿ�height�ˡ�ö�ٺ�׺����������֮ǰ�������ɵ�LCP��
���ht[i]>=ht[i-1]����ô����֮ǰ����LCP��i-1һ��������ht[i]�����ⲿ�ֵ�LCP���ȡ�
�õ���ջά����i�����ht[p]<=i��λ��p����f[i]=f[p]+(i-p)*ht[i]��
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
const int N=1e6+5;

struct Suffix_Automaton
{
	int n,las,tot,fa[N],son[N][26],len[N],sz[N],A[N],tm[N];
	char s[N>>1];
	void Insert(int c)
	{
		int p=las,np=++tot;
		len[las=np]=len[p]+1, sz[np]=1;
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
		scanf("%s",s+1), n=strlen(s+1);
		std::reverse(s+1,s+1+n);
		for(int i=1; i<=n; ++i) Insert(s[i]-'a');
		for(int i=1; i<=tot; ++i) ++tm[len[i]];
		for(int i=1; i<=n; ++i) tm[i]+=tm[i-1];
		for(int i=1; i<=tot; ++i) A[tm[len[i]]--]=i;

		long long res=0;
		for(int i=tot,x=A[i],f; i; x=A[--i])
			f=fa[x], res+=1ll*sz[f]*sz[x]*len[f], sz[f]+=sz[x];
		printf("%lld\n",1ll*n*(n+1)/2*(n-1)-(res<<1));
	}
}sam;

int main()
{
	sam.Build();
	return 0;
}
