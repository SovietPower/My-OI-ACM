#include<cstdio>
#include<cctype>
#include<algorithm>
#define gc() (SS==TT &&(TT=(SS=IN)+fread(IN,1,1<<15,stdin),SS==TT)?EOF:*SS++)
const int N=1e5+7,DEL=-1<<30;

int n,m,val[N],son[N][2],dis[N],fa[N];//id[N]这个数组完全用不到，比较编号直接比较AB即可 
//long long val[N];//开int能有效提高效率 
char IN[1<<15],*SS=IN,*TT=IN;
//bool del[N];//也不需要，改变val值即可 

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int Merge(int A,int B)
{
	if(!A||!B) return A+B;
	if(val[A]>val[B]||(val[A]==val[B]&&A>B)) std::swap(A,B);
	son[A][1]=Merge(son[A][1],B);
	fa[son[A][1]]=A;
	if(dis[son[A][1]]>dis[son[A][0]]) std::swap(son[A][1],son[A][0]);
//	if(!son[A][1]) dis[A]=0;
//	else dis[A]=dis[son[A][1]]+1;
	dis[A]=dis[son[A][1]]+1;
	return A;
}
int Top(int p)
{
	while(fa[p]) p=fa[p];
	return p;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("3377.in","r",stdin);
	freopen("3377.out","w",stdout);
#endif

	dis[0]=-1;
	n=read(),m=read();
	for(int i=1;i<=n;++i) val[i]=read();//,fa[i]=i;
	int opt,x,y;
	while(m--)
	{
		opt=read(),x=read();
		if(opt==1)
		{
			y=read();
			if(val[x]==DEL||val[y]==DEL||x==y) continue;
			Merge(Top(x),Top(y));//,printf("%d:%d %d:%d\n",x,Top(x),y,Top(y));
		}
		else if(val[x]==DEL)
			puts("-1");
		else
		{
			y=Top(x);
			printf("%d\n",val[y]),
			val[y]=DEL;
			fa[son[y][0]]=fa[son[y][1]]=0;
			Merge(son[y][0],son[y][1]);//,printf("%d:%d %d:%d\n",x,Top(x),y,Top(y));
		}
	}

	return 0;
}
