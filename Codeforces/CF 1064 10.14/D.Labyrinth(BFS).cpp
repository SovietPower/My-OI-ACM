/*
62ms	4100KB
��ΪBFSһ���ǿ��Ա�֤����һ����ʱ������С�����Կ���BFS��
����������������������ۡ���Ȼ�������û�и����谭�����ǿ�����һֱ��������չ״̬��
Ȼ�����һֱ����������ң���ôBFS���ĵ���Ȼ������С��
���Ҫ�߻�ͷ·����ֱ�����ϵ�·����ס����������ȥ������ô�����������Ҫ��$a$�������������ƻ�ȥ�����ұ���Ҫ$b$�������������ƻ�ȥ����ôǰ������ҲҪ��$a$������������ҲҪ��$b$������������ֻ��֤�����ߵĲ��������٣��Ϳ��Ա�֤����ĳһ����ʱ�����ߵĲ���Ҳ�����١�����Ҳ�ܷ���BFS���ʣ�ֱ��BFS��
���������ߵĲ����ٲ�����������������ͼ�����Ϊ�׵㣬Ҫ�����̵㣬��Ȼ�Ӱ׵�����������������٣�����ָ�������ҵĲ��������������ֱ��BFS����Ϊ������������˷���ʱ�䣬����ʵ���ȵ��̵������׵��ұ߳�����·�����⵱Ȼ���ţ����Ѷࣩ��
��Ϊ���������ǲ��ƴ��۵ģ�Ҳ���Ǿ���Ϊ$0$��������BFS��һ����ʱ��Ҫ����������ֱ�ӵ��ĵ�ͬʱ������У�������ͬ��Ҳ���Ǿ�����ͬ����Ȼ��BFS��Ҫͬʱ��ӣ����������ڰ�����������ʱ���ڶ����м������µĵ㣨BFS�����壿�����ĵ㻨��/�����֮ǰ�ĵ�ߡ���ʵ�����Ǵ�����һ���ģ���
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=2005;
const int D[]={-1,1};

int n,m,r,c,X,Y;
bool ok[N][N];
struct Node
{
	int x,y,r1,r2;
};
std::queue<Node> q;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void Extend(int x,int y,int r1,int r2)
{
	for(int i=x; ok[i][y]; --i)
		ok[i][y]=0, q.push((Node){i,y,r1,r2});
	for(int i=x+1; ok[i][y]; ++i)
		ok[i][y]=0, q.push((Node){i,y,r1,r2});
}
void BFS()
{
	int ans=0;
	Extend(r,c,X,Y);
	while(!q.empty())
	{
		++ans;
		Node tmp=q.front(); q.pop();
		int x=tmp.x,y=tmp.y,r1=tmp.r1,r2=tmp.r2;
		if(r1&&ok[x][y-1]) Extend(x,y-1,r1-1,r2);
		if(r2&&ok[x][y+1]) Extend(x,y+1,r1,r2-1);
	}
	printf("%d\n",ans);
}

int main()
{
	n=read(),m=read(),r=read(),c=read(),X=read(),Y=read();
	for(int i=1; i<=n; ++i)
	{
		register char c=gc(); while(c!='*'&&c!='.') c=gc();
		ok[i][1]=c=='.';
		for(int j=2; j<=m; ++j) ok[i][j]=gc()=='.';
	}
	BFS();

	return 0;
}
