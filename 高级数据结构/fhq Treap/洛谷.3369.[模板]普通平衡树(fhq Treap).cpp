#include<cstdio>
#include<cctype>
#include<algorithm>
//#define gc() getchar()
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1e5+5,MAXIN=2e6;

char IN[MAXIN],*SS=IN,*TT=IN;
int size,sz[N],son[N][2],val[N],fix[N];
int New_Node(int v)
{
	sz[++size]=1, val[size]=v, fix[size]=rand();
	return size;
}
inline void Update(int rt)
{
	sz[rt]=sz[son[rt][0]]+sz[son[rt][1]]+1;
}
void Split(int rt,int v,int &x,int &y)
{
	if(!rt) x=y=0;
	else
	{
		if(val[rt]<=v) x=rt,Split(son[rt][1],v,son[rt][1],y);
		else y=rt,Split(son[rt][0],v,x,son[rt][0]);
		Update(rt);
	}
}
int Merge(int x,int y)
{
	if(!x||!y) return x+y;
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
int Kth(int rt,int k)
{
	while(1)
	{
		if(sz[son[rt][0]]+1==k) return rt;
		if(sz[son[rt][0]]<k) k-=sz[son[rt][0]]+1,rt=son[rt][1];
		else rt=son[rt][0];
		}
}
int Find(int rt,int w)
{
	while(son[rt][w]) rt=son[rt][w];
	return val[rt];
}
inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	int q=read(),opt,v,x,y,z,root=0;
	while(q--)
	{
		opt=read(),v=read();
		switch(opt)
		{
			case 1: Split(root,v,x,y),root=Merge(Merge(x,New_Node(v)),y);//Insert
					break;
			case 2: Split(root,v,x,z),Split(x,v-1,x,y);//Delete
					y=Merge(son[y][0],son[y][1]),root=Merge(Merge(x,y),z);
					break;
			case 3: Split(root,v-1,x,y),printf("%d\n",sz[x]+1);//Get_Rank
					root=Merge(x,y);
					break;
			case 4: printf("%d\n",val[Kth(root,v)]);//Rank
					break;
			case 5: Split(root,v-1,x,y),printf("%d\n",val[Kth(x,sz[x])]);//printf("%d\n",Find(x,1));
					root=Merge(x,y);//Precursor
					break;
			case 6: Split(root,v,x,y),printf("%d\n",val[Kth(y,1)]);//printf("%d\n",Find(y,0));
					root=Merge(x,y);//Successor
					break;
		}
	}

	return 0;
}
