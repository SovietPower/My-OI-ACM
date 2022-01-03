/*
80628kb	7088ms
$Description$
����һ��n��Ҷ�ӵĶ�������ÿ��Ҷ�ڵ���Ȩֵ(1<=ai<=n)����������Ľ������������������˳��������õ���Ҷ��Ȩֵ�����У����ٵ���������Ƕ��١�
$Solution$
����Ҫ��һ�����������ڲ��������Ҷ��Ӷ�����������û��Ӱ��ġ�����Ȼ���������ڽ������������������ڲ�Ҳ��û��Ӱ��ģ�
����DFS����ÿ���ڵ������������������˸��žͻ������žͲ�����
��ôͳ������������/������������������أ�������������ֵ���߶����ϲ��������/��������������������������Ĵ�С��ϵ�жϾ����ˡ�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e5+5;

int n;
LL Ans;
char IN[MAXIN],*SS=IN,*TT=IN;
struct Segment_Tree
{
	#define S N*19//ֻ�н������ϲ��Ļ� nlogn�͹��� n(logn+1)!
	#define lson son[x][0]
	#define rson son[x][1]
	int tot,sz[S],son[S][2];

	void Insert(int &x,int l,int r,int p)
	{
		sz[x=++tot]=1;
		if(l==r) return;
		int m=l+r>>1;
		if(p<=m) Insert(lson,l,m,p);
		else Insert(rson,m+1,r,p);
	}
	int Merge(int x,int y,LL &ans1,LL &ans2)
	{
		if(!x||!y) return x^y;
		ans1+=1ll*sz[rson]*sz[son[y][0]], ans2+=1ll*sz[lson]*sz[son[y][1]];
		lson=Merge(lson,son[y][0],ans1,ans2);
		rson=Merge(rson,son[y][1],ans1,ans2);
		sz[x]+=sz[y];// sz[x]=sz[lson]+sz[rson]; ����д���ںϲ�Ҷ�ӽڵ�ʱ���԰�����y���²���x��
		return x;
	}
//	void Print(int x,int l,int r)
//	{
//		if(!x) return;
//		printf("%d:%d~%d sz:%d\n",x,l,r,sz[x]);
//		if(l==r) ;
//		else Print(lson,l,l+r>>1), Print(rson,(l+r>>1)+1,r);
//	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int DFS()//����root 
{
	int v=read();
	if(v) {int x; T.Insert(x,1,n,v); return x;}
	LL ans1=0, ans2=0;
	int rt=T.Merge(DFS(),DFS(),ans1,ans2);//��Ȼ����˳���Ƿ��ŵ� 
	Ans+=std::min(ans1,ans2);
	return rt;
}

int main()
{
	n=read(), DFS(), printf("%lld\n",Ans);
	return 0;
}
