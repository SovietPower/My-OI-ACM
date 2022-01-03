#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
#define BIT 12
typedef long long LL;
typedef unsigned long long ull;
const int N=2005,dx[]={1,0},dy[]={0,1};

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int n,k,prex[N][N][BIT+1],prey[N][N][BIT+1];
ull w1[N<<1],w2[N<<1],hs[N][N][BIT+1];
char A[N][N],tmps[N<<1],Ans[N<<1],prec[N][N];
struct Node
{
	int x,y,k,now;
};

inline ull Rd()
{
	return (((((rand()<<16)|rand())<<16)|rand())<<16)|rand();
}

void Check(int k)
{
	int t=0,x=n,y=n,tmpx; tmps[++t]=k?'a':A[n][n];
	while(x!=1||y!=1)
		tmps[++t]=prec[x][y], tmpx=x, x=prex[x][y][0], y=prey[tmpx][y][0];
	for(int i=1; i<=t; ++i)
		if(Ans[i]<tmps[i]) return;
		else if(Ans[i]>tmps[i]) break;
	std::reverse(tmps+1,tmps+1+t);
	memcpy(Ans,tmps,sizeof Ans);
}
int Better(int x1,int y1,int x2,int y2)
{
	printf("Check(%d,%d) (%d,%d)\n",x1,y1,x2,y2);
	for(int i=BIT,tmp; ~i; --i)
		if(hs[x1][y1][i]==hs[x2][y2][i])
			printf("v1:%I64u v2:%I64u\n",hs[x1][y1][i],hs[x2][y2][i]),
			tmp=x1, x1=prex[tmp][y1][i], y1=prey[tmp][y1][i],
			tmp=x2, x2=prex[tmp][y2][i], y2=prey[tmp][y2][i],
			printf("to (%d,%d) (%d,%d)\n",x1,y1,x2,y2);
	if(prec[x1][y1]<prec[x2][y2]) return 1;
	if(prec[x1][y1]>prec[x2][y2]) return 0;
	return -1;
}
void Solve(int n,int K)
{
	static int rest[N][N];
	static std::queue<Node> q;
	memset(rest,0xff,sizeof rest);
	rest[1][1]=A[1][1]=='a'?k:k-1;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j) prec[i][j]='z'+1;
	for(int i=2*n-1; i; --i) Ans[i]='z'+1;

	q.push((Node){1,1,K,1});
//	for(int i=1; i<=BIT; ++i) hs[0][0][i]=123486;
	while(!q.empty())
	{
		Node tmp=q.front(); q.pop();
		int x=tmp.x,y=tmp.y,k=tmp.k,now=tmp.now;
		if(x==n&&y==n) {Check(k); continue;}
		char c=A[x][y];
		if(k&&c!='a') --k, c='a';
		if(Ans[now]<c) continue;
		++now;

		for(int xn,yn,i=1; i<=BIT; ++i)
			xn=prex[x][y][i-1], yn=prey[x][y][i-1],
			prex[x][y][i]=prex[xn][yn][i-1], prey[x][y][i]=prey[xn][yn][i-1];
		hs[x][y][0]=prec[x][y];
		for(int i=1,xn,yn; i<=BIT; ++i)
			xn=prex[x][y][i], yn=prey[x][y][i],
			hs[x][y][i]=(hs[x][y][i-1]^w1[now])*w2[now]+hs[xn][yn][i-1];

		for(int i=0,xn,yn; i<2; ++i)
			if((xn=x+dx[i])<=n&&(yn=y+dy[i])<=n)
			{
				if(rest[xn][yn]>k||(k&&rest[xn][yn]==k)) continue;
				if(prec[xn][yn]=='z'+1)
				{
					printf("(%d,%d)->(%d,%d)\n",x,y,xn,yn);
					rest[xn][yn]=k, prex[xn][yn][0]=x, prey[xn][yn][0]=y, prec[xn][yn]=c;
					q.push((Node){xn,yn,k,now});
				}
				else
				{
					int v=Better(x,y,prex[xn][yn][0],prey[xn][yn][0]);
					printf("Better:%d\n",v);
					if((v==-1&&prec[xn][yn]>c)||v==1)
					{
						printf("Better! (%d,%d)->(%d,%d)\n",x,y,xn,yn);
						rest[xn][yn]=k, prex[xn][yn][0]=x, prey[xn][yn][0]=y, prec[xn][yn]=c;
						q.push((Node){xn,yn,k,now});
					}
				}
			}
	}
//	for(int i=2*n-1; i; --i) putchar(Ans[i]);
	for(int i=1; i<2*n; ++i) putchar(Ans[i]);
}

int main()
{
	n=read(),k=read();
	for(int i=1; i<=2*n; ++i) w1[i]=Rd(),w2[i]=Rd();
	for(int i=1; i<=n; ++i)
	{
		register char c=gc(); for(;!isalpha(c);c=gc());
		A[i][1]=c;
		for(int j=2; j<=n; ++j) A[i][j]=gc();
	}
	Solve(n,k);

	return 0;
}
