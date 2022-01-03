//注意反转时先分裂r，因为l,r是针对整棵树的排名 
#include<cstdio>
#include<cctype>
#include<algorithm>
//#define gc() getchar()
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1e5+7,MAXIN=2e6;

int n,root,sz[N],son[N][2],fix[N],tag[N];
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
	sz[rt]=sz[son[rt][0]]+sz[son[rt][1]]+1;
}
inline void Down(int rt)
{
	tag[son[rt][0]]^=1,
	tag[son[rt][1]]^=1;
	std::swap(son[rt][0],son[rt][1]);
	tag[rt]=0;//清空！
}
int Build(int l,int r)
{
	if(l>r) return 0;
	int m=l+r>>1;
	fix[m]=rand(),sz[m]=1;
	son[m][0]=Build(l,m-1),
	son[m][1]=Build(m+1,r);
	Update(m);
	return m;
}
void Split(int rt,int k,int &x,int &y)
{
	if(!rt) x=y=0;
	else
	{
		if(tag[rt]) Down(rt);
		if(k<=sz[son[rt][0]]) y=rt,Split(son[rt][0],k,x,son[rt][0]);
		else x=rt,Split(son[rt][1],k-sz[son[rt][0]]-1,son[rt][1],y);
		Update(rt);
	}
}
int Merge(int x,int y)
{
	if(!x||!y) return x+y;
	if(tag[x]) Down(x);
	if(tag[y]) Down(y);
	if(fix[x]<fix[y])
	{
		son[x][1]=Merge(son[x][1],y);
		Update(x);
		return x;
	}
	else
	{
		son[y][0]=Merge(x,son[y][0]);
		Update(y);
		return y;
	}
}
void Reverse()
{
	int x,y,z,l=read(),r=read();
	Split(root,r+1,y,z), Split(y,l,x,y);
	tag[y]^=1;
	root=Merge(Merge(x,y),z);
}
void DFS(int rt)
{
	if(tag[rt]) Down(rt);
	if(son[rt][0]) DFS(son[rt][0]);
	if(rt!=1&&rt!=n+2) printf("%d ",rt-1);
	if(son[rt][1]) DFS(son[rt][1]);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("3391.in","r",stdin);
#endif

	n=read();
	root=Build(1,n+2);
	int q=read();
	while(q--) Reverse();
	DFS(root);

	return 0;
}
