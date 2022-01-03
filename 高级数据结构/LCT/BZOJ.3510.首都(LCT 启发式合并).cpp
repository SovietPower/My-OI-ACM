/*
4044kb	2256ms
�����е㵽ĳ����������̣������������ġ�������ζ�̬ά����
���������ϲ��������һ����������������֮���������ϣ������ںϲ���ʱ��������ʽ�ϲ���ÿ�ϲ�һ������sz[]����ǿ�����������(��Ϊroot)���������sz[]*2�Ƿ�>n��
��>n������fa�ƶ�һ��(�ȰѺϲ���Splay����)�����Ļ�һ������sz[]����ǿ������У����ƶ��������ᳬ��sz[]С�������ĵ���(�������ƶ��������ᳬ��O(n)?)��
���Ӷ�O(nlog^2n).
����ʵ�֡���~~��ͨ�������ر�򵥡���~~Ҳ�������
��Link��Ȼ����������������(��ȴ������ң�).
ÿ��һ�����ж�����������������sz��*2�Ƿ�>��ǰ����sz������ǣ���ǰ����Ҫ�ҵ����ģ�������һ������sz[x]*2 < sz[root]����ôroot���Ǹ��ˡ�
�����ж�����ģ���Щ����Ӧ����������һ�Ρ���Ϊ�����С����sz[x]*2==sz[root] && id[x]<id[root]�������root������
�ò��鼯ά�����ġ�(Find_root()̫����)
(����Ҫ����������ȡmax�������С������������С����Ϊ��Ȼ�������Ǳ߾Ͳ�������һ�ߣ����ο���һ�߻��ֲ�����һ������)
(ά���������ֵ�����Ĳ��аɣ��ϲ����º�����鷳��ֱ����sz[]�Ϳ�����).

Ϊʲôһ��ҪMake_root()���ġ���ͻȻ���ø���������LCT����֪����ô�ߵ��ˡ����Ժ���˵�ɡ���~~��ˮ��ȥ~~
ע���õ��sz[]ǰ��Splay()���£�
���ڸ������Ŀ���ͨ�������������� �ܵ�O(nlogn)�ķ���(�����������⡣��)�Ժ������� 
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1e5+5;

#define lson son[x][0]
#define rson son[x][1]

int n,m,Ans,sz[N],sz_i[N],_fa[N],fa[N],son[N][2],sk[N];
bool tag[N];
inline void Update(int x){
	sz[x]=sz[lson]+sz[rson]+sz_i[x]+1;
}
inline bool n_root(int x){
	return son[fa[x]][0]==x||son[fa[x]][1]==x;
}
inline void Rev(int x){
	std::swap(lson,rson), tag[x]^=1;
}
inline void PushDown(int x){
	if(tag[x]) Rev(lson),Rev(rson),tag[x]=0;
}
void Rotate(int x)
{
	int a=fa[x],b=fa[a],l=son[a][1]==x,r=l^1;
	if(n_root(a)) son[b][son[b][1]==a]=x;
	if(son[x][r]) fa[son[x][r]]=a;
	fa[a]=x, fa[x]=b, son[a][l]=son[x][r], son[x][r]=a;
	Update(a);
}
void Splay(int x)
{
	int t=1,a=x; sk[1]=x;
	while(n_root(a)) sk[++t]=a=fa[a];
	while(t) PushDown(sk[t--]);
	while(n_root(x))
	{
		a=fa[x];
		if(n_root(a)) Rotate(son[a][1]==x^son[fa[a]][1]==a?x:a);
		Rotate(x);
	}
	Update(x);
}
void Access(int x){
	for(int pre=0; x; x=fa[pre=x])
		Splay(x), sz_i[x]+=sz[rson]-sz[pre], rson=pre;//Update(x);
}
void Make_root(int x){
	Access(x), Splay(x), Rev(x);
}
void Split(int x,int y){
	Make_root(x), Access(y), Splay(y);
}
int Find_root(int x)
{
	Access(x), Splay(x);
	while(lson) x=lson;
	return x;
}
void Link(int x,int y){
	Split(x,y), sz_i[y]+=sz[x], fa[x]=y, Update(y);
}
int Get_fa(int x){
	return x==_fa[x]?x:_fa[x]=Get_fa(_fa[x]);
}
//int Next(int x){//?
//	PushDown(x), x=rson;
//	while(lson) PushDown(x),x=lson;
//	return x;
//}
int q[N],cnt;
void DFS(int x,int lim)
{
	PushDown(x);
	if(lson) DFS(lson,lim);
	if(cnt>lim) return;
	q[++cnt]=x;
	if(cnt>lim) return;
	if(rson) DFS(rson,lim);
}
int Union(int x,int y)
{
	int r1=Get_fa(x),r2=Get_fa(y);
//	int r1=Find_root(x),r2=Find_root(y);
	Splay(r1), Splay(r2);//��Splay����sz[]��
	if(sz[r1]>sz[r2]||(sz[r1]==sz[r2]&&y>x)) std::swap(x,y),std::swap(r1,r2);//x->y r1->r2
	int lim=sz[r1],res=r2,tot=sz[r2]+sz[r1];
	Link(x,y), Access(x), Splay(r2);
	cnt=0;
	DFS(r2,lim);
	for(int sum,i=1; i<=cnt; ++i)
	{
		Splay(q[i]), sum=sz[son[q[i]][1]]+sz_i[q[i]]+1;
//		if(tot<sum<<1) res=q[i];//����ôд�ǲ����е����Ⱑ 
//		else if(tot==sum<<1) res=std::min(res,q[i]);
		if(tot<sum<<1||(tot==sum<<1&&q[i]<=res)) res=q[i];
		else break;
	}
	Make_root(res);
	_fa[r1]=_fa[r2]=_fa[res]=res/*��������*/;
	return res;
}
inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read(),m=read();
	int res=0,x,y; char opt[5];
	for(int i=1; i<=n; ++i) _fa[i]=i, res^=i, sz[i]=1;
	while(m--)
	{
		scanf("%s",opt);
		if(opt[0]=='A') x=read(),y=read(),res^=Get_fa(x)^Get_fa(y)^Union(x,y);
		else if(opt[0]=='Q') x=read(),printf("%d\n",Get_fa(x));//printf("%d\n",Find_root(x));
		else printf("%d\n",res);
	}
	return 0;
}
