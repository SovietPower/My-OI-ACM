/*
38224kb	2860ms
��mxΪ��������1~mx������ɵ�����
���ǵ�ǰ�ܹ���1~v�е����������ټ���һ����x����x>v+1����mx=v��x�������Ӱ�죻����x<=v+1�����µ�mx=x+v��
��������[l,r]��ѯ�ʣ�ģ��������̡����赱ǰ��Ϊv����ѯ[l,r]��ֵ��[1,v+1]�е����ĺ�sum����sum==v����������v+1��break������v������Щv+1�ĺͼ�v=sum��������
����ϯ��ʵ�֡�vÿ����������һ�������Ը��Ӷ�$O(nlognloga)$��
Ϊʲô�ܵıȽ����ء���
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1e5+5;

int A[N],root[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Tree
{
	#define S N*31//loga not logn && 31 not 30...
	#define lson son[x][0]
	#define rson son[x][1]
	int tot,sum[S],son[S][2];

	inline void Insert(int x,int &y,int l,int r,int p)
	{
		sum[y=++tot]=sum[x]+p;
		if(l==r) return;
		int m=l+r>>1;
		if(p<=m) son[y][1]=rson, Insert(lson,son[y][0],l,m,p);
		else son[y][0]=lson, Insert(rson,son[y][1],m+1,r,p);
	}
	int Query(int x,int y,int l,int r,int R)
	{
		if(r<=R) return sum[y]-sum[x];
		int m=l+r>>1;
		if(m<R) return sum[son[y][0]]-sum[lson]+Query(rson,son[y][1],m+1,r,R);
		else return Query(lson,son[y][0],l,m,R);
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int n=read(); int R=1;
	for(int i=1; i<=n; ++i) R+=(A[i]=read());
	for(int i=1; i<=n; ++i) T.Insert(root[i-1],root[i],1,R,A[i]);
	for(int m=read(),l,r,ans,sum; m--; )
	{
		l=read(),r=read(),ans=0;
		while(ans<(sum=T.Query(root[l-1],root[r],1,R,ans+1))) ans=sum;
		printf("%d\n",ans+1);
	}
	return 0;
}
