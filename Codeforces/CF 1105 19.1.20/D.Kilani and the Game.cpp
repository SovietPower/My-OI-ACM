#include <set>
#include <map>
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
typedef long long LL;
const int N=1005,M=12,Way[]={1,0,-1,0,1};

int S[N],vis[N][N];
std::queue<pr> q[M];
struct Node
{
	int x,y,step;
};

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
void Solve(int n,int m,int P,int blo)
{
	static int Ans[M];
	int now=blo,lim=n*m,p=1;
	while(now<lim)//while(1)
	{
		int f=0;
		while(!q[p].size()&&f<P) ++p, p>P&&(p=1), ++f;
		if(f==P) break;//奇怪 为什么需要这一个if啊=-= now<lim不行吗=-= 
		Ans[p]+=q[p].size(), now+=q[p].size();
		std::queue<Node> tmp1;
		while(!q[p].empty())
		{
			int x=q[p].front().first,y=q[p].front().second; q[p].pop();
			tmp1.push((Node){x,y,0});
		}
		while(!tmp1.empty())//s[p]次BFS 
		{
			int x=tmp1.front().x,y=tmp1.front().y,step=tmp1.front().step; tmp1.pop();
			if(step==S[p]) {q[p].push(mp(x,y)); continue;}
			if(step) ++now, ++Ans[p];
			for(int i=0,xn,yn; i<4; ++i)
				if((xn=x+Way[i])>0 && xn<=n && (yn=y+Way[i+1])>0 && yn<=m && !vis[xn][yn])
					vis[xn][yn]=p, tmp1.push((Node){xn,yn,step+1});
		}
		++p, p>P&&(p=1);
	}
	for(int i=1; i<=P; ++i) printf("%d ",Ans[i]);
}

int main()
{
	static char s[N];
	int n=read(),m=read(),P=read();
	for(int i=1; i<=P; ++i) S[i]=read();
	int tmp=0;
	for(int i=1; i<=n; ++i)
	{
		scanf("%s",s+1);
		for(int j=1; j<=m; ++j)
			if(isdigit(s[j])) vis[i][j]=s[j]-'0', q[s[j]-'0'].push(mp(i,j));
			else if(s[j]=='#') vis[i][j]=-1, ++tmp;
	}
	Solve(n,m,P,tmp);

	return 0;
}
