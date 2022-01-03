/*
404ms	3.36MB
$Description$
����һ�������Ȩ��ͨͼ��ÿ�����Ǻ�ɫ���ɫ����һ����СȨ��ǡ����K���ױߵ���������
$Solution$
Kruskal��ѡȡ��С��n-1���ߡ����ױ��������ƣ�����Ϊ��������ȨC��
����C����ѡ�İױ���Ӧ�ǲ����ġ����Զ�����һ��Cֵʹ�ô�ʱǡ��ѡ��K���ߡ�ѡȡʱӦ����ѡ�ױߣ���Ϊ���˻������úڱ��滻������ֻ�ܼ���C��
���ܵ������ǣ�C=midʱ�ױ���>K��C=mid+1ʱ�ױ���<K����Ϊ�кܶ�ڱ���+mid��İױ�Ȩֵ��ȡ���������Щ�ڱ��滻������İױߣ����Դ�Ӧ�Ǽ�K*mid(�����ڱ�)��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 100000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=5e4+5,M=1e5+5;

int n,m,K,fa[N],Ans;
char IN[MAXIN],*SS=IN,*TT=IN;
int read();
struct Edge
{
	int fr,to,val,col;
	inline void Init(){
		fr=read()+1, to=read()+1, val=read(), col=read();
	}
	bool operator <(const Edge &x)const{
		return val==x.val?col<x.col:val<x.val;
	}
}e[M];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int GetFa(int x){
	return x==fa[x]?x:fa[x]=GetFa(fa[x]);
}
bool Check(int x)
{
	for(int i=1; i<=m; ++i) if(!e[i].col) e[i].val+=x;
	for(int i=1; i<=n; ++i) fa[i]=i;
	std::sort(e+1,e+1+m);
	int sum=0, cnt=0;
	for(int i=1,k=0,r1,r2; i<=m; ++i)
	{
		if((r1=GetFa(e[i].fr))==(r2=GetFa(e[i].to))) continue;
		fa[r1]=r2, sum+=e[i].val;
		cnt+=e[i].col^1;
		if(++k+1==n) break;
	}
	for(int i=1; i<=m; ++i) if(!e[i].col) e[i].val-=x;
	if(cnt<K) return 0;
	Ans = sum-K*x;//����ȡmin��
	return 1;
}

int main()
{
	n=read(),m=read(),K=read();
	for(int i=1; i<=m; ++i) e[i].Init();
	Ans=m*101; int l=-101,r=101,mid;
	while(l<=r)//l==rʱҪCheckһ��(���߽���ʱ)
		if(Check(mid=l+r>>1)) l=mid+1;
		else r=mid-1;
//	Check(l);
	printf("%d",Ans);

	return 0;
}
