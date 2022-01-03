/*
3656kb	280ms
���±��$0\sim m-1$����Ϊ��������ԭ�߶�$[l,r]$����$l\leq r$�Ͳ�������߶�$[l,r],[l+m-1,r+m-1]$��������һ���߶�$[l,r+m-1]$��������ö�ٵ�ʱ��������ѡ�߶���һ��$m$�����ھ����ˣ�
���Ǳ�����ֱ��ö���Ƿ�һ��ѡĳ���߶�$i$��Ȼ��̰��ѡ�����ļ��ɣ�������ѡ�߶���$[l_i,l_i+m-1]$�ڣ������Ӷ�$O(n^2)$��$O(n^2\log n)$��
�������Ŵ���$x$����$x\leq\sqrt n$����ôÿ������ѡ$x$�Ρ�
��$x\gt\sqrt n$����ôÿ�����һ���߶ζ�����$\frac xn$�ĸ���ѡ�����Ž⡣�����������$\frac nx+$�ο��ܾͲ���ˡ�
��������Ҳ��֪��$x$��д��һ�ֺ���Ҳ���鷳���Ǿ��õڶ�������������������ˡ�
������Ĵ�����$k$����ô���Ӷ���$O(kn)$�ġ�
������ȡ���ˡ���ʵ��ȡ$k=2$�Ϳ��Թ��������=v=��
��Ȼ��ʵ��ȷ�Բ�û�б�֤=v=...
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define Rand() (rand()<<16|rand())
#define gc() getchar()
#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;

int L[N],R[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Node
{
	int l,r;
	bool operator <(const Node &x)const
	{
		return r<x.r;
	}
}A[N<<1];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
int Calc(int x,int n,int m,int tot)
{
	int ans=0;
	for(int i=1,now=0,l=L[x],r=l+m; i<=tot; ++i)
		if(A[i].l>=l && A[i].r<=r && A[i].l>=now)
			now=A[i].r, ++ans;
	return ans;
}

int main()
{
	srand(1002330);
	const int m=read()-1,n=read(); int tot=0;
	for(int i=1; i<=n; ++i)
	{
		int l=L[i]=read(),r=R[i]=read();//�Ҹտ�ʼ��Ȼû��L[i] WA n��=-= 
		if(l<=r) A[++tot]=(Node){l,r}, A[++tot]=(Node){l+m,r+m};
		else A[++tot]=(Node){l,r+m};
	}
	std::sort(A+1,A+1+tot);
	int ans=0;
//	for(int k=2,i=1; i<=n; i+=n/k) ans=std::max(ans,Calc(i,n,m,tot));//Ҳ�ɹ�...
	for(int k=100; k--; ) ans=std::max(ans,Calc(Rand()%n+1,n,m,tot));
	printf("%d\n",ans);

	return 0;
}
