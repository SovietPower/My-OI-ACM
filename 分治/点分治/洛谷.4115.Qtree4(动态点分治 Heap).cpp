/*
$Description$
����һ�ñߴ�Ȩ��������ʼʱ���е�Ϊ��ɫ�����ֲ�����1. ��תĳ�����ɫ�� 2. ѯ��������Զ��������ɫ�ڵ�ľ��루ֻ��һ����Ϊ0����
$n\leq 10^5,\ m\leq 2\times10^5$��
$Solution$
��ÿ��Solve������root�����������γ�һ�����Ϊlogn�������ͽ���������ɡ���
���Ƕ�ÿ��rootά����������: ����Ͻ�����������а׵㵽����һ��(������е�fa[x])�ľ���(��Ϊh1)���Լ���������������h1�����ֵ���δ�ֵ(�������д���)(��Ϊh2) 
Ҫ����ʱ������ɾ�����룬ͬʱҪȡ��ֵ���ö�ά�����ɡ�ɾ���ö���һ����ʵ�֡�
��Ҫ��һ����Ansͳ�ƴ𰸣���ÿ��root��h2ȥ����Ans��
�޸�ʱһ����ֻ��Ӱ�����������Ƚڵ�(��logn��)������ֻ��Ҫ�޸�ֵ����(�����ľ���·��)������ֱ���ö�ʵ�֣����Ӷ�O(log^2n) 
����Ҫ��ѯ���������ľ��룬dis[a]+dis[b]-2*dis[lca]���ɣ���RMQ��O(1)��LCA(������ռ���2����).

ע����޸�ʱһ��Ҫ������������������Ĺ���heap.top���޸����ټ���heap.top��
�����ڷ���ÿ����xʱ��h2[x]�м���0����Ϊ2����ſ��ԶԴ��й��ף�x��ʼΪ�׵��ǺϷ��ġ�ͬʱ�ڰ�����Ϊ�ڵ�ʱֱ�ӿ���ɾ0���������ۡ�
��Զ��Ȩ�Ǹ���ʱ��Ӧ��0��
���������� �� �߶���+�������У���Ȩ��Ϊ1��������ǳ��ࡣ
�����������е�������https://www.cnblogs.com/SovietPower/p/10333155.html��
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1e5+5,MAXIN=3e5;

int n,Min,root,sz[N],Enum,H[N],to[N<<1],nxt[N<<1],val[N<<1],fa[N];
int dis[N],lg[N<<1],tm,cnt,id[N],A[N<<1][18],pos[N];//RMQ for LCA(�о�д�ĺ��鷳--)
bool sta[N],vis[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Heap
{
	std::priority_queue<int> h,d;
	inline void Insert(int x){
		h.push(x);
	}
	inline void Delete(int x){
		d.push(x);
	}
	inline int Size(){
		return h.size()-d.size();
	}
	inline void Fix(){
		while(d.size() && h.top()==d.top()) h.pop(),d.pop();
	}
	inline int Top(){
		Fix(); return h.top();
	}
	inline void Pop(){
		Fix(), h.pop();
	}
	inline int Sec(){
		int t=Top(); h.pop();//ע���Ҫ�ĵط�Ҫfix 
		int t2=Top(); h.push(t);
		return t2;
	}
	inline int Two(){
		int t=Top(); h.pop();//ע���Ҫ�ĵط�Ҫfix 
		int t2=Top(); h.push(t);
		return t+t2;
	}
	void Change(int x,bool s){
		if(s) Delete(x);
		else Insert(x);
	}
}h1[N],h2[N],Ans;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline void AddEdge(int u,int v,int w)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, val[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, val[Enum]=w;
}
void pre_DFS(int x,int f)
{
	int t=++tm; A[pos[x]=++cnt][0]=t, id[t]=x;
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=f)
			dis[to[i]]=dis[x]+val[i], pre_DFS(to[i],x), A[++cnt][0]=t;//������һ������ʱ�ټ��� 
}
void Init_RMQ()
{
	for(int i=2; i<=cnt; ++i) lg[i]=lg[i>>1]+1;//lg[]��С2N 
	for(int j=1; j<=lg[cnt]; ++j)
		for(int i=cnt-(1<<j-1); i; --i)//cnt-(1<<j-1) not n-(1<<j-1)!
			A[i][j]=std::min(A[i][j-1],A[i+(1<<j-1)][j-1]);
}
void Get_root(int x,int f,int tot)
{
	int mx=0; sz[x]=1;
	for(int v,i=H[x]; i; i=nxt[i])
		if(!vis[v=to[i]]&&v!=f)
		{
			Get_root(v,x,tot), sz[x]+=sz[v];
			if(sz[v]>mx) mx=sz[v];
		}
	mx=std::max(mx,tot-sz[x]);
	if(mx<Min) Min=mx, root=x;
}
void DFS(int x,int f,int d,Heap &h)
{//��ʼȫ�� ���ӽ�ȥ 
	h.Insert(d);
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[to[i]]&&to[i]!=f)
			DFS(to[i],x,d+val[i],h);
}
inline void Add_Ans(Heap &h){
//	if(h.Size()>=2) Ans.Insert(h.Top()+h.Sec());
	if(h.Size()>=2) Ans.Insert(h.Two());
}
inline void Del_Ans(Heap &h){
//	if(h.Size()>=2) Ans.Delete(h.Top()+h.Sec());
	if(h.Size()>=2) Ans.Delete(h.Two());
}
void Solve(int x)
{
	vis[x]=1, h2[x].Insert(0);
	for(int v,i=H[x]; i; i=nxt[i])
		if(!vis[v=to[i]])
		{
			Heap tmp; DFS(v,x,val[i],tmp);
			Min=N, Get_root(v,x,sz[v]), fa[root]=x;
			h1[root]=tmp;//h1[root]
			h2[x].Insert(tmp.Top());
			Solve(root);
		}
	Add_Ans(h2[x]);
}
int LCA(int l,int r)
{
	if(l>r) std::swap(l,r);
	int k=lg[r-l+1];
	return id[std::min(A[l][k],A[r-(1<<k)+1][k])];
}
int Calc_dis(int a,int b){
	return dis[a]+dis[b]-2*dis[LCA(pos[a],pos[b])];
}
void Change(int x,bool s)
{
	Del_Ans(h2[x]), h2[x].Change(0,s), Add_Ans(h2[x]);
	for(int now=x; fa[now]; now=fa[now])
	{
		Del_Ans(h2[fa[now]]);//!
		if(h1[now].Size()) h2[fa[now]].Delete(h1[now].Top());//����ǰ��ɾ�� 
		h1[now].Change(Calc_dis(x,fa[now]),s);//���dis��x��fa[now]�ģ�����now��fa[now]�ġ���mdzz 
		if(h1[now].Size()) h2[fa[now]].Insert(h1[now].Top());
		Add_Ans(h2[fa[now]]);
	}
}
inline char get(){
	char c=gc();
	while(c!='A'&&c!='C') c=gc();
	return c;
}

int main()
{
	n=read();
	for(int u,v,w,i=1; i<n; ++i) u=read(),v=read(),w=read(),AddEdge(u,v,w);
	pre_DFS(1,-1), Init_RMQ();
	Min=N, Get_root(1,-1,n), Solve(root);
	int m=read(),x,white=n;char opt[3];
	while(m--)
	{
//		scanf("%s",opt);
		if(/*opt[0]*/get()=='C') x=read(),Change(x,sta[x]^=1),white+=sta[x]?-1:1;
		else if(!white) puts("They have disappeared.");
		else printf("%d\n",white>1?std::max(0,Ans.Top()):0);
	}
	return 0;
}
