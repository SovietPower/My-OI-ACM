/*
38448kb	2488ms
����һ�ִ���ı���BFS����չ��ʱ��û�и�����չ�ĵ㣩�����ǼӸ�random_shuffle����Ҳ��֪������ô����
Ԥ����ÿ�����ܵ�������$[l,r]$��
����$i,i+1$��һ���ţ����Կ����$i$���ұߣ�����$i\to i+1$����ʾ��$i$����������$i+1$����������$i+1\to i$��û���ŵĻ�������һ���㡣
������ڱ�$i\to j$����ô$j$���������$i$����$i$�϶�������$j$��������ȵĵ㱩����չ���������ܵ��ĵ���������һ��Ȼ���ٱ�����չ�����Ӷ���$O(n)$�ġ�
����һ��������[���](https://www.cnblogs.com/mjtcn/p/10424510.html)���о�Ҳ��Щ����Ӷ�Ҳ��$O(n)$��

����ֱ�Ӷ�ÿ����$DFS$���ϼ��仯��д����һ�����Ҳ��$O(n)$�ģ��ұ�ʾ����������
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e6+5;

int pos[N],L[N],R[N],A[N];
std::vector<int> vec[N];
std::priority_queue<int,std::vector<int>,std::greater<int> > q;
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
bool BFS1(int t,int s)
{
	int l=s,r=s;
	while(t<l||t>r)
	{
		bool f=0;
		while(!pos[r]||(pos[r]<=r&&pos[r]>=l)) f=1, ++r;
		while(!pos[l-1]||(pos[l-1]<=r&&pos[l-1]>=l)) f=1, --l;
		if(!f) break;
	}
	return t>=l&&t<=r;
}
void Subtask1(int n,int m,int Q)
{
	while(Q--) puts(BFS1(read(),read())?"YES":"NO");
}
void Subtask2(int n,int m,int Q)
{
	for(int i=1; i<n; ++i) if(pos[i]) vec[pos[i]].push_back(i);
	L[1]=1, R[1]=n, q.push(N);
	for(int x=2; x<n; ++x)
	{
		if(pos[x-1])
		{
			L[x]=x;
			for(int i=L[x-1]; i<x; ++i)
				for(int j=0,l=vec[i].size(); j<l; ++j) q.push(vec[i][j]);
			while(q.top()<x) q.pop();
			R[x]=q.top();
		}
		else L[x]=L[x-1], R[x]=R[x-1];
	}
	for(int s,t; Q--; ) s=read(),t=read(),puts(L[s]<=t&&t<=R[s]?"YES":"NO");
}
void BFS2(int s)
{
	int l=s,r=s;
	while(1)
	{
		bool f=0;
		while(!pos[r]||(pos[r]<=r&&pos[r]>=l))
		{
			f=1, ++r;
			if(L[r]) l=std::min(l,L[r]), r=std::max(r,R[r]);
		}
		while(!pos[l-1]||(pos[l-1]<=r&&pos[l-1]>=l))
		{
			f=1, --l;
			if(L[l]) l=std::min(l,L[l]), r=std::max(r,R[l]);
		}
		if(!f) break;
	}
	L[s]=l, R[s]=r;
}

int main()
{
//	freopen("game.in","r",stdin);
//	freopen("game.out","w",stdout);

	const int n=read(),m=read(); int Q=read();
	bool f=1;
	for(int i=1,x; i<=m; ++i)
	{
		x=read(), pos[x]=read();
		if(pos[x]>x) f=0;
	}
	pos[n]=N, pos[0]=N;
	if(1ll*n*m<=1e7) return Subtask1(n,m,Q),0;
	if(f) return Subtask2(n,m,Q),0;
	for(int i=1; i<=n; ++i) A[i]=i;
	std::random_shuffle(A+1,A+n+1);//mt199...
	for(int i=1,x=A[i]; i<=n; x=A[++i]) BFS2(x);
	for(int s,t; Q--; ) s=read(),t=read(),puts(L[s]<=t&&t<=R[s]?"YES":"NO");

	return 0;
}
