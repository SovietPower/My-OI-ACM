/*
1736ms	54284kb
�ȿ���һ�е������ÿ�β���Ϊ��������ȡ��һ��Ԫ�أ�Ȼ��ŵ�ȡ���ĵ�n��λ�á��������Ԥ��n+q��λ�ã�������������൱���߶�������ɾ���͵�����롣
��չ�����С����Ƿ��ֶ����һ�еĲ����Ͷ�ĳһ�еĲ�������ͬ�ģ�ȡ��һ�����ŵ�ĩβһ������
�������ǿ�����n+1�ö�̬�����߶���ά����
��Щϸ�ڣ�����ɾ������Ҫ��嵽�߶��������vector���ɡ�
*/
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 150000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=3e5+4;

int n,m,R,root[N];
std::vector<LL> v[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Segment_Tree
{
	#define S N*18//*2
	#define lson son[x][0],l,m
	#define rson son[x][1],m+1,r
	int tot,son[S][2],sum[S];//����Ҫֱ�Ӽ����������== ��ɾ���������� 
	#undef S

	int Delete(int &x,int l,int r,int p)
	{
		if(!x) x=++tot; ++sum[x];
		if(l==r) return l;
		int m=l+r>>1,tmp=m-l+1-sum[son[x][0]];
		if(tmp<p) return Delete(rson,p-tmp);
		return Delete(lson,p);
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
LL Solve1(int x,LL tmp)
{
	int p=T.Delete(root[0],1,R,x);
	LL ans= p<=n?(LL)p*m:v[0][p-n-1];
	v[0].push_back(tmp?tmp:ans);
	return ans;
}
LL Solve2(int x,int y)
{
	int p=T.Delete(root[x],1,R,y);
	LL ans= p<m?(1ll*(x-1)*m+p):v[x][p-m];
	v[x].push_back(Solve1(x,ans));
	return ans;
}

int main()
{
	n=read(),m=read(); int Q=read(); R=std::max(n,m)+Q;
	for(int x,y; Q--; )
	{
		x=read(),y=read();
		if(y==m) printf("%lld\n",Solve1(x,0));
		else printf("%lld\n",Solve2(x,y));
	}
	return 0;
}
