/*
32176kb	928ms
SAM：能成为识别子串的只有那些|right|=1的节点代表的串。
设这个节点对应原串的右端点为r[i]，则如果|right[i]|=1，即s[ [r[i]-len[i]+1,r[i]-len[fa[i]]] ~ r[i] ]这些子串都出现一次。
那么对于[r[i]-len[i]+1, r[i]-len[fa[i]]]都可以用此时对应的长度(r-i+1)更新其最小值（这个维护每个位置最小的r就可以）。
对于位置[r[i]-len[fa[i]]+1, r[i]可以用len[fa[i]]+1更新（这个直接维护最小值）。
所以建两棵线段树就可以了。
SA：在整个串中不重复出现，我们能想到height。对于一个位置i，以它为左端点能形成的最短的不重复出现串长度l=max(ht[i],ht[i+1])+1.
那么i能对区间i~i+l-2贡献l；包含i的子串长度>l时一定也只出现了一次，即可以对i+l-1~n贡献对应长度(p-i+1)的值。还是用线段树维护。
l==r的时候不能PushDown啊mdzz。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
const int N=1e5+5,INF=1061109554;

struct Segment_Tree
{
	#define lson rt<<1
	#define rson rt<<1|1
	#define ToL l,m,rt<<1
	#define ToR m+1,r,rt<<1|1
	int mn[N<<2],tag[N<<2];
	Segment_Tree(){
		memset(mn,0x3f,sizeof mn), memset(tag,0x3f,sizeof tag);
	}
	inline void PushUp(int rt){
		mn[rt]=std::min(mn[lson],mn[rson]);
	}
	inline void Update(int x,int v){
		tag[x]=std::min(tag[x],v), mn[x]=std::min(mn[x],v);
	}
	inline void PushDown(int rt){
		Update(lson,tag[rt]), Update(rson,tag[rt]), tag[rt]=INF;
	}
	void Modify(int l,int r,int rt,int L,int R,int v)
	{//线段树都没一次写对→_→ 
		if(L>R) return;
		if(L<=l && r<=R){
			tag[rt]=std::min(tag[rt],v), mn[rt]=std::min(mn[rt],v); return;
		}
		if(tag[rt]<INF) PushDown(rt);
		int m=l+r>>1;
		if(L<=m) Modify(ToL,L,R,v);
		if(m<R) Modify(ToR,L,R,v);
//		PushUp(rt);
	}
}t1,t2;
struct Suffix_Automaton
{
	#define S N<<1
	int tot,las,fa[S],son[S][26],len[S],R[S],right[S],A[S],tm[S];
	char s[N];
	void Insert(int pos,int c)
	{
		int p=las,np=++tot;
		len[las=np]=len[p]+1, R[np]=pos, right[np]=1;
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
	int Build()
	{
		las=tot=1, scanf("%s",s+1);
		int l=strlen(s+1);
		for(int i=1; i<=l; ++i) Insert(i,s[i]-'a');
		for(int i=1; i<=tot; ++i) ++tm[len[i]];
		for(int i=1; i<=l; ++i) tm[i]+=tm[i-1];
		for(int i=1; i<=tot; ++i) A[tm[len[i]]--]=i;
		for(int i=tot,x=A[tot],f,p; i; x=A[--i])
		{
			right[fa[x]]+=right[x];// R[fa[x]]=R[x];
			if(right[x]==1)
				f=fa[x], p=R[x], t1.Modify(1,l,1,p-len[f]+1,p,len[f]+1), t2.Modify(1,l,1,p-len[x]+1,p-len[f],p);
		}
		return l;
	}
}sam;

void Query(int l,int r,int rt)
{
	if(l==r) printf("%d\n",std::min(t1.mn[rt],t2.mn[rt]-l+1));
	else
	{
		if(t1.tag[rt]<INF) t1.PushDown(rt);
		if(t2.tag[rt]<INF) t2.PushDown(rt);
		Query(l,l+r>>1,rt<<1), Query((l+r>>1)+1,r,rt<<1|1);
	}
}

int main()
{
	int n=sam.Build(); Query(1,n,1);
	return 0;
}
