/*
107ms	2028kb
稳定婚姻问题：有n个男生n个女生，每个男/女生对每个女/男生有一个不同的喜爱程度。给每个人选择配偶。
若不存在 x,y未匹配，且x喜欢y胜过喜欢x当前的配偶，y喜欢x也胜过y当前的配偶 的完备匹配，则称这是一个稳定匹配。
稳定匹配一定存在，且存在一个$O(n^2)$的算法：
任选一个未匹配的男生x，按x的喜爱程度从大到小枚举每个女生，若当前女生没有配偶或喜欢x胜过喜欢当前配偶，则与x匹配。直到所有男生都匹配。
这一题我们用行表示男生，n个数表示女生。喜爱程度为：行更喜欢靠前的数，数更喜欢其出现位置靠后的行。
eg.如果x这一行靠后的一些数都被选过了，让它们喜欢x，要不产生矛盾则要x喜欢(选)尽量靠前的数。
复杂度$O(nm)$。
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=205,M=405;

int A[N][M],pos[N][N],lk[N],ans[N];
std::queue<int> q;
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	for(int T=read(),n,m; T--; )
	{
		n=read(), m=read();
		for(int i=1; i<=n; ++i)
			for(int j=1; j<=m; ++j)
				pos[i][A[i][j]=read()]=j;
		memset(lk,0,sizeof lk);
		for(int i=1; i<=n; ++i) q.push(i);
		while(!q.empty())
		{
			int x=q.front(); q.pop();
			ans[x]=0;
			for(int i=1,v; i<=m; ++i)
				if(v=A[x][i])
				{
					if(!lk[v]) {lk[v]=x, ans[x]=v; break;}
					else if(pos[x][v]>pos[lk[v]][v])
					{
						q.push(lk[v]), lk[v]=x, ans[x]=v;
						break;
					}
				}
		}
		for(int i=1; i<=n; ++i) printf("%d ",ans[i]); putchar('\n');
	}
	return 0;
}
