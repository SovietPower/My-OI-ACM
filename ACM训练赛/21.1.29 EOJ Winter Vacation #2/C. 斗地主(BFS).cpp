/*
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
typedef long long LL;
const int N=1405,M=620;
const int Dx[]={0,1,1,-1,-1,2,2,-2,-2,3,3,-3,-3,2,-2,4,-4,6,-6};
const int Dy[]={0,1,-2,-1,2,2,-4,-2,4,3,-6,-3,6,-1,1,-2,2,-3,3};

struct Node
{
	int dep,a,b;
};
std::queue<Node> q;
bool vis[N][N];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	int a[5];
	int n=read(); for(int i=1; i<=3; ++i) a[i]=read()+M;// std::sort(a+1,a+4);
	Node x=(Node){0,M,M};
	q.push(x);
	while(!q.empty())
	{
		x=q.front(); q.pop();
		int A=x.a,B=x.b;
//		printf("A:%d B:%d dep:%d\n",A,B,x.dep);
		if(x.dep&&A==a[1]&&B==a[2]) return !printf("%d\n",x.dep);
		if(x.dep>n) return !puts("-1");
		for(int i=1; i<=18; ++i)
		{
			int xn=A+Dx[i],yn=B+Dy[i];
//			printf("%d,%d %d %d,%d\n",A,B,i,xn,yn);
			if(!vis[xn][yn]) vis[xn][yn]=1, q.push((Node){x.dep+1,xn,yn});
		}
	}
	

	return 0;
}
