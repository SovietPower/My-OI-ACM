/*
249ms	131600KB
$Description$
����һ���ַ���s[1]��һ���ַ�������s[]����s[i]������s[i-1]�г��ֹ�����(i>=2)��������k���������s[1]~s[k]��
$Solution$
һ��ʼ��Ϊֱ���Ե����Ϻϲ�right�����|right|>1�ͼ������ϡ�����Ȼ���԰����������ִ���>1��һ������֮ǰ���ӽڵ��г��ִ���>1��
�����A�����ڴ�B�����Σ���ô˵��ʲô����right(endpos)��ʾһ��������λ�õ����Ҷ˵㼯�ϣ���right(A)��s[right(B)-len(A),right(B)]�����ٳ��ֹ����Ρ�
���Ҷ�����ԭ����������λ�ó��ֵ�B��A�����������������
�������������һ��pos[B]=ĳһ��right(B)��A����B�г�����������������right(A)��s[pos[B]-len(B)+len(A),pos[B]]�����ٳ��������Σ�sΪԭ������
���нڵ��right���ǿ���ͨ���߶����ϲ�ȫ���õ���
parent���ϵĸ��ڵ���ת�Ƶ��ӽڵ㡣���Կ������ϵ��µ�DP�����������������£���B(�ӽڵ�)��Ϊ�µ�A(�´�ƥ����Ϊ���ڵ�)����������������֮ǰ��A��֮ǰ�ĸ��ڵ� ���ţ���
��Ϊ���ڵ�$A$�Ѿ��������ӽڵ�$B$�г��ֹ�һ���ˣ�����ֻ��Ҫ��$s[pos[B]-len(B)+len(A),pos[B]-1]$���Ƿ����$right(A)$��$A$���߶������ڸ������Ƿ���ֵ����
��ע����Ȼ$A$�����ʾһ���ڵ㣬�ƺ���Ȼ����$mnlen(A)$����ȷ����������$A$�ڵ���Ĵ��ĳ���$len(A)$������...ʵ������û����ģ���Ϊ��Ȼͬ��$A$�ڵ�...����Щ��������ʡ������ľ�д$mnlen$�ɣ�
������һ������hash��������
*/
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e5+5;

char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

struct Segment_Tree
{
	#define ls son[x][0]
	#define rs son[x][1]
	static const int S=N*2*25;//�����4nlogn...
	int tot,son[S][2];

	void Insert(int &x,int l,int r,int p)
	{
		/*if(!x)*/ x=++tot;
		if(l==r) return;
		int m=l+r>>1;
		if(p<=m) Insert(ls,l,m,p);
		else Insert(rs,m+1,r,p);
	}
	bool Query(int x,int l,int r,int L,int R)
	{
		if(!x) return 0;
		if(L<=l && r<=R) return 1;//������ڵ㼴�� 
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return Query(ls,l,m,L,R)||Query(rs,m+1,r,L,R);
			else return Query(ls,l,m,L,R);
		else return Query(rs,m+1,r,L,R);
	}
	int Merge(int x,int y)
	{
		if(!x||!y) return x|y;
		int now=++tot;//!
		son[now][0]=Merge(ls,son[y][0]), son[now][1]=Merge(rs,son[y][1]);
		return now;
	}
};
struct Suffix_Automaton
{
	static const int S=N<<1;
	int n,tot,las,len[S],pos[S],son[S][26],fa[S],tm[S],A[S],root[S],f[S],top[S];
	Segment_Tree T;

	Suffix_Automaton() {tot=las=1;}
	void Insert(int c,int id)
	{
		int np=++tot,p=las;
		len[las=np]=len[p]+1, pos[np]=id;
		for(; p&&!son[p][c]; p=fa[p]) son[p][c]=np;
		if(!p) fa[np]=1;
		else
		{
			int q=son[p][c];
			if(len[q]==len[p]+1) fa[np]=q;
			else
			{
				int nq=++tot;
				len[nq]=len[p]+1, pos[nq]=pos[q]/*!*/;
				memcpy(son[nq],son[q],sizeof son[q]);
				fa[nq]=fa[q], fa[q]=fa[np]=nq;
				for(; son[p][c]==q; p=fa[p]) son[p][c]=nq;
			}
		}
	}
	void Solve()
	{
		n=read(); register char c=gc(); for(;!isalpha(c);c=gc());
		Insert(c-'a',1),T.Insert(root[las],1,n,1);
		for(int i=2; i<=n; ++i) Insert(gc()-'a',i),T.Insert(root[las],1,n,i);

		for(int i=1; i<=tot; ++i) ++tm[len[i]];
		for(int i=1; i<=n; ++i) tm[i]+=tm[i-1];
		for(int i=1; i<=tot; ++i) A[tm[len[i]]--]=i;

		for(int i=tot,x=A[i]; i>1; x=A[--i]) root[fa[x]]=T.Merge(root[fa[x]],root[x]);
		int ans=1;
		for(int i=2,x=A[i],tp; i<=tot; x=A[++i])
		{
			if(fa[x]==1) {f[x]=1, top[x]=x; continue;}
			tp=top[fa[x]];
			if(T.Query(root[tp],1,n,pos[x]-len[x]+len[tp],pos[x]-1))//or pos[x]-len[x]+len[fa[tp]]+1
				f[x]=f[tp]+1, top[x]=x, ans=std::max(ans,f[x]);
			else f[x]=f[tp], top[x]=tp;
		}
		printf("%d\n",ans);
	}
}sam;

int main()
{
	sam.Solve();
	return 0;
}
