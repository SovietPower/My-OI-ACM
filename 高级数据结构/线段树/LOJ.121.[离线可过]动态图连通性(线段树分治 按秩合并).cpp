/*
1548ms	48256K
��ʱ��Ϊ�±꽨�߶������߶���ÿ���ڵ㿪��vector��
��ÿ�����������ʱ���ڼ����߶����������������߰�ʱ������߶����Ķ�Ӧ�����ϣ���Ӱ��$O(\log n)$���ڵ㡣
ѯ�ʾͷ����߶����Ķ�ӦҶ�ӽڵ��ϡ�

Ȼ���������DFS��������һ���ڵ�ʱ���������������������г��ֵı�ȫ���ӵ�ͼ����ϲ�������֮�����뿪�����ʱ������
�����ò�·��ѹ�������Ⱥϲ��Ĳ��鼯ά����ͨ�ԡ������Ϳ��Գ����ˡ�
�ϲ�ʱ��ջ��¼�ϲ�ǰ״̬���ϲ�ǰ�ĸ��ڵ���$x$����$fa[x]$���У���Ϊ�ϲ���ʱ���Ǻϲ����ϸ��ڵ㣬��$x$����$fa[x]$��һ������
����ȸı�ҲҪ����ջ��

����ʽ�ϲ�����Ȼ��ǰ�size����ν��
*/
#include <map>
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define Vec std::vector<int>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=5005,M=5e5+5;

int n,m,fa[N],dep[N],top;
std::map<pr,int> las;
char IN[MAXIN],*SS=IN,*TT=IN;
struct Node
{
	int x,dep;
}sk[M<<1];//M�͹��ɡ���
struct Operation
{
	int id,u,v;
}opt[M];
struct Segment_Tree
{
	#define lson rt<<1
	#define rson rt<<1|1
	std::vector<int> vec[M<<2];
	void Update(int l,int r,int rt,int L,int R,int id)
	{
		if(L<=l && r<=R) return (void)vec[rt].push_back(id);
		int m=l+r>>1;
		if(L<=m) Update(l,m,rt<<1,L,R,id);
		if(m<R) Update(m+1,r,rt<<1|1,L,R,id);
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int Get_fa(int x){
	return x==fa[x]?x:Get_fa(fa[x]);
}
inline void Merge(int x,int y)
{
	if((x=Get_fa(x))==(y=Get_fa(y))) return;
	if(dep[y]>dep[x]) std::swap(x,y);//y->x
	fa[y]=x, sk[++top]=(Node){y,dep[y]};
	if(dep[x]==dep[y]) sk[++top]=(Node){x,dep[x]++};
}
inline void Delete(int bef)
{
	while(top>bef)
	{
		int x=sk[top].x;
		fa[x]=x, dep[x]=sk[top--].dep;
	}
}
void DFS(int l,int r,int rt)
{
	int now=top;
	const Vec &v=T.vec[rt];
	for(int i=0,lim=v.size(); i<lim; ++i) Merge(opt[v[i]].u,opt[v[i]].v);
	if(l==r){
		if(opt[l].id==2)//ѯ��ֱ����Ҷ�ڵ��� 
			putchar(Get_fa(opt[l].u)==Get_fa(opt[l].v)?'Y':'N'),putchar('\n');
	}
	else DFS(l,l+r>>1,lson), DFS((l+r>>1)+1,r,rson);
	Delete(now);
}

int main()
{
	n=read(), m=read();
	for(int i=1; i<=n; ++i) fa[i]=i;
	std::map<pr,int>::iterator it;
	for(int id,x,y,i=1; i<=m; ++i)
	{
		id=read(), x=read(), y=read();
		if(x>y) std::swap(x,y);
		if(!id) las[mp(x,y)]=i;
		else if(id==1) it=las.find(mp(x,y)), T.Update(1,m,1,it->second,i,i), it->second=0;//����������i����ν�ˣ�i���Ѳ���ѯ�� 
		opt[i]=(Operation){id,x,y};
	}
	for(it=las.begin(); it!=las.end(); ++it)
		if(it->second) T.Update(1,m,1,it->second,m,it->second);
	DFS(1,m,1);

	return 0;
}
