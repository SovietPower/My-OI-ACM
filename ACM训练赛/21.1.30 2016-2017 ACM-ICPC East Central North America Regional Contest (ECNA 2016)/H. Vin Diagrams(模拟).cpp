/*
30ms	400KB
因为限制条件很多，所以直接从`A`和`B`位置开始DFS，求出每个`X`属于的方阵，然后再对方阵里面的点DFS。至于交，可以先分别DFS整个A方阵和B方阵中的点，被DFS两次的点即交。
然后想找到A或B方阵中的某个点，可以找到方阵的**左上角**$(i,j)$，那么$(i+1,j+1)$一定在该方阵中，从它开始DFS即可。
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define OK(x,y) (x>=1 && x<=n && y>=1 && y<=m)
typedef long long LL;
const int N=105,Way[5]={1,0,-1,0,1};//down,left,up,right

int n,m,Ans[5],bel[N][N];//1:A 2:B 3:intersection
char s[N][N];
int vis[N][N],vis2[N][N];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
void DFS(int x,int y,int val,int pre)
{
	int t=0;
	for(int i=0; i<4; ++i)
	{
		int xn=x+Way[i],yn=y+Way[i+1];
		if(OK(xn,yn)) t+=s[xn][yn]!='.';
	}
	if(t==4)
	{
		bel[x][y]=3;
		for(int i=0; i<4; ++i)
			if(i==pre)
			{
				int xn=x+Way[i],yn=y+Way[i+1];
				if(OK(xn,yn)&&s[xn][yn]=='X'&&!bel[xn][yn]) DFS(xn,yn,val,i);
			}
	}
	else
	{
		bel[x][y]=val, assert(t==2);
		for(int i=0; i<4; ++i)
		{
			int xn=x+Way[i],yn=y+Way[i+1];
			if(OK(xn,yn)&&s[xn][yn]!='.'&&(!bel[xn][yn]||bel[xn][yn]==3)) DFS(xn,yn,val,i);
		}
	}
}
void DFS2(int x,int y,int val)
{
	vis[x][y]+=val, vis2[x][y]=1;
	for(int i=0; i<4; ++i)
	{
		int xn=x+Way[i],yn=y+Way[i+1];
		if(OK(xn,yn)&&bel[xn][yn]!=val&&bel[xn][yn]!=3&&!vis2[xn][yn]) DFS2(xn,yn,val);
	}
}
void Calc(int val)
{
	memset(vis2,0,sizeof vis2);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)//找一个最左上角的，它的右下一定在封闭图形里面 
			if(bel[i][j]==val) {DFS2(i+1,j+1,val); return;}
}

int main()
{
	int n=read(),m=read(); ::n=n, ::m=m;
	for(int i=1; i<=n; ++i) scanf("%s",s[i]+1);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			if(s[i][j]=='A'||s[i][j]=='B') DFS(i,j,s[i][j]=='A'?1:2,0);
	Calc(1), Calc(2);

	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j) if(!bel[i][j]) ++Ans[vis[i][j]];
	printf("%d %d %d\n",Ans[1],Ans[2],Ans[3]);
	

	return 0;
}
