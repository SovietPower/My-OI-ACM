/*
4432kb	13600ms
二维莫队，按x,y坐标一起分块.(x,y)的所属的块为 x/sq(n)*sq(m) + y/sq(m) 
排序时按照(左下点所在块，右上点的标号)排序 
排序后 先得出一个询问的答案，然后利用上一个询问的矩形与当前矩形位置关系更新答案 
转移真的麻烦。。为了避免算重 一定要加个vis[][] 
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=205,M=1e5+5;

int n,m,Q,szX,szY,A[N][N],ref[N*N],tm[N*N],bel[N][N],idv[N][N];
LL Ans[M],Now;
bool vis[N][N];
struct Ask
{
	int x1,y1,x2,y2,id;
	inline bool operator <(const Ask &a)const{
		return bel[x1][y1]==bel[a.x1][a.y1]?idv[x2][y2]<idv[a.x2][a.y2]:bel[x1][y1]<bel[a.x1][a.y1];
	}
}q[M];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
int Find(int x,int r)
{
	int l=1,mid;
	while(l<r)
		if(ref[mid=l+r>>1]>=x) r=mid;
		else l=mid+1;
	return l;
}
void Discrete()
{
	int tot=0,cnt=1;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			ref[idv[i][j]=++tot]=A[i][j]=read();
	std::sort(ref+1,ref+1+tot);
	for(int i=2; i<=tot; ++i)
		if(ref[i]!=ref[i-1]) ref[++cnt]=ref[i];
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			A[i][j]=Find(A[i][j],cnt);
}
inline void add(int i,int j){
	if(!vis[i][j]) vis[i][j]=1, Now+=2*(tm[A[i][j]]++)+1;
}
inline void subd(int i,int j){
	if(vis[i][j]) vis[i][j]=0, Now-=2*(--tm[A[i][j]])+1;
}
void Add(int x1,int x2,int y1,int y2)
{
	for(int i=x1; i<=x2; ++i)
		for(int j=y1; j<=y2; ++j) add(i,j);
}
void Subd(int x1,int x2,int y1,int y2)
{
	for(int i=x1; i<=x2; ++i)
		for(int j=y1; j<=y2; ++j) subd(i,j);
}
void Change(int l,int n)
{//now位于las的左下方 左上方 被包含 都是可能的 
	int t;
	t=std::min(q[l].x1-1,q[n].x2), Add(q[n].x1,t,q[n].y1,q[n].y2);
	t=std::min(q[l].y1-1,q[n].y2), Add(q[n].x1,q[n].x2,q[n].y1,t);
	t=std::max(q[l].x2+1,q[n].x1), Add(t,q[n].x2,q[n].y1,q[n].y2);
	t=std::max(q[l].y2+1,q[n].y1), Add(q[n].x1,q[n].x2,t,q[n].y2);
	
	t=std::min(q[l].x2,q[n].x1-1), Subd(q[l].x1,t,q[l].y1,q[l].y2);
	t=std::min(q[l].y2,q[n].y1-1), Subd(q[l].x1,q[l].x2,q[l].y1,t);
	t=std::max(q[l].y1,q[n].y2+1), Subd(q[l].x1,q[l].x2,t,q[l].y2);
	t=std::max(q[l].x1,q[n].x2+1), Subd(t,q[l].x2,q[l].y1,q[l].y2);
}

int main()
{
	n=read(),m=read(); szX=sqrt(n),szY=sqrt(m);
	Discrete();
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			bel[i][j]=(i-1)/szX*szY+(j-1)/szY;
//	for(int i=1; i<=n; ++i,putchar('\n'))
//		for(int j=1; j<=m; ++j) printf("%d ",bel[i][j]);
	Q=read();
	for(int i=1; i<=Q; ++i)
	{
		q[i].x1=read(),q[i].y1=read(),q[i].x2=read(),q[i].y2=read();
		if(q[i].x1>q[i].x2) std::swap(q[i].x1,q[i].x2);//将(x1,y1)设为矩形左下角 
		if(q[i].y1>q[i].y2) std::swap(q[i].y1,q[i].y2);
		q[i].id=i;
	}
	std::sort(q+1,q+1+Q);
	Add(q[1].x1,q[1].x2,q[1].y1,q[1].y2);
	Ans[q[1].id]=Now;
	for(int i=2; i<=Q; ++i)
		Change(i-1,i), Ans[q[i].id]=Now;
	for(int i=1; i<=Q; ++i) printf("%lld\n",Ans[i]);

	return 0;
}
