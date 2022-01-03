/*
529ms	56700KB
$Description$
������S��m����Ti��Q��ѯ�ʣ�ÿ��ѯ��l,r,pl,pr����S[pl~pr]��Tl~Tr�е��ĸ������ִ�����࣬�������������T���±ꡣ���ж��������±���С�ġ�
$Solution$
��T������SAM��Ȼ��Ҫ���SAMÿ���ڵ���|right|�������ĸ�����
ÿ���ڵ��|right|������DFS parent��ʱ�ϲ��ӽڵ�õ���������߶���ά����|right|����λ��Ҳ���Ժϲ��õ���
�����������ߴ���ѯ�ʣ����DFSһ��õ��𰸡�
��ô�õ�S[pl~pr]��SAM�ϵ�ƥ��ڵ��ء�
��S[1]��S[i]������ƥ�䣬ƥ�䲻�˾���fa�������ܱ�֤��׺(S[i])�����ˡ�
������i�⴦��pr==i��ѯ�ʡ�ֻҪ���Ǵӵ�ǰ�ڵ�һֱ��fa�������ҵ�ƥ��S[pl,pr]�Ľڵ㣬��𰸾��Ǹýڵ��|right|״̬�������ñ�����
�������Ϊ0�Ļ�ҲҪ����ǰ��(l)�����ԡ�
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define Bit 16
const int N=5e5+5,M=5e4+5,S=M<<1;

int m,root[S],fa[S][18];
char s[N],tmp[M];
struct Edge
{
	int Enum,H[N],nxt[N],to[N];
	inline void AddEdge(int u,int v){
		to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	}
}Pos,Qy;
struct Edge2
{
	int Enum,H[S],nxt[S],to[S];
	inline void AddEdge(int u,int v){
		to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	}
}Par;
struct Queries{
	int l,r,pl,pr;
}q[N];
struct Suffix_Automaton
{
	int tot,las,fa[S],son[S][26],len[S];

	Suffix_Automaton() {tot=las=1;}
	void Insert(int c)
	{
		int np=++tot,p=las; len[las=np]=len[p]+1;
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
}sam;
struct Node
{
	int val,id;
	bool operator <(const Node &x)const{
		return val<x.val||(val==x.val&&id>x.id);
	}
}Ans[N];
struct Segment_Tree
{
	#define S M*17
	#define lson son[x][0]
	#define rson son[x][1]
	int tot,son[S][2];
	Node node[S];
	#undef S
	#define Update(x) node[x]=std::max(node[lson],node[rson]);
	void Insert(int &x,int l,int r,int pos)
	{
		x=++tot;
		if(l==r) return (void)(node[x]=(Node){1,pos});
		int m=l+r>>1;
		pos<=m ? Insert(lson,l,m,pos) : Insert(rson,m+1,r,pos);
		Update(x);//Update 
	}
	int Merge(int x,int y)
	{
		if(!x||!y) return x^y;
		if(!lson&&!rson) return node[x].val+=node[y].val, x;//Ҷ�ڵ㣬�ϲ�right 
		lson=Merge(lson,son[y][0]), rson=Merge(rson,son[y][1]);
		Update(x); return x;
	}
	Node Query(int x,int l,int r,int L,int R)
	{
		if(!x) return (Node){0,L};
		if(L<=l && r<=R) return node[x];
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return std::max(Query(lson,l,m,L,R),Query(rson,m+1,r,L,R));
			else return Query(lson,l,m,L,R);
		return Query(rson,m+1,r,L,R);
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void DFS(int x)
{
	for(int i=Par.H[x]; i; i=Par.nxt[i])
		DFS(Par.to[i]), root[x]=T.Merge(root[x],root[Par.to[i]]);
	for(int i=Pos.H[x],id; i; i=Pos.nxt[i])
		id=Pos.to[i], Ans[id]=T.Query(root[x],1,m,q[id].l,q[id].r);
}

int main()
{
	scanf("%s",s+1); int n=strlen(s+1);
	m=read();
	for(int i=1; i<=m; ++i)
	{
		scanf("%s",tmp), sam.las=1;
		for(int j=0,l=strlen(tmp); j<l; ++j)
			sam.Insert(tmp[j]-'a'), T.Insert(root[sam.las],1,m,i);//������ÿλ��|right[las]|=1���_�����ھ���ʲô 
	}
	int Q=read();
	for(int i=1; i<=Q; ++i)
		q[i]=(Queries){read(),read(),read(),read()}, Qy.AddEdge(q[i].pr,i);
	int lim=sam.tot;
	for(int x=2; x<=lim; ++x) Par.AddEdge(fa[x][0]=sam.fa[x],x);
	for(int i=1; i<=Bit; ++i)
		for(int x=2; x<=lim; ++x)
			fa[x][i]=fa[fa[x][i-1]][i-1];
	for(int c,now=0,p=1,i=1; i<=n; ++i)
	{
		if(sam.son[p][c=s[i]-'a']) p=sam.son[p][c], ++now;//!!!�� ��д���������Сʱ �� ���� 
		else
		{
			for(c=s[i]-'a'; p&&!sam.son[p][c]; p=sam.fa[p]);
			if(!p) {p=1, now=0; continue;}
			now=sam.len[p]+1, p=sam.son[p][c];
		}
		for(int j=Qy.H[i],len,id; j; j=Qy.nxt[j])
		{
			id=Qy.to[j];
			if(now<(len=q[id].pr-q[id].pl+1)) continue;
			int x=p;
			for(int i=Bit; ~i; --i)
				if(sam.len[fa[x][i]]>=len) x=fa[x][i];
			Pos.AddEdge(x,id);
		}
	}
	DFS(1);
	for(int i=1; i<=Q; ++i)
		if(!Ans[i].val) printf("%d 0\n",q[i].l);
		else printf("%d %d\n",Ans[i].id,Ans[i].val);

	return 0;
}
