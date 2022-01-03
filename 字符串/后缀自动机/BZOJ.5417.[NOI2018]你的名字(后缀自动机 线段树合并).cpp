/*
LOJ:10770ms	337788K
���:16362ms	348.41MB 
BZOJ:408052kb	28352ms
����l=1,r=|S|�������
��S����SAM��T������ƥ�䣬���Եõ�ÿ��λ��i�ĺ�׺���ƥ�䳤��mx[i]��
��ΪҪȥ�أ���TҲ��SAM�������������нڵ�Ĵ𰸡���pos[i]��ʾi�ڵ��һ�γ��ֵ��±꣨ͬһ�ڵ����Ĵ����ֵ�λ�ü�����ͬ����������һ�����ɣ���
��ڵ�i�Ĵ�Ϊ��max(0, len[i]-max(len[fa[i]], mx[pos[i]]))��
����l,r����������
Ҫ�ж�T�ܷ���S[l,r]��ƥ�䣬Ҳ����ƥ���ʱ��ֻ������S[l,r]���ֹ��Ľڵ㡣
�߶����ϲ����Ե����Ϻϲ�right���ϣ��Ϳ��Եõ�SAM��ÿ���ڵ���ֹ���λ�ã�right����
�����ƥ�䳤��Ϊnow����ô������ʱ��Ҫ��[l+now,r]������faʱҪͬʱ��now����Ҫ������68�֣���
��nowӦ����ÿ�μ�һ����������pֱ����fa����������96�֣���
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e6+5;

int mx[N],root[N];
char s[N];
struct Segment_Tree
{
	#define ls son[x][0]
	#define rs son[x][1]
	#define lson ls,l,m
	#define rson rs,m+1,r
	#define S N*20
	int tot,son[S][2];
	#undef S
	void Insert(int &x,int l,int r,int p)
	{
		/*if(!x)*/ x=++tot;//
		if(l==r) return;
		int m=l+r>>1;
		p<=m ? Insert(lson,p) : Insert(rson,p);
	}
	int Merge(int x,int y)
	{
		if(!x||!y) return x|y;
		int now=++tot;
		son[now][0]=Merge(ls,son[y][0]), son[now][1]=Merge(rs,son[y][1]);
		return now;
	}
	bool Query(int x,int l,int r,int L,int R)
	{
		if(!x) return 0;
		if(L<=l && r<=R) return 1;
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return Query(lson,L,R)||Query(rson,L,R);
			else return Query(lson,L,R);
		return Query(rson,L,R);
	}
	#undef ls
	#undef rs
}Tr;
struct Suffix_Automaton
{
	int n,tot,las,fa[N],son[N][26],len[N],tm[N],A[N],pos[N];

	void Insert(int c,int id)
	{
		int np=++tot,p=las;
		len[las=np]=len[p]+1, pos[np]=id;
		for(;p&&!son[p][c]; p=fa[p]) son[p][c]=np;
		if(!p) fa[np]=1;
		else
		{
			int q=son[p][c];
			if(len[q]==len[p]+1) fa[np]=q;
			else
			{
				int nq=++tot;
				len[nq]=len[p]+1, pos[nq]=pos[q];
				memcpy(son[nq],son[q],sizeof son[q]);
				fa[nq]=fa[q], fa[q]=fa[np]=nq;
				for(; son[p][c]==q; p=fa[p]) son[p][c]=nq;
			}
		}
	}
	void Build_S(char *s,int l)
	{
		memset(son,0,(tot+2)*sizeof son[0]);
		tot=las=1, n=l;
		for(int i=1; i<=n; ++i) Insert(s[i]-'a',i),Tr.Insert(root[las],1,n,i);
		for(int i=1; i<=tot; ++i) ++tm[len[i]];
		for(int i=1; i<=n; ++i) tm[i]+=tm[i-1];
		for(int i=1; i<=tot; ++i) A[tm[len[i]]--]=i;
		for(int i=tot,x=A[i]; i>1; x=A[--i]) root[fa[x]]=Tr.Merge(root[x],root[fa[x]]);
	}
	void Build_T(char *s,int l)
	{
		memset(son,0,(tot+2)*sizeof son[0]);
		tot=las=1, n=l;
		for(int i=1; i<=l; ++i) Insert(s[i]-'a',i);
	}
}S,T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void Solve(int ls)
{
	scanf("%s",s+1);
	int l=read(),r=read(),n=strlen(s+1);
	T.Build_T(s,n);
	for(int i=1,now=0,p=1,c; i<=n; mx[i++]=now)
	{
		c=s[i]-'a';
		while(1)
		{
			if(!Tr.Query(root[S.son[p][c]],1,ls,l+now,r))
			{
				if(!now) break;//ƥ�䳤��Ϊ0��Ҫ��ƥ��һ�� 
				--now;
				if(now==S.len[S.fa[p]]) p=S.fa[p];
			}
			else {++now, p=S.son[p][c]; break;}
		}
//		if(Tr.Query(root[S.son[p][c]],1,ls,l+now,r)) p=S.son[p][c], ++now;
//		else
//		{
//			for(; p&&!Tr.Query(root[S.son[p][c]],1,ls,l+now,r); p=S.fa[p],now=S.len[p]);
//			if(!p) p=1, now=0;
//			else now=S.len[p]+1, p=S.son[p][c];//����д96�� ��ֻ����һ��ѯ�� 
//		}
	}
	LL ans=0;
	for(int i=2; i<=T.tot; ++i)
		ans+=std::max(0,T.len[i]-std::max(T.len[T.fa[i]],mx[T.pos[i]]));
	printf("%lld\n",ans);
}

int main()
{
//	freopen("name.in","r",stdin);
//	freopen("name.out","w",stdout);

	scanf("%s",s+1); int ls=strlen(s+1);
	S.Build_S(s,ls);
	for(int Q=read(); Q--; Solve(ls));

	return 0;
}
