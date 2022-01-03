/*
21632kb	880ms
$Description$
����$n$������$[L_i,R_i]$��Ҫѡ������������䣬���������ǻ����ཻ���������ѡ�����ٸ��������Լ��ֵ�����С�ķ�����
$n\leq2\times10^5$��
$Solution$
��һ���������
���ڵڶ��ʣ���С����ö������$[l_i,r_i]$��������Ҫ�жϴ�ʱ�ܲ���ѡ$[l_i,r_i]$��
��֮ǰѡ�������У�����$i$�����$l_i$�����������Ҷ˵���$L$����$i$�ұ���$i$�������˵���$R$��
��ȻҪ����$i$��ѡ�е����䲻�ཻ����$L<l_i$��$R>r_i$��ͬʱ��������������ѡ���������һ�������ڵġ�����$set$ά��ѡ������䣬$lower\_bound$һ���ҳ���

���㲻�ཻ�󣬻�Ҫ�������š�
��$Ans(l,r)$��ʾ����$[l,r]$��ѡ���������������
��ô�ܷ�������$[l_i,r_i]$��Ҫ����$Ans(L+1,R-1)==Ans(L+1,l_i-1)+Ans(r_i+1,R-1)+1$���ܺ���⡣��ֻ��$i$��ǰ��׺��Ȼ���԰���

�����$Ans(l,r)$��
���ֿ����ҵ���һ������$l_i\geq l$������$i$��Ȼ���$i$����ѡ��ֱ���Ҷ˵�$>r$��������򵥵�̰�ģ�ÿѡһ��������һ��ѡ���������ȷ���ġ�so���Ա�������$f[i][j]$��ʾ������$i$��ʼѡ��ѡ��$2^j$�������ͣ���ĸ����䡣
��Ȼ��ʱ���԰���ȫ������������Ĵ������ȥ����������Ҫȥ�������ѡ�����ǻ�Ӱ��𰸣���
*/
#include <set>
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e5+5,INF=1<<30;

int cnt,Bit,L[N],R[N],f[18][N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Node
{
	int l,r,id;
	bool operator <(const Node &x)const
	{
		return r==x.r?l>x.l:r<x.r;
	}
}A[N],tmp[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline int Find(int x)
{
	int l=1,r=cnt,mid;//cnt+1!��l may be greater than l[cnt]��
	while(l<r)
		if(L[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}
inline int Calc(int l,int r)
{
	if(L[cnt]<l) return 0;
	int p=Find(l);
	if(R[p]>r) return 0;
	int res=1;
	for(int i=Bit; ~i; --i)
		if(R[f[i][p]]<=r) res+=1<<i, p=f[i][p];
	return res;
}

int main()
{
	const int n=read();
	for(int i=1; i<=n; ++i) A[i]=tmp[i]=(Node){read(),read()};
	std::sort(tmp+1,tmp+1+n), cnt=1;
	for(int i=2; i<=n; ++i) if(tmp[i].l>tmp[cnt].l) tmp[++cnt]=tmp[i];//���Ҷ˵�Ӧ�ö��ǵ����� 
	for(int i=1; i<=cnt; ++i) L[i]=tmp[i].l, R[i]=tmp[i].r;
	L[cnt+1]=INF+1, R[0]=R[cnt+1]=INF+1;//INF+1!��������l~INF��
	for(int i=1,j=1; i<=cnt; ++i)
	{
		while(L[j]<=R[i]) ++j;
		f[0][i]=j;
	}
	for(; 1<<Bit+1<=cnt; ++Bit);
	for(int j=1; j<=Bit; ++j)
		for(int i=1; i<=cnt; ++i)
			f[j][i]=f[j-1][f[j-1][i]];

	int ans=Calc(1,INF-1); printf("%d\n",ans);
	std::set<Node> st;
	st.insert((Node){0,0}), st.insert((Node){INF,INF});
	for(int i=1,k=0; i<=n; ++i)
	{
		int l=A[i].l, r=A[i].r;
		std::set<Node>::iterator it=st.lower_bound(A[i]);
		int R=(*it).l; if(r>=R) continue;
		int L=(*(--it)).r; if(l<=L) continue;
		if(Calc(L+1,R-1)==Calc(L+1,l-1)+Calc(r+1,R-1)+1)
			if(++k!=ans) printf("%d ",i), st.insert(A[i]);
			else {printf("%d",i); break;}
	}

	return 0;
}
