/*
41644 kb  2404 ms
题意:n个数，有两个操作:1.修改某个数为v；2.询问一段区间第k小的数 

如果没有修改，则可以用线段树，每个节点P[a,b]存储大小为b-a+1的数组，代表其中的数 
同时，这个数组还是要排好序的 
直接找答案很不方便，于是考虑对数组二分答案，求比它小的数的个数 
关于构造过程，更新完子节点后，子节点维护的数组就是有序的了，可以通过归并得到父节点的有序数组 
这样空间O(nlogn) 每次查询时间O((logn)^2)

修改同时有序，二叉排序树是好选择 
线段树每个节点维护一棵平衡树，查询时在平衡树中查询；
修改一个点就将它从平衡树中删掉，更改后再插入(所有包含这个点的区间都要执行) 
空间复杂度为O(dep*n),dep为线段树的深度，大约就是O(nlogn)
时间O(n(logn)^3)
*/
#include<cstdio>
#include<cctype>
#define gc() getchar()
//#define gc() (SS==TT &&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1e5+5,M=15*N,MAXIN=5e6;

int n,q,tot,A[N],root[N],size,fa[M],son[M][2],sz[M],cnt[M],t[M];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

inline void Update(int rt)
{
	sz[rt]=sz[son[rt][0]]+sz[son[rt][1]]+cnt[rt];
}
void Rotate(int x,int &k)
{
	int a=fa[x],b=fa[a],l=son[a][1]==x,r=l^1;
	if(a==k) k=x;
	else son[b][son[b][1]==a]=x;
	fa[x]=b, fa[a]=x, fa[son[x][r]]=a,
	son[a][l]=son[x][r], son[x][r]=a;
	Update(a), Update(x);
}
void Splay(int x,int &k)
{
	while(x!=k)
	{
		int a=fa[x],b=fa[a];
		if(a!=k)
		{
			if((son[a][0]==x)^(son[b][0]==a)) Rotate(x,k);
			else Rotate(a,k);
		}
		Rotate(x,k);
	}
}
void Get_Rank(int v,int x)
{
	if(!root[x]) return;//!
	int k=root[x];
	while(t[k]!=v && son[k][v>t[k]]) k=son[k][v>t[k]];
	Splay(k,root[x]);
}
void Insert(int v,int x)
{
	int f=0,k=root[x];
	while(k && v!=t[k]) f=k,k=son[k][v>t[k]];
	if(k) ++cnt[k];
	else
	{
		k=++size, cnt[k]=sz[k]=1, t[k]=v, fa[k]=f;
		if(f) son[f][v>t[f]]=k;
	}
	Splay(k,root[x]);
}
void Delete(int v,int x)
{
	Get_Rank(v,x);
	int k=root[x];
	if(cnt[k]>1) {--cnt[k],--sz[k]; return;}
	else if(!son[k][0]||!son[k][1]) root[x]=son[k][0]|son[k][1];
	else
	{
		int p=son[k][0];
		k=son[k][1], root[x]=k;//!
		while(son[k][0]) k=son[k][0];
		sz[k]+=sz[p], fa[p]=k, son[k][0]=p;
		Splay(k,root[x]);
	}
	fa[root[x]]=0;//!
}
void Build(int l,int r,int rt,int pos)
{
	Insert(A[pos],rt);
	if(l==r) return;
	int m=l+r>>1;
	if(pos<=m) Build(l,m,rt<<1,pos);
	else Build(m+1,r,rt<<1|1,pos);
}
void Modify(int l,int r,int rt,int pos,int v)
{
//	printf("Modify:%d~%d rt:%d pos:%d v:%d\n",l,r,rt,pos,v);
	Delete(A[pos],rt), Insert(v,rt);
	if(l>=r) return;
	int m=l+r>>1;
	if(pos<=m) Modify(l,m,rt<<1,pos,v);
	else Modify(m+1,r,rt<<1|1,pos,v);
}
void Calc(int v,int k)
{
	while(k)
	{
//		printf("k:%d v:%d tot:%d\n",k,v,tot);
		if(v==t[k]) {tot+=sz[son[k][0]]; return;}
		if(v>t[k]) tot+=sz[son[k][0]]+cnt[k],k=son[k][1];
		else k=son[k][0];
	}
}
void Query(int l,int r,int rt,int L,int R,int v)
{
//	printf("Query:%d~%d rt:%d L~R:%d~%d v:%d\n",l,r,rt,L,R,v);
	if(L<=l && r<=R) {Calc(v,root[rt]); return;}
	int m=l+r>>1;
	if(L<=m) Query(l,m,rt<<1,L,R,v);
	if(m<R) Query(m+1,r,rt<<1|1,L,R,v);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("1901.in","r",stdin);
//	freopen("1901.out","w",stdout);
#endif

	n=read(),q=read();
	for(int i=1;i<=n;++i) A[i]=read(),Build(1,n,1,i);
	char s[5];
	int i,j,k;
	while(q--)
	{
		scanf("%s",s),i=read(),j=read();
		if(s[0]=='C') Modify(1,n,1,i,j),A[i]=j;
		else
		{
			k=read();
			int l=0,r=1e9,m,ans=0;
			while(l<=r)
			{
				m=l+r>>1;
				tot=0, Query(1,n,1,i,j,m);
//				printf("%d~%d %d\n",l,r,tot);
				if(tot>=k) r=m-1;
				else l=m+1,ans=m;
			}
			printf("%d\n",ans);
		}
	}

	return 0;
}
