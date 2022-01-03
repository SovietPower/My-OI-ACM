/*
32176kb	928ms
SAM���ܳ�Ϊʶ���Ӵ���ֻ����Щ|right|=1�Ľڵ����Ĵ���
������ڵ��Ӧԭ�����Ҷ˵�Ϊr[i]�������|right[i]|=1����s[ [r[i]-len[i]+1,r[i]-len[fa[i]]] ~ r[i] ]��Щ�Ӵ�������һ�Ρ�
��ô����[r[i]-len[i]+1, r[i]-len[fa[i]]]�������ô�ʱ��Ӧ�ĳ���(r-i+1)��������Сֵ�����ά��ÿ��λ����С��r�Ϳ��ԣ���
����λ��[r[i]-len[fa[i]]+1, r[i]������len[fa[i]]+1���£����ֱ��ά����Сֵ����
���Խ������߶����Ϳ����ˡ�
SA�����������в��ظ����֣��������뵽height������һ��λ��i������Ϊ��˵����γɵ���̵Ĳ��ظ����ִ�����l=max(ht[i],ht[i+1])+1.
��ôi�ܶ�����i~i+l-2����l������i���Ӵ�����>lʱһ��Ҳֻ������һ�Σ������Զ�i+l-1~n���׶�Ӧ����(p-i+1)��ֵ���������߶���ά����
l==r��ʱ����PushDown��mdzz��
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
	{//�߶�����ûһ��д�ԡ�_�� 
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
