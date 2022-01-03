/*
163128kb	16108ms
����ÿ��ѯ�ʣ���s���ֵĴ�������s��SAM������󵽴�ڵ��|right|��SAM����ģ�崮�������Ӵ���״̬�� û��ת���Ǿ���ƥ�䲻���ˣ���
���Ǿͳ��˶�̬ά��right���ϵĴ�С��
�����Ļ���ÿ�μ���һ���ַ� ֻ��Ҫ����fa����++|right|�Ϳ����ˡ�Ҫע�⸴�ƽڵ�nq��ʱ��|right|ҲҪ���ơ�
������Ҫ��LCT����̬ά��parent������֧�ָ��µ㵽����������ֵ������ɾ�ߡ�ѯ�ʵ�ʱ��ֱ���������ڵ��size���ɡ�
��������и��������Բ���ҪMake_root()��
������sz[]ά�����ǵ�Ҷ�ڵ��size��ע��sz[]�ĸ��£����ı�SAM�е�fa[]ʱ��Ҫ�޸�parent����
����sz[]��ֵ��sz[np]=1��sz[nq]=0��������ǰ������������ֻ��ÿ��np�ߵ��ĳ�ʼ��Ϊ1.
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=(6e5+5)*2;

namespace LCT
{
	#define lson son[x][0]
	#define rson son[x][1]
	int fa[N],son[N][2],sz[N],tag[N],sk[N];

	inline void Update(int x,int v){
		sz[x]+=v, tag[x]+=v;
	}
	inline void PushDown(int x){
		if(tag[x]) Update(lson,tag[x]), Update(rson,tag[x]), tag[x]=0;
	}
	inline bool n_root(int x){
		return son[fa[x]][0]==x||son[fa[x]][1]==x;
	}
	void Rotate(int x)
	{
		int a=fa[x],b=fa[a],l=son[a][1]==x,r=l^1;
		if(n_root(a)) son[b][son[b][1]==a]=x;
		if(son[x][r]) fa[son[x][r]]=a;
		fa[x]=b, fa[a]=x, son[a][l]=son[x][r], son[x][r]=a;
	}
	void Splay(int x)
	{
		int a=x,t=1; sk[1]=x;
		while(n_root(a)) sk[++t]=a=fa[a];
		while(t) PushDown(sk[t--]);
		while(n_root(x))
		{
			if(n_root(a=fa[x])) Rotate(son[a][1]==x^son[fa[a]][1]==a?x:a);
			Rotate(x);
		}
	}
	void Access(int x){
		for(int pre=0; x; x=fa[pre=x])
			Splay(x), rson=pre;//, Update(x);
	}
	void Link(int x,int y){//Link x->y
		Access(y), Splay(y), fa[x]=y, Update(y,sz[x]);
	}
	void Cut(int x){//Cut x->fa[x]
		Access(x), Splay(x), Update(lson,-sz[x]), lson=fa[lson]=0;//Update()!
	}
}
struct Suffix_Automaton
{
	int l,tot,las,Mask,fa[N],son[N][26],len[N];
	char s[3000005];
	void Insert(int c)
	{
		int p=las,np=++tot;
		len[las=np]=len[p]+1, LCT::sz[np]=1;
		for(; p&&!son[p][c]; p=fa[p]) son[p][c]=np;
		if(!p) fa[np]=1, LCT::Link(np,1);
		else
		{
			int q=son[p][c];
			if(len[q]==len[p]+1) fa[np]=q, LCT::Link(np,q);
			else
			{
				int nq=++tot; len[nq]=len[p]+1;
				memcpy(son[nq],son[q],sizeof son[q]);
				fa[nq]=fa[q], LCT::Link(nq,fa[q]);
				fa[np]=fa[q]=nq, LCT::Cut(q), LCT::Link(np,nq), LCT::Link(q,nq);
				for(; son[p][c]==q; p=fa[p]) son[p][c]=nq;
			}
		}
	}
	inline void Decode_With_Mask(int mask)//mask�Ǵ��� 
	{
		for(int i=0; i<l; ++i)
			mask=(mask*131+i)%l, std::swap(s[i+1],s[mask+1]);
	}
	void Init()//����д�� ��Ϊû��Decode����
	{
		tot=las=1, Mask=0;
		scanf("%s",s+1), l=strlen(s+1);
		for(int i=1; i<=l; ++i) Insert(s[i]-'A');
	}
	void Build()
	{
		scanf("%s",s+1), l=strlen(s+1);
		Decode_With_Mask(Mask);
		for(int i=1; i<=l; ++i) Insert(s[i]-'A');
	}
	int Walk()
	{
		int p=1;
		for(int i=1; i<=l; ++i)
			if(!(p=son[p][s[i]-'A'])) return 0;
		LCT::Splay(p);
		return Mask^=LCT::sz[p], LCT::sz[p];
	}
	void Query()
	{
		scanf("%s",s+1), l=strlen(s+1);
		Decode_With_Mask(Mask);
		printf("%d\n",Walk());
	}
}sam;

int main()
{
	int Q; char opt[8];
	scanf("%d",&Q), sam.Init();
	while(Q--){
		if(scanf("%s",opt),opt[0]=='A') sam.Build();
		else sam.Query();
	}
	return 0;
}
