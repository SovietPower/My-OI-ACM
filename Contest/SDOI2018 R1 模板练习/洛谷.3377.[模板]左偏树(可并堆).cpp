#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define MAXIN 50000//这个到底需要多大啊QAQ 
const int N=1e5+5,DEL=-1<<30;

char IN[MAXIN],*SS=IN,*TT=IN;
namespace Leftist_Tree
{
	#define lson son[x][0]
	#define rson son[x][1]

	int fa[N],son[N][2],dis[N],val[N];
	int Merge(int x,int y)
	{
		if(!x||!y) return x^y;
		if(val[x]>val[y]||(val[x]==val[y]&&x>y)) std::swap(x,y);
		rson=Merge(rson,y), fa[rson]=x;
		if(dis[lson]<dis[rson]) std::swap(lson,rson);
		dis[x]=dis[rson]+1;
		return x;
	}
	inline int Top(int x){
		while(fa[x]) x=fa[x];
		return x;
	}
}
using namespace Leftist_Tree;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	dis[0]=-1;
	int n=read(),Q=read(),opt,x,y;
	for(int i=1; i<=n; ++i) val[i]=read();
	while(Q--)
	{
		opt=read(),x=read();
		if(opt==1)
		{
			y=read();
			if(val[x]==DEL||val[y]==DEL||x==y) continue;
			if((x=Top(x))!=(y=Top(y))) Merge(x,y);
		}
		else if(val[x]==DEL) puts("-1");
		else
		{
			printf("%d\n",val[x=Top(x)]),val[x]=DEL;
			fa[lson]=fa[rson]=0, Merge(lson,rson);//记得清空fa[]!
		}
	}
	return 0;
}
