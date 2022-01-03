/*
480556kb	16480ms
����: �ڸ��������������ҳ����ٵ����������>=k��������ĸ������������ݷ�Χ��
0~50 ע�⵽(��ûע�⵽...)P[i,j]<=1000�����ǿ�������ǰ׺��Ԥ����.
num[i][j][v]��ʾ(1,1)~(i,j)��ֵ>=v�ĸ�����val[i][j][v]��ʾ(1,1)~(i,j)ֵ>=v���������ĺ͡�(��Ҫ��ʲô>=v�ӣ��Ͷ�άǰ׺��һ����ֻ��һ����ĳ�ʼֵΪA[i,j]>=k)
���ɶ��֡�(�����������֮����Ż��ռ䣿������)
60~100 ��һ�����е��������� �����>=k������ϯ��+��������ע��ȥ�ض�sz[]��Ӱ�죡P[i,j]<=1000��������ɢ����
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define Failed puts("Poor QLW")

int r,c,Q;
inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
namespace Problem1
{
	const int N=202;

	int A[N][N],num[N][N][1002],val[N][N][1002];

	inline int Get_num(int x1,int y1,int x2,int y2,int v){
		return num[x2][y2][v]-num[x1][y2][v]-num[x2][y1][v]+num[x1][y1][v];
	}
	inline int Get_val(int x1,int y1,int x2,int y2,int v){
		return val[x2][y2][v]-val[x1][y2][v]-val[x2][y1][v]+val[x1][y1][v];
	}
	void Solve()
	{
		int Max=0;
		for(int i=1; i<=r; ++i)
			for(int j=1; j<=c; ++j) Max=std::max(Max,A[i][j]=read());
		for(int k=1; k<=Max; ++k)
			for(int i=1; i<=r; ++i)
				for(int j=1; j<=c; ++j)//ÿ��kֱ�ӵ��ƾ��а���sb�ˡ�
					num[i][j][k]=num[i-1][j][k]+num[i][j-1][k]-num[i-1][j-1][k]+(A[i][j]>=k),
					val[i][j][k]=val[i-1][j][k]+val[i][j-1][k]-val[i-1][j-1][k]+(A[i][j]>=k?A[i][j]:0);//���ţ�Ҫ������val=(..+..+..)>=k?A:0; 
		int x1,y1,x2,y2,h;
		while(Q--)
		{
			x1=read()-1,y1=read()-1,x2=read(),y2=read(),h=read();
			int l=1,r=Max,mid,res=0;
			while(l<=r)
			{
				if(Get_val(x1,y1,x2,y2,mid=l+r>>1)>=h) l=mid+1,res=mid;
				else r=mid-1;
			}
			if(res) printf("%d\n",Get_num(x1,y1,x2,y2,res)-(Get_val(x1,y1,x2,y2,res)-h)/res/*�ظ�����*/);
			else Failed;
		}
	}
}
namespace Problem2
{
	#define lson son[rt][0]
	#define rson son[rt][1]
	const int N=5e5+5,S=500005*20,Max=1e3;

	int A[N],root[N],tot,son[S][2],sz[S],sum[S];

	inline void Update(int rt){
		sum[rt]=sum[lson]+sum[rson];
	}
	void Insert(int rt,int &y,int l,int r,int p)
	{
		sz[y=++tot]=sz[rt]+1, sum[y]=sum[rt]/*no need?*/;
		if(l==r) sum[y]+=p;//s_y=s_x+ref[p]
		else{
			int m=l+r>>1;
			if(p<=m) son[y][1]=rson, Insert(lson,son[y][0],l,m,p);
			else son[y][0]=lson, Insert(rson,son[y][1],m+1,r,p);
			Update(y);
		}
	}
	int Query(int rt,int y,int l,int r,int k)
	{
		if(sz[y]<=sz[rt]+k) return sum[y]-sum[rt];
		if(l==r) return (sum[y]-sum[rt])/(sz[y]-sz[rt])*k;
		if(sz[son[y][1]]>=sz[rson]+k) return Query(rson,son[y][1],(l+r>>1)+1,r,k);
		return Query(lson,son[y][0],l,l+r>>1,k-sz[son[y][1]]+sz[rson])+sum[son[y][1]]-sum[rson];
	}
	void Solve()
	{
		for(int i=1; i<=c; ++i) A[i]=read();
		int x,s,t,h;
		for(int i=1; i<=c; ++i) Insert(root[i-1],root[i],1,Max,A[i]);
		while(Q--)
		{
			x=read(),s=read()-1,x=read(),t=read(),h=read();
			int l=1,r=t-s+1,mid;
			int tst;
			while(l<r)
			{
				if((tst=Query(root[s],root[t],1,Max,mid=l+r>>1))>=h) r=mid;
				else l=mid+1;
			}
			if(r==t-s+1) Failed;
			else printf("%d\n",l);
		}
	}
}

int main()
{
	r=read(),c=read(),Q=read();
	r==1?Problem2::Solve():Problem1::Solve();
	return 0;
}
