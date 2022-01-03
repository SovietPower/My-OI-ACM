/*
147544kb	9488ms
$Description$
给定一个长为n的序列，多次询问[l,r]中最大的只出现一次的数。强制在线。
$Solution$
我也不知道该怎么说，反正就是预处理 建主席树，套堆/set，树i存l为i，r为[i,n]的答案（这样就是在某棵树上单点查maxv了）。
处理好最初的树，就可以利用主席树根据前缀建树的性质，每个点i的建树只需要处理i位置。
那么最初的树就是将所有的数在区间[第一次出现位置,nxt[]-1]中加入这个数。
当左端点i移动时，A[i-1]的贡献没了，要删掉；但是如果A[i-1]在后面出现，则还要在[nxt[A[i-1]],nxt[nxt[A[i-1]]]-1]上加入A[i-1]。(A[i]已经处理了，要么在建最初树时要么在先前建的树中)
也不是每棵树每个节点都套堆，堆只需要帮助建主席树时加加删删（还是利用前缀），要用的只是根据堆得到的每个节点的maxv[]，所以堆还是4n大就可以。。
和CF那题不同的是这题固定l更方便，那题固定r好些。所以只需要nxt(和最靠前的一个las用来建最初的树)。
第一次主席树区间修改。。在信息覆盖当前区间时直接给节点赋值,return；查询单点时加上沿路节点的mx[]（标记永久化）。
注意新建节点时copy x的mx[]。因为每次删除是完全删除上一次的加入，so在未递归到完全覆盖区间前copy mx是对的？真这样麻烦吗。。以后是不是该乖乖写Update()。。

询问的限制条件可以看成三个维度，即在某三维空间内找权值最大的点，可以用K-D Tree。出题人说这不应是正解，可以卡，只是数据问题跑的比主席树快。。
不过还是K-D Tree更好的应用吧，不想看了，先放着。。
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1e5+5;

int n,Q,A[N],las[N],nxt[N],rcnt,root[N*3],pos[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Tree//Persistent Segment Tree
{
	#define S N*100//我也不知道这样搞区间修改的主席树会有多少节点(2个log？) 
	#define lson son[x][0]
	#define rson son[x][1]
	#define ToL l,m,rt<<1
	#define ToR m+1,r,rt<<1|1
	struct Heap
	{
		std::priority_queue<int> h,d;
		inline void Insert(int x) {h.push(x);}
		inline void Delete(int x) {d.push(x);}
		inline void Maintain(){
			while(!h.empty()&&!d.empty()&&h.top()==d.top()) h.pop(),d.pop();
		}
		inline int Top(){
			Maintain(); return h.empty()?0:h.top();
		}
	}hp[N<<2];
	int tot,son[S][2],mx[S];

//	inline void Update(int x){//Update没啥用啊 又不用区间信息 
//		mx[x]=std::max(mx[lson],mx[rson]);
//	}
	void Insert(int &y,int x,int l,int r,int rt,int L,int R,int v)//rt:一般线段树的节点 存储堆 
	{
		y=++tot;
		if(L<=l && r<=R){
			hp[rt].Insert(v), mx[y]=hp[rt].Top(), son[y][0]=lson, son[y][1]=rson;
			return ;
		}
		int m=l+r>>1; mx[y]=mx[x];//!
		if(L<=m)
			if(m<R) Insert(son[y][0],lson,ToL,L,R,v), Insert(son[y][1],rson,ToR,L,R,v);
			else son[y][1]=rson, Insert(son[y][0],lson,ToL,L,R,v);
		else son[y][0]=lson, Insert(son[y][1],rson,ToR,L,R,v);
	}
	void Delete(int &y,int x,int l,int r,int rt,int L,int R,int v)
	{
		y=++tot;
		if(L<=l && r<=R){
			hp[rt].Delete(v), mx[y]=hp[rt].Top(), son[y][0]=lson, son[y][1]=rson;
			return;
		}
		int m=l+r>>1; mx[y]=mx[x];//!
		if(L<=m)
			if(m<R) Delete(son[y][0],lson,ToL,L,R,v), Delete(son[y][1],rson,ToR,L,R,v);
			else son[y][1]=rson, Delete(son[y][0],lson,ToL,L,R,v);
		else son[y][0]=lson, Delete(son[y][1],rson,ToR,L,R,v);
	}
	int Query(int x,int l,int r,int pos)
	{
		if(!x) return 0;//这个没啥用啊...
		if(l==r) return mx[x];
		int m=l+r>>1;
		if(pos<=m) return std::max(mx[x],Query(lson,l,m,pos));
		else return std::max(mx[x],Query(rson,m+1,r,pos));
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read(), Q=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int i=1; i<=n; ++i) las[i]=n+1;
	for(int i=n; i; --i) nxt[i]=las[A[i]], las[A[i]]=i;
	for(int i=n; i; --i)//直接枚举值域建树就可以啊 话说倒着插入堆会更快吗 
		if(las[i]<=n) T.Insert(root[rcnt],root[rcnt++],1,n,1,las[i],nxt[las[i]]-1,i);//参数顺序 
	pos[1]=root[rcnt];//root[rcnt] not rcnt→_→
	for(int i=1; i<n; ++i)
	{
		T.Delete(root[rcnt],root[rcnt++],1,n,1,i,nxt[i]-1,A[i]);
		if(nxt[i]<=n)
			T.Insert(root[rcnt],root[rcnt++],1,n,1,nxt[i],nxt[nxt[i]]-1,A[i]);
		pos[i+1]=root[rcnt];
	}
	for(int ans=0,i=1,l,r; i<=Q; ++i)
	{
		l=(read()+ans)%n+1, r=(read()+ans)%n+1;
		if(l>r) std::swap(l,r);//l>r&&(std::swap(l,r),1);
		printf("%d\n",ans=T.Query(pos[l],1,n,r));
	}
	return 0;
}
